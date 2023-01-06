#pragma once

namespace Parameters
{
    /// @brief Global parameters (can be changed easily)
    struct Parameters
    {
        /// @brief The max room temperature after which fan control is shut off
        float MaxRoomTemp = 20;

        /// @brief The minimal delta between room and heater after which fan control is turned on
        float MinTempDelta = 5;

        /// @brief Temperature-Delta at which the lowest duty cycle is applied
        float TempLowestPWM = 0;

        /// @brief Temperature-Delta at which the highest duty cycle is applied
        float TempHighestPWM = 10;
    };

    /// @brief Turns parameters into a comma separates, dotted float string
    /// @param input the parameters to serialze
    /// @param buffer will be set to an allocated char array
    /// @return the length of the string
    int Serialize(Parameters const &input, char *&buffer);

    /// @brief Attempts to parse aa comma separates, dotted float string
    /// @param input the string to parse
    /// @param output unchanged or if true is returned, the parsed data
    /// @return true if successful
    bool TryParse(char *input, Parameters &output);
}
