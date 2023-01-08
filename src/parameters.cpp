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

    bool TryParse(char const *input, Parameters &output)
    {
        StaticJsonDocument<JSON_BUFFER_SIZE> doc;
        DeserializationError const error = deserializeJson(doc, input);
        if (error)
            return false;

        JsonVariant maxRoomTemp = doc["maxRoomTemp"];
        JsonVariant minTempDelta = doc["minTempDelta"];
        JsonVariant tempLowestPwm = doc["tempLowestPwm"];
        JsonVariant tempHighestPwm = doc["tempHighestPwm"];

        if (maxRoomTemp.isNull() || minTempDelta.isNull() || tempLowestPwm.isNull() || tempHighestPwm.isNull())
            return false;

        output.MaxRoomTemp = maxRoomTemp;
        output.MinTempDelta = minTempDelta;
        output.TempLowestPWM = tempLowestPwm;
        output.TempHighestPWM = tempHighestPwm;
        return true;
    }

}