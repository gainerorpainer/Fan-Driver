#pragma once

namespace Status
{
    struct Status
    {
        float HeaterTemp;

        float RoomTemp;

        // if manual override, to which value to override
        int ManualPowerPerc = 0;

        // if >0, the seconds left in manual mode
        int ManualSecondsLeft = 0;
    };

    /// @brief Turns a status into a string
    /// @param input the status to serialze
    /// @param buffer will be set to an allocated char array
    /// @return the length of the string
    int Serialize(Status const &input, char *&buffer);
}
