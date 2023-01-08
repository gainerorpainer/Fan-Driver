#include "html.h"

#include "parameters.h"
#include "control_page_html.h"
#include "storage.h"

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
        _server->send(200, "text/html", CONTROL_PAGE_HTML);
    }

    void onGetStatus()
    {
        char *content;
        size_t const contentLength = Status::Serialize(*_status, content);
        _server->send(200, "application/json", content, contentLength);
        return;
    }

    void onGetOrPostParameters()
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

            Storage::Store(*_parameters);

            _server->send(200, "text/plain", "OK");
            return;
        }

        _server->send(403, "text/plain", "Use GET or POST");
    }

}