#pragma once

#include <WString.h>

#include <los.h>

#include "html.h"

namespace codegen::Http_Server
{
    static inline void setup()
    {
        // GET /version
        LOS::_HttpServer.on("/version", []()
                            { LOS::_HttpServer.send(200, "text/plain", String{"1.0-2024_11_05"}); });
        
        // GET /os
        LOS::_HttpServer.on("/os", []()
                            { LOS::_HttpServer.send(200, "application/json", LOS::Info::getInfoJson()); });

        /* USER CALLBACKS */
        LOS::_HttpServer.on("/", ::Html::onGetHome);
        LOS::_HttpServer.on("/favicon.ico", ::Html::onGetFavicon);
        LOS::_HttpServer.on("/status", ::Html::onGetStatus);
        LOS::_HttpServer.on("/parameters", ::Html::onGetOrPostParameters);
        LOS::_HttpServer.on("/manual", ::Html::onManualOverride);
    }
}
