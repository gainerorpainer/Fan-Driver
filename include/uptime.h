#pragma once

#include <Arduino.h>

namespace UpTime
{
    /// @brief Calculates ticks in 64 bit (basically never overflows, unlike millis() which overflows every 47 days). Must be called regularly!
    /// @return Milliseconds uptime
    uint64_t Handle();
}