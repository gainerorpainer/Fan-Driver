#pragma once

#include "parameters.h"

namespace Storage
{
    void Setup();

    bool Load(Parameters::Parameters &output);

    void Store(Parameters::Parameters const &parameters);
}
