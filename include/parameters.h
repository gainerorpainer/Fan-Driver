#pragma once

#include <inttypes.h>

#include <ArduinoJson.h>

namespace Parameters
{
    /// @brief Global parameters (can be changed easily)
    struct Parameters
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

    /// @brief Turns parameters into a comma separates, dotted float string
    /// @param input the parameters to serialze
    /// @param buffer will be cleared and written to
    /// @return the length of the string
    int Serialize(Parameters const &input, String &buffer);

    /// @brief Attempts to parse aa comma separates, dotted float string
    /// @param input the string to parse
    /// @param output unchanged or if true is returned, the parsed data
    /// @return true if successful
    bool TryParse(char const *input, Parameters &output);
}
