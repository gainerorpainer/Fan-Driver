#include "uptime.h"

namespace UpTime
{

    static uint32_t _LowerDigit = 0;
    static uint32_t _UpperDigit = 0;

    uint64_t Handle()
    {
        auto const now = millis();

        // overflow detection (~47days)
        if (now < _LowerDigit)
            _UpperDigit++;

        _LowerDigit = now;

        // assemble number
        return ((uint64_t)_UpperDigit << sizeof(_UpperDigit)) + (uint64_t)_LowerDigit;
    }
}
