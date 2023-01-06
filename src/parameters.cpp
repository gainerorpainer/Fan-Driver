#include "parameters.h"

#include <ArduinoJson.h>
namespace Parameters
{
    // 64 should suffice according to https://arduinojson.org/v6/assistant
    constexpr size_t JSON_BUFFER_SIZE = 128;

    char _jsonBuffer[JSON_BUFFER_SIZE];

    int Serialize(Parameters const &input, char *&buffer)
    {
        buffer = _jsonBuffer;
        StaticJsonDocument<JSON_BUFFER_SIZE> doc;
        doc["maxRoomTemp"] = input.MaxRoomTemp;
        doc["minTempDelta"] = input.MinTempDelta;
        doc["tempLowestPwm"] = input.TempLowestPWM;
        doc["tempHighestPwm"] = input.TempHighestPWM;
        return serializeJson(doc, _jsonBuffer);
    }

    bool TryParse(char *input, Parameters &output)
    {
        return false;
    }

}