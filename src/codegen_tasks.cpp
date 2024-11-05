#include "codegen_tasks.h"

#include <CycleLimit.h>

#include "tasks.h"

namespace codegen::Tasks
{
    void loop()
    {
        static CycleLimit::CycleLimit cycle1Hz_cl_limit{1000};
        if (cycle1Hz_cl_limit.IsCycleCooledDown())
        	::Tasks::cycle1Hz();
    }
}
