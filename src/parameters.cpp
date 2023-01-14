#include "parameters.h"

namespace Parameters
{
    // 64 should suffice according to https://arduinojson.org/v6/assistant
    constexpr size_t JSON_HEAP = 1024;

    int Serialize(Parameters const &input, String &buffer)
    {
        // reset buffer just in case
        buffer.clear();

        DynamicJsonDocument doc{JSON_HEAP};
        doc["pMin"] = input.PMin;
        doc["pMax"] = input.PMax;
        doc["tRoomMin"] = input.TRoomMin;
        doc["tHeatMin"] = input.THeatMin;
        doc["hostName"] = input.HostName;
        return serializeJson(doc, buffer);
    }

    bool TryParse(char const *input, Parameters &output)
    {
        DynamicJsonDocument doc{JSON_HEAP};
        DeserializationError const error = deserializeJson(doc, input);
        if (error)
            return false;

        JsonVariant pMin = doc["pMin"];
        JsonVariant pMax = doc["pMax"];
        JsonVariant tRoomMin = doc["tRoomMin"];
        JsonVariant tHeatMin = doc["tHeatMin"];
        JsonVariant hostName = doc["hostName"];

        if (pMin.isNull() || pMax.isNull() || tRoomMin.isNull() || tHeatMin.isNull() || hostName.isNull())
            return false;

        output.PMin = pMin;
        output.PMax = pMax;
        output.TRoomMin = tRoomMin;
        output.THeatMin = tHeatMin;

        // memcpy hostname with some boundary checking
        const char *hostNameCstr = doc["hostName"];
        memcpy(output.HostName, hostNameCstr, min(strlen(hostNameCstr), (size_t)sizeof(output.HostName)));

        return true;
    }

}