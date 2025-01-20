#pragma once

#include "parameters.h"
#include "status.h"
#include "circular_buffer.h"

#include "codegen_attributes.h"

namespace Tasks
{
    /// @brief used to control fan
    constexpr int PWM_PIN = D8;

    /// @brief Interval for logHistory(), make sure to call task_with_interval with this value
    constexpr unsigned int LOG_HISTORY_INTERVAL_MS = 5000;

    /// @brief Fixed precision float with 16bit size
    /// @tparam BIAS which value is stored as '0' (aka lowest possible value)
    /// @tparam SUBDIVISIONS the number of fractions into which a value increment of 1 is divided (e.g. SUBDIVISIONS=5 corresponds to a precision of 0.2)
    template <int BIAS, int SUBDIVISIONS>
    class FixedFloat
    {
    private:
        uint16_t _Data;

    public:
        FixedFloat() : _Data{0} {};
        FixedFloat(float value) : _Data{(uint16_t)((value - (float)BIAS) * (float)SUBDIVISIONS)} {}

        constexpr float AsFloat() const
        {
            return (float)_Data / (float)SUBDIVISIONS + (float)BIAS;
        }

        /// @brief The lowest possible value without overflow
        constexpr float MinValue()
        {
            return (float)BIAS;
        }

        /// @brief The highest valid value
        constexpr float MaxValue()
        {
            return (float)UINT16_MAX / (float)SUBDIVISIONS + (float)BIAS;
        }
    };

    struct HistoryDataPoint
    {
        using TReading = FixedFloat<-100, 10>;

        TReading HeaterTemp;
        TReading RoomTemp;
    };

    class SubMinuteHistory
    {
    private:
        float _HeaterAvg = 0;
        float _RoomAvg = 0;
        unsigned int _SubMinuteCounter = 0;
    public:
        bool PushDatapoint(float heater, float room);

        void Reset();

        HistoryDataPoint GetDataPoint();
    };

    /// @brief Each datapoint corresponds to one minute temperature readings
    extern CircularBuffer<HistoryDataPoint, 60 * 24> MinutesReport;

    extern SubMinuteHistory SubMinute;

    /// @brief Mandatory setup
    /// @param parameters pointer where parameters are stored
    /// @param status pointer where status is stored
    void setup(Parameters::Parameters *parameters, Status::Status *status);

    [[task_with_interval(1000)]]
    void controlFans();

    /// @brief Make sure to call this with LOG_HISTORY_INTERVAL_MS!
    [[task_with_interval(5000/60)]]
    void logHistory();
}
