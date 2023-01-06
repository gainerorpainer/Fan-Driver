#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#include "inputs.h"
#include "parameters.h"
#include "status.h"
#include "html.h"

// #define FEATURE_TEMPINPUTS
#define FEATURE_WIFI

/// @brief used to control fan
constexpr byte PWM_PIN = 9;

/// @brief wifi data
const struct
{
  const char *Ssid = "Welahn24";
  const char *Password = "34200359922680323403";
  const char *HostName = "FanControlDriver";
} WIFI_SERVER_SETUP;

// static publics
Parameters::Parameters _parameters = {};
Status::Status _status = {};
ESP8266WebServer _server(80);

/// @brief Calc the PWM duty cycle
/// @param heaterTemp in ° C
/// @param roomTemp in ° C
/// @return 0..255
int CalcPWM(float heaterTemp, float roomTemp)
{
  // max room temp
  if (roomTemp >= _parameters.MaxRoomTemp)
    return 1;

  // min powercycle
  float const tempDelta = heaterTemp - roomTemp;
  if (tempDelta < _parameters.MinTempDelta)
    return 1;

  // LERP
  float pwm = map(tempDelta, _parameters.TempLowestPWM, _parameters.TempHighestPWM, 0, 255);

  // sanity check
  if (isnan(pwm))
    pwm = 0.0f;

  // cap
  return max(min((int)pwm, 255), 0);
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

  // activate LED
  pinMode(LED_BUILTIN, OUTPUT);

  // wifi setup
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SERVER_SETUP.Ssid, WIFI_SERVER_SETUP.Password);
  Serial.print("Wait for Wifi");
  while (WiFi.status() != WL_CONNECTED)
  {
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.print(".");
  }
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // DNS
  MDNS.begin(WIFI_SERVER_SETUP.HostName);

  // HTML ressource mapping
  _server.on("/", Html::onGetHome);
  _server.on("/status", Html::onGetStatus);
  _server.on("/settings", Html::onGetOrPostSettings);
  // 404
  _server.onNotFound([]()
                     { _server.send(404, "text/plain", "Not Found"); });
  // logging
  _server.addHook([](const String &method, const String &url, WiFiClient *client, ESP8266WebServer::ContentTypeFunction contentType)
                  { Serial.printf("HTML %s %s\n", method.c_str(), url.c_str());
                  return ESP8266WebServer::CLIENT_REQUEST_CAN_CONTINUE; });
  _server.begin();
}

/// @brief LOOP
void loop()
{
  // blink
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);

#if defined(FEATURE_TEMPINPUTS)
  // get temp readings
  auto const report = Inputs::Read();
  _status.HeaterTemp = report.Temp1;
  _status.RoomTemp = report.Temp2;

  // t1 = heater, t2 = room
  int const pwm_cycle = CalcPWM(report.Temp1, report.Temp2);

  Serial.print("Heater: ");
  Serial.print(_status.HeaterTemp, 1);
  Serial.print(", Room: ");
  Serial.print(_status.HeaterTemp, 1);
  Serial.print(", PWM0..255: ");
  Serial.println(pwm_cycle);

  // apply fan power
  // do not let duty cycle == 0, otherwise timer setup is discarded
  analogWrite(PWM_PIN, pwm_cycle);
#endif

#if defined(FEATURE_WIFI)
  // handle html server & dns broadcast
  MDNS.update();
  _server.handleClient();
#endif

  // cycle length
  delay(1000);
}
