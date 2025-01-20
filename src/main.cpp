#include <Arduino.h>

#include <los.h>

#include "parameters.h"
#include "status.h"
#include "tasks.h"
#include "codegen_tasks.h"
#include "codegen_http_server.h"

/// @brief Main loop cycle time
constexpr int CYCLE_TIME_MS = 1000;

// static publics
Parameters::Parameters _Parameters = {};
Status::Status _Status = {};

/// @brief SETUP
void setup()
{
  // os setup
  LOS::setup();
  codegen::Http_Server::setup();

  Tasks::setup(&_Parameters, &_Status);
  Html::setup(LOS::_HttpServer, _Parameters, _Status);
  if (!LOS::_Storage.getParameters(_Parameters))
    Serial.println("Could not load parameters, fall back to defaults");
  if (!_Parameters.ArePlausible())
  {
    Serial.println("Parameters are inplausible, fall back to defaults");
    LOS::_Storage.setParameters(Parameters::Parameters{});
    LOS::_Storage.storeToEEprom();
  }
}

/// @brief LOOP
void loop()
{
  // os loops
  LOS::loop();
  codegen::Tasks::loop();
}
