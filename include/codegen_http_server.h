#pragma once

#include <los.h>

#include "html.h"

namespace codegen::Http_Server
{
    static inline void setup()
    {
        LOS::_HttpServer.on("/", ::Html::onGetHome);
        LOS::_HttpServer.on("/favicon.ico", ::Html::onGetFavicon);
        LOS::_HttpServer.on("/status", ::Html::onGetStatus);
        LOS::_HttpServer.on("/parameters", ::Html::onGetOrPostParameters);
        LOS::_HttpServer.on("/manual", ::Html::onManualOverride);
    }
}
