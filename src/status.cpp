#include "status.h"

#include <ArduinoJson.h>

namespace Status
{
    // 32 should be ok according to https://arduinojson.org/v6/assistant
    constexpr size_t JSON_BUFFER_SIZE = 64;

    static char _jsonBuffer[JSON_BUFFER_SIZE];

    int Serialize(Status const &input, char *&buffer)
    {
        buffer = _jsonBuffer;
        StaticJsonDocument<JSON_BUFFER_SIZE> doc;
        doc["heaterTemp"] = input.HeaterTemp;
        doc["roomTemp"] = input.RoomTemp;
        return serializeJson(doc, _jsonBuffer);
    }

}