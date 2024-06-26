#pragma once

#include "parameters.h"
#include "status.h"

#include "codegen_attributes.h"

namespace Tasks
{
    /// @brief used to control fan
    constexpr int PWM_PIN = D8;

    void setup(Parameters::Parameters *parameters, Status::Status *status);

    [[task_with_interval(1000)]]
    void cycle1Hz();
}
