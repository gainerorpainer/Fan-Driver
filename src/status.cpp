#include "status.h"

namespace Status
{
    constexpr int JSON_HEAP = 1024;

    int Serialize(Status const &input, String &buffer)
    {
        // reset buffer just in case
        buffer.clear();

        DynamicJsonDocument doc{JSON_HEAP};

        doc["heaterTemp"] = input.HeaterTemp;
        doc["roomTemp"] = input.RoomTemp;
        doc["currentPowerPwm"] = input.CurrentPowerPwm;
        doc["currentPowerPerc"] = input.PowerRequestPerc;
        doc["manualPowerPerc"] = input.ManualPowerPerc;
        doc["manualSecondsLeft"] = input.ManualSecondsLeft;
        doc["numReconnects"] = input.NumReconnects;

        doc["upTimeSeconds"] = millis() / 1000;
        doc["freeHeap"] = ESP.getFreeHeap();

        return serializeJson(doc, buffer);
    }

}