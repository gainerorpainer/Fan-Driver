#include "html.h"

#include <los.h>

#include "parameters.h"
#include "storage.h"
#include "static_html_mainpage.h"
#include "static_html_favicon.h"

namespace Html
{
    ESP8266WebServer *_server = nullptr;
    Parameters::Parameters *_parameters = nullptr;
    Status::Status *_status = nullptr;

    void setup(ESP8266WebServer &server, Parameters::Parameters &parameters, Status::Status &status)
    {
        _server = &server;
        _parameters = &parameters;
        _status = &status;
    }

    void onGetHome()
    {
        _server->send(200, "text/html", STATIC_HTML_MAINPAGE);
    }

    void onGetFavicon()
    {
        _server->send(200, "image/x-icon", STATIC_HTML_FAVICON_CONTENT, sizeof(STATIC_HTML_FAVICON_CONTENT));
    }

    void onGetStatus()
    {
        String content;
        size_t const contentLength = Status::Serialize(*_status, content);
        _server->send(200, "application/json", content.c_str(), contentLength);
        return;
    }

    void onGetOrPostParameters()
    {
        if (_server->method() == HTTP_GET)
        {
            String content;
            size_t const contentLength = Parameters::Serialize(*_parameters, content);

            _server->send(200, "application/json", content.c_str(), contentLength);
            return;
        }

        if (_server->method() == HTTP_POST)
        {
            // try find FORM parameter
            if (!_server->hasArg("parameters"))
            {
                _server->send(403, "text/plain", "Missing FORM parameter: \"parameters\"");
                return;
            }

            if (!Parameters::TryParse(_server->arg("parameters").c_str(), *_parameters))
            {
                _server->send(403, "text/plain", "Bad JSON");
                return;
            }

            LOS::_Storage.setParameters(*_parameters);
            LOS::_Storage.storeToEEprom();

            _server->send(200, "text/plain", "OK");
            return;
        }

        _server->send(403, "text/plain", "Use GET or POST");
    }

    void onManualOverride()
    {
        if (_server->method() != HTTP_POST)
        {
            _server->send(403, "text/plain", "Use POST");
            return;
        }

        // try find FORM parameter
        if (!_server->hasArg("percent"))
        {
            _server->send(403, "text/plain", "Missing FORM parameter: \"percent\"");
            return;
        }

        int const parsedPercent = atoi(_server->arg("percent").c_str());
        if (parsedPercent < 0 || parsedPercent > 100)
        {
            _server->send(403, "text/plain", "Bad \"percent\" parameter value: valid range is 0..100");
            return;
        }

        int const parsedSeconds = _server->hasArg("seconds") ? atoi(_server->arg("seconds").c_str()) : 60;
        if (parsedSeconds < 0 || parsedSeconds > 3600)
        {
            _server->send(401, "text/plain", "Bad \"seconds\" parameter value: valid range is 0..3600");
            return;
        }

        // set override for the next 30 seconds
        _status->ManualPowerPerc = parsedPercent;
        _status->ManualSecondsLeft = parsedSeconds;

        _server->send(200, "text/plain", "OK");
        return;
    }
}