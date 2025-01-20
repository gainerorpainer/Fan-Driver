#pragma once

#include <CycleLimit.h>

#include "tasks.h"

namespace codegen::Tasks
{
    static inline void call_once()
    {
        ::Tasks::controlFans();
    }

    static inline void loop()
    {
        CycleLimit::Time_t const now = millis();
        
        static CycleLimit::CycleLimit controlFans_cl_limit{1000};
        if (controlFans_cl_limit.IsCycleCooledDown(now))
        	::Tasks::controlFans();
    }
}
