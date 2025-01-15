#pragma once

#include "parameters.h"
#include "status.h"

#include "codegen_attributes.h"

#include "history_buffer.h"

namespace Tasks
{
    /// @brief used to control fan
    constexpr int PWM_PIN = D8;

    extern HistoryBuffer<Inputs::Report, 60> InputsHistory;

    void setup(Parameters::Parameters *parameters, Status::Status *status);

    [[task_with_interval(1000)]]
    void cycle1Hz();
}
