#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ArduinoOTA.h>

#include <CycleLimit.h>

#include "inputs.h"
#include "parameters.h"
#include "status.h"
#include "html.h"
#include "storage.h"
#include "uptime.h"
#include "wifi_data.h"

/// @brief used to control fan
constexpr byte PWM_PIN = D8;

/// @brief Main loop cycle time
constexpr int CYCLE_TIME_MS = 1000;

// static publics
Parameters::Parameters _parameters = {};
Status::Status _status = {};
ESP8266WebServer _server(80);

/// @brief Calc the PWM duty cycle
/// @param heaterTemp in ° C
/// @param roomTemp in ° C
/// @return 0.0 to 100.0
float CalcFanPowerPerc(float heaterTemp, float roomTemp)
{
  // heaters are hot enough?
  if (heaterTemp < _parameters.THeatMin)
    return 0;

  // 100 % region?
  float const tRoomMinLerpBound = _parameters.TRoomMin - 1;
  if (roomTemp < tRoomMinLerpBound)
    return 100;

  // 0% region?
  if (roomTemp > _parameters.TRoomMin)
    return 0;

  // LERP within the interval [TRoomMin - 1; TRoomMin]
  // increase integer precision
  float pwm = map((int)(100.0f * roomTemp), (int)(100.0f * tRoomMinLerpBound), (int)(100.0f * _parameters.TRoomMin), 0, 100);

  // sanity check & cap
  return isnan(pwm) ? 100 : max(min(pwm, 100.0f), 0.0f);
}

void busyWaitWifiConnected()
{
  Serial.print("Wait for Wifi");
  while (WiFi.status() != WL_CONNECTED)
  {
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.print(".");
  }
}

/// @brief SETUP
void setup()
{
  // activate Serial
  Serial.begin(115200);

  // set fast-PWM to mid frequency of 16k
  analogWriteFreq(16000);

  // activate LED
  pinMode(LED_BUILTIN, OUTPUT);

  // setup modules
  Inputs::Setup();
  Html::setup(_server, _parameters, _status);
  Storage::Setup();

  // load parameters
  if (!Storage::Load(_parameters))
  // no storage found
  {
    Serial.println("Storage empty, generating...");

    _parameters = Parameters::Parameters();

    Storage::Store(_parameters);
  }

  // wifi setup
  WiFi.mode(WIFI_STA);
  // stay connected to wifi
  WiFi.persistent(true);
  WiFi.begin(WIFI_SERVER_SETUP.Ssid, WIFI_SERVER_SETUP.Password);
  busyWaitWifiConnected();
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // setup ota updates
  ArduinoOTA.setPassword("sjalw8589slxcmcxyie2980tnsdas");
  ArduinoOTA.onStart([]()
                     {
      String type = ArduinoOTA.getCommand() == U_FLASH ? "sketch" : "filesystem";
      Serial.println("Start updating " + type); });
  ArduinoOTA.onEnd([]()
                   { Serial.println("\nEnd"); });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total)
                        { Serial.printf("Progress: %u%%\r", (progress / (total / 100))); });
  ArduinoOTA.onError([](ota_error_t error)
                     {
      Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
      else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
      else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
      else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
      else if (error == OTA_END_ERROR) Serial.println("End Failed"); });
  ArduinoOTA.begin(false); // no useMDNS!

  // HTML ressource mapping
  _server.on("/", Html::onGetHome);
  _server.on("/favicon.ico", Html::onGetFavicon);
  _server.on("/status", Html::onGetStatus);
  _server.on("/parameters", Html::onGetOrPostParameters);
  _server.on("/manual", Html::onManualOverride);
  // 404
  _server.onNotFound([]()
                     { _server.send(404, "text/plain", "Not Found"); });
  // logging
  _server.addHook([](const String &method, const String &url, WiFiClient *client, ESP8266WebServer::ContentTypeFunction contentType)
                  { Serial.printf("HTML %s %s\n", method.c_str(), url.c_str());
                  return ESP8266WebServer::CLIENT_REQUEST_CAN_CONTINUE; });
  _server.begin();
}

void cycle1Hz()
{
  // get temp readings
  auto const report = Inputs::Read();
  _status.HeaterTemp = report.Temp1;
  _status.RoomTemp = report.Temp2;

  // t1 = heater, t2 = room
  _status.PowerRequestPerc = CalcFanPowerPerc(report.Temp1, report.Temp2);

  // manual override?
  if (_status.ManualSecondsLeft > 0)
  {
    // tick down!
    _status.ManualSecondsLeft -= 1;
    _status.PowerRequestPerc = _status.ManualPowerPerc;
  }

  // detect that a startup is necessary
  static int StartupCycles = 0;
  static decltype(_status.PowerRequestPerc) LastRequest = 0;
  if (
      (StartupCycles <= 0)                         // if not in startup already
      && (_status.PowerRequestPerc != LastRequest) // if power perc changed since last iteration
      && (_status.PowerRequestPerc != 0))          // if not shut off
  {
    // add startup cycles
    StartupCycles = 2;

    // store at which request startup happened
    LastRequest = _status.PowerRequestPerc;
  }

  // handle according to state
  if (StartupCycles > 0)
  {
    // full power
    StartupCycles--;
    _status.CurrentPowerPwm = 255;
  }
  else
  {
    // apply fan power with respect to parameters
    // make 0% == 0 PWM
    _status.CurrentPowerPwm = _status.PowerRequestPerc == 0
                                  ? 0
                                  : map(_status.PowerRequestPerc, 0, 100, _parameters.PMin, _parameters.PMax);
  }
  analogWrite(PWM_PIN, _status.CurrentPowerPwm);

  // printouts
  Serial.println(".");
}

void waitWifiConnected(unsigned long timeOutMs = (unsigned long)-1)
{
  Serial.print("Wait for Wifi");
  auto const startOfCycle = millis();
  while (WiFi.status() != WL_CONNECTED)
  {
    digitalWrite(LED_BUILTIN, LOW);
    delay(500); // this is important to yield for the watchdog
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.print(".");

    if ((millis() - startOfCycle) > timeOutMs)
      return;
  }
}

/// @brief LOOP
void loop()
{
  // blink
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);

  // handle regular things in a busy loop
  _server.handleClient();
  ArduinoOTA.handle();

  // cycle length
  static CycleLimit::CycleLimit cycle1s{CYCLE_TIME_MS};
  if (cycle1s.IsCycleCooledDown())
    cycle1Hz();

  // check wifi status every 5s
  static CycleLimit::CycleLimit cycle5s{CYCLE_TIME_MS};
  if (cycle5s.IsCycleCooledDown())
  {
    static bool isConnected = false;
    if (WiFi.status() == WL_CONNECTED)
    {
      isConnected = true;
    }
    else
    {
      if (isConnected)
      {
        isConnected = false;
        _status.NumReconnects += 1;
      }
      WiFi.reconnect();
      waitWifiConnected(5000); // do not wait longer than 5000ms!
    }
  }

  digitalWrite(LED_BUILTIN, LOW);
}
