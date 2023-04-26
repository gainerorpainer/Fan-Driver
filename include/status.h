#pragma once

#include <ArduinoJson.h>

namespace Status
{
    struct Status
    {
        float HeaterTemp;

        float RoomTemp;

        /// @brief Power in PWM
        byte CurrentPowerPwm = 0;

        /// @brief Power in 0..255
        byte CurrentPowerPerc = 0;

        /// @brief if manual override, to which value to override
        byte ManualPowerPerc = 0;

        /// @brief if >0, the seconds left in manual mode
        byte ManualSecondsLeft = 0;

        /// @brief How many times a reconnect to wifi happenend
        int NumReconnects = 0;
    };

    /// @brief Turns a status into a string
    /// @param input the status to serialze
    /// @param buffer will be cleared and written to
    /// @return the length of the string
    int Serialize(Status const &input, String &buffer);
}
