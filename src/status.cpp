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
        doc["currentPowerPerc"] = input.CurrentPowerPerc;
        doc["manualPowerPerc"] = input.ManualPowerPerc;
        doc["manualSecondsLeft"] = input.ManualSecondsLeft;
        doc["upTimeSeconds"] = input.UpTimeSeconds;
        return serializeJson(doc, buffer);
    }

}