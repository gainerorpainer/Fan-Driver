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

/// @brief used to control fan
constexpr byte PWM_PIN = D8;

/// @brief Main loop cycle time
constexpr int CYCLE_TIME_MS = 1000;

/// @brief wifi data
const struct
{
  const char *Ssid = "Welahn24";
  const char *Password = "34200359922680323403";
} WIFI_SERVER_SETUP;

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

  // set fast-PWM to highest possible frequency of 40k
  analogWriteFreq(40000);

  // setup modules
  Inputs::Setup();
  Html::setup(_server, _parameters, _status);
  Storage::Setup();

  // activate LED
  pinMode(LED_BUILTIN, OUTPUT);

  // load parameters
  if (!Storage::Load(_parameters))
  // no storage found
  {
    Serial.println("Storage empty, generating...");

    _parameters = Parameters::Parameters();

    // watch out for string length!
    sprintf(_parameters.HostName, "FanDriver_%i", (int)random(0, 1000));

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
  ArduinoOTA.setHostname(_parameters.HostName);
  ArduinoOTA.begin(true); // useMDNS

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

  // set watchdog to 2 seconds since modules block relatively long
  ESP.wdtDisable();
  ESP.wdtEnable(2000);
}

void cycle1Hz()
{
  // get temp readings
  auto const report = Inputs::Read();
  _status.HeaterTemp = report.Temp1;
  _status.RoomTemp = report.Temp2;

  // manual override?
  if (_status.ManualSecondsLeft > 0)
  {
    // tick down!
    _status.ManualSecondsLeft -= 1;

    _status.CurrentPowerPerc = _status.ManualPowerPerc;
  }
  else
  {
    // t1 = heater, t2 = room
    _status.CurrentPowerPerc = CalcFanPowerPerc(report.Temp1, report.Temp2);
  }

  // apply fan power with respect to parameters
  // make use of higher integer precision
  // make 0% == 0 PWM
  _status.CurrentPowerPwm = _status.CurrentPowerPerc == 0 ? 0 : map(100 * _status.CurrentPowerPerc, 100 * (0), 100 * (100), _parameters.PMin, _parameters.PMax);
  analogWrite(PWM_PIN, _status.CurrentPowerPwm);

  // handle other things
  _status.UpTimeSeconds = (int)(UpTime::Handle() / 1000ul);

  // printouts
  Serial.printf("Heater: %0.1f, Room: %0.1f, P: %i\n", _status.HeaterTemp, _status.RoomTemp, _status.CurrentPowerPwm);
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
  static CycleLimit::CycleLimit cycleLimit{CYCLE_TIME_MS};
  if (cycleLimit.IsCycleCooledDown())
    cycle1Hz();

  digitalWrite(LED_BUILTIN, LOW);

  if (WiFi.status() != WL_CONNECTED)
  {
    WiFi.reconnect();
    busyWaitWifiConnected();
  }
}
