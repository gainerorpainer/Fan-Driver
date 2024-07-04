#pragma once

#include <cinttypes>

#include <ArduinoJson.h>

namespace Status
{
    struct Status
    {
        float HeaterTemp;

        float RoomTemp;

        /// @brief Power in PWM
        int CurrentPowerPwm = 0;

        /// @brief Power in 0..255
        uint8_t PowerRequestPerc = 0;

        /// @brief if manual override, to which value to override
        uint8_t ManualPowerPerc = 0;

        /// @brief if >0, the seconds left in manual mode
        int ManualSecondsLeft = 0;

        /// @brief How many times a reconnect to wifi happenend
        int NumReconnects = 0;
    };

    int serialize(Status const &input, String &buffer);
}
