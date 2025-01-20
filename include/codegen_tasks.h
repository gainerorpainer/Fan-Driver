#pragma once

#include <CycleLimit.h>

#include "tasks.h"

namespace codegen::Tasks
{
    static inline void call_once()
    {
        ::Tasks::cycle1Hz();
    }

    static inline void loop()
    {
        static CycleLimit::CycleLimit cycle1Hz_cl_limit{1000};
        if (cycle1Hz_cl_limit.IsCycleCooledDown())
        	::Tasks::cycle1Hz();
    }
}
