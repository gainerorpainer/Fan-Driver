#pragma once

#include <CycleLimit.h>

#include "tasks.h"

namespace codegen::Tasks
{
    inline static void loop()
    {
        ::Tasks::cycle1Hz();
    }
}
