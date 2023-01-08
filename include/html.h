#pragma once

#include <ESP8266WebServer.h>

#include "parameters.h"
#include "status.h"

namespace Html
{
    /// @brief Initializes module
    /// @param server Initialized server instance
    /// @param server Initialized parameter instance (for /parameters)
    /// @param server Initialized status instance (for /status)
    void setup(ESP8266WebServer &server, Parameters::Parameters &parameters, Status::Status &status);

    /// @brief Handles GET /
    void onGetHome();

    /// @brief Handles GET /status
    void onGetStatus();

    /// @brief Handles GET or POST /parameters
    void onGetOrPostParameters();
}
