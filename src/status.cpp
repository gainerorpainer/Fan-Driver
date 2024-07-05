#include "status.h"

#include <los.h>

namespace Status
{
    void serialize_debug_info(JsonDocument &doc)
    {
        doc["NumReconnects"] = LOS::_NumWifiReconnects;
        doc["UpTimeSeconds"] = millis() / 1000;
        doc["FreeHeap"] = ESP.getFreeHeap();
    }
}