#pragma once

#include <ArduinoJson.h>

#include "parameters.h"
#include "status.h"

namespace codegen::Serializable
{
    /// @brief Turns Parameters into json
    /// @param in the Parameters to serialze
    /// @param out will be cleared and written to
    /// @return the length of the string
    int serialize(::Parameters::Parameters const &in, String &out)
    {
        // reset buffer just in case
        out.clear();
        JsonDocument doc;
    
        doc["PMin"] = in.PMin;
        doc["PMax"] = in.PMax;
        doc["TRoomMin"] = in.TRoomMin;
        doc["THeatMin"] = in.THeatMin;
    
        // user extension code, if any
    
        return serializeJson(doc, out);
    }
    /// @brief Attempts to parse Parameters from json
    /// @param in the string to parse
    /// @param out unchanged or if true is returned, the parsed data
    /// @return true if successful
    bool tryParse(char const *in, ::Parameters::Parameters &out)
    {
        JsonDocument doc;
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
    
        // user extension code, if any
        // not implemented
    
        return true;
    }
    
    /// @brief Turns Status into json
    /// @param in the Status to serialze
    /// @param out will be cleared and written to
    /// @return the length of the string
    int serialize(::Status::Status const &in, String &out)
    {
        // reset buffer just in case
        out.clear();
        JsonDocument doc;
    
        doc["HeaterTemp"] = in.HeaterTemp;
        doc["RoomTemp"] = in.RoomTemp;
        doc["CurrentPowerPwm"] = in.CurrentPowerPwm;
        doc["PowerRequestPerc"] = in.PowerRequestPerc;
        doc["ManualPowerPerc"] = in.ManualPowerPerc;
        doc["ManualSecondsLeft"] = in.ManualSecondsLeft;
    
        // user extension code, if any
        ::Status::serialize_debug_info(doc);
    
        return serializeJson(doc, out);
    }
}
