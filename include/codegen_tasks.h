#pragma once

#include "tasks.h"

namespace codegen::Tasks
{
    inline static void loop()
    {
        ::Tasks::cycle1Hz();
    }
}
