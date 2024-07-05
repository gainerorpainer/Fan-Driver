#pragma once

#include <inttypes.h>

#include <ArduinoJson.h>

#include "codegen_attributes.h"

namespace Parameters
{
    /// @brief Global parameters (can be changed easily)
    struct [[is_serializable_class(SERIALIZABLE_AND_PARSABLE)]] Parameters
    {
        /// @brief The lowest power (in PWM) before the fans stop moving
        uint8_t PMin = 50;

        /// @brief The highest acceptable power (in PWM)
        uint8_t PMax = 255;

        /// @brief The min room temp which the control tries to reach
        float TRoomMin = 20;

        /// @brief The min heater temp at which control is enabled
        float THeatMin = 20;
    };
}
