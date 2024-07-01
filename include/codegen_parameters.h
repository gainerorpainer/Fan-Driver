#pragma once

#include <ArduinoJson.h>

#include "parameters.h"

namespace codegen::Parameters
{
    /// @brief Turns parameters into json
    /// @param input the parameters to serialze
    /// @param buffer will be cleared and written to
    /// @return the length of the string
    template <typename T>
    static inline int serialize(T const &in, String &out)
    {
        // reset buffer just in case
        out.clear();
        JsonDocument doc{};

        doc["PMin"] = in.PMin;
        doc["PMax"] = in.PMax;
        doc["TRoomMin"] = in.TRoomMin;
        doc["THeatMin"] = in.THeatMin;

        return serializeJson(doc, out);
    }

    /// @brief Attempts to parse as json
    /// @param input the string to parse
    /// @param output unchanged or if true is returned, the parsed data
    /// @return true if successful
    template <typename T>
    static inline bool tryParse(char const *in, T &out)
    {
        JsonDocument doc{};
        DeserializationError const error = deserializeJson(doc, in);
        if (error)
            return false;

        JsonVariant PMin = doc["PMin"];
        JsonVariant PMax = doc["PMax"];
        JsonVariant TRoomMin = doc["TRoomMin"];
        JsonVariant THeatMin = doc["THeatMin"];
        
        if (PMin.isNull() || PMax.isNull() || TRoomMin.isNull() || THeatMin.isNull())
        	return false;
        
        out.PMin = PMin;
        out.PMax = PMax;
        out.TRoomMin = TRoomMin;
        out.THeatMin = THeatMin;

        return true;
    }
}
