#pragma once

#include <cinttypes>

#include <ArduinoJson.h>

#include "codegen_attributes.h"

namespace Status
{
    struct [[is_serializable_class(TYPE_STATUS)]] Status
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
    };
}
