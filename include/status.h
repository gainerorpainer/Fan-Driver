#pragma once

namespace Status
{
    struct Status
    {
        float HeaterTemp;

        float RoomTemp;
    };

    /// @brief Turns a status into a string
    /// @param input the status to serialze
    /// @param buffer will be set to an allocated char array
    /// @return the length of the string
    int Serialize(Status const &input, char *&buffer);
}
