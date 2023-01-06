#include "html.h"

#include "parameters.h"

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
        _server->send(200, "text/plain", "HOME");
    }

    void onGetStatus()
    {
        char *content;
        size_t const contentLength = Status::Serialize(*_status, content);
        _server->send(200, "application/json", content, contentLength);
        return;
    }

    void onGetOrPostSettings()
    {
        if (_server->method() == HTTP_GET)
        {
            char *content;
            size_t const contentLength = Parameters::Serialize(*_parameters, content);

            _server->send(200, "application/json", content, contentLength);
            return;
        }

        if (_server->method() == HTTP_POST)
        {
            _server->send(200, "text/plain", "OK");
            return;
        }

        _server->send(403, "text/plain", "BAD METHOD");
    }

}