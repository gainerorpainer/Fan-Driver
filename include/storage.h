#pragma once

#include "parameters.h"

namespace Storage
{
    void Setup();

    Parameters::Parameters Load();

    void Store(Parameters::Parameters const &parameters);
}
