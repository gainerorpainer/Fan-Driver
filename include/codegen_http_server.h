#pragma once

#include <WString.h>

#include <los.h>

#include "html.h"

namespace codegen::Http_Server
{
    constexpr int BUILDNUMBER = 0;

    static inline void setup()
    {
        // GET /version
        LOS::_HttpServer.on("/version", []()
                            { _HttpServer.send(200, "text/plain", String{VERSION} + "_" + String{BUILDNUMBER}); });

        LOS::_HttpServer.on("/", ::Html::onGetHome);
        LOS::_HttpServer.on("/favicon.ico", ::Html::onGetFavicon);
        LOS::_HttpServer.on("/status", ::Html::onGetStatus);
        LOS::_HttpServer.on("/parameters", ::Html::onGetOrPostParameters);
        LOS::_HttpServer.on("/manual", ::Html::onManualOverride);
    }
}
