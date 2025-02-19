#pragma once

#include <CycleLimit.h>

#include "tasks.h"

namespace codegen::Tasks
{
    static inline void call_once()
    {
        ::Tasks::controlFans();
        ::Tasks::logHistory();
        ::Tasks::alivePing();
    }

    static inline void loop()
    {
        CycleLimit::Time_t const now = millis();
        
        static CycleLimit::CycleLimit controlFans_cl_limit{1000};
        if (controlFans_cl_limit.IsCycleCooledDown(now))
        	::Tasks::controlFans();
        static CycleLimit::CycleLimit logHistory_cl_limit{83};
        if (logHistory_cl_limit.IsCycleCooledDown(now))
        	::Tasks::logHistory();
        static CycleLimit::CycleLimit alivePing_cl_limit{60000};
        if (alivePing_cl_limit.IsCycleCooledDown(now))
        	::Tasks::alivePing();
    }
}
