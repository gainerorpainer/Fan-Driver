#pragma once

#include <ESP8266WebServer.h>

#include "status.h"
#include "parameters.h"
#include "codegen_attributes.h"

namespace Html
{
    /// @brief Initializes module
    /// @param server Initialized server instance
    /// @param server Initialized parameter instance (for /parameters)
    /// @param server Initialized status instance (for /status)
    void setup(ESP8266WebServer &server, Parameters::Parameters &parameters, Status::Status &status);

    /// @brief Handles GET /
    [[http_server_bind_to("/")]]
    void onGetHome();

    /// @brief Handles GET /favicon.ico
    [[http_server_bind_to("/favicon.ico")]]
    void onGetFavicon();

    /// @brief Handles GET /status
    [[http_server_bind_to("/status")]]
    void onGetStatus();

    /// @brief Handles GET or POST /parameters
    [[http_server_bind_to("/parameters")]]
    void onGetOrPostParameters();

    /// @brief Handles POST /manual
    [[http_server_bind_to("/manual")]]
    void onManualOverride();
}
