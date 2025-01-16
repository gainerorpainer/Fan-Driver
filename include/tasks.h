#pragma once

#include "parameters.h"
#include "status.h"

#include "codegen_attributes.h"

#include "circular_buffer.h"

namespace Tasks
{
    template <unsigned int OFFSET, unsigned int FACTOR>
    class TemperatureReading
    {
    private:
        uint16_t _Data;

    public:
        TemperatureReading() : _Data{0} {};
        TemperatureReading(float value) : _Data{uint16_t((value + (float)OFFSET) * (float)FACTOR)} {}

        float AsFloat() const
        {
            return _Data;
        }
    };

    struct HistoryDataPoint
    {
        using TReading = TemperatureReading<100, 10>;

        TReading HeaterTemp;
        TReading RoomTemp;
    };

    /// @brief used to control fan
    constexpr int PWM_PIN = D8;

    /// @brief Each datapoint corresponds to one minute reading
    extern CircularBuffer<HistoryDataPoint, 60 * 24> MinutesReport;

    void setup(Parameters::Parameters *parameters, Status::Status *status);

    [[task_with_interval(1000)]]
    void cycle1Hz();
}
