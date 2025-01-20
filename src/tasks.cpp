#include "tasks.h"

#include <Arduino.h>

#include <CycleLimit.h>

#include "inputs.h"

namespace Tasks
{
    // globals
    CircularBuffer<HistoryDataPoint, 60 * 24> MinutesReport;
    SubMinuteHistory SubMinute;

    // statics
    Parameters::Parameters *_parameters = nullptr;
    Status::Status *_status = nullptr;

    /// @brief Calc the PWM duty cycle
    /// @param heaterTemp in ° C
    /// @param roomTemp in ° C
    /// @return 0.0 to 100.0
    static inline float CalcFanPowerPerc(float heaterTemp, float roomTemp)
    {
        // heaters are hot enough?
        if (heaterTemp < _parameters->THeatMin)
            return 0;

        // 100 % region?
        float const tRoomMinLerpBound = _parameters->TRoomMin - 1;
        if (roomTemp < tRoomMinLerpBound)
            return 100;

        // 0% region?
        if (roomTemp > _parameters->TRoomMin)
            return 0;

        // LERP within the interval [TRoomMin - 1; TRoomMin]
        // increase integer precision
        float pwm = map((int)(100.0f * roomTemp), (int)(100.0f * tRoomMinLerpBound), (int)(100.0f * _parameters->TRoomMin), 0, 100);

        // sanity check & cap
        return isnan(pwm) ? 100 : max(min(pwm, 100.0f), 0.0f);
    }

    void setup(Parameters::Parameters *parameters, Status::Status *status)
    {
        _parameters = parameters;
        _status = status;

        Inputs::Setup();

        // set fast-PWM to mid frequency of 4k
        analogWriteFreq(4000);
    }

    bool SubMinuteHistory::PushDatapoint(float heater, float room)
    {
        _HeaterAvg = (_HeaterAvg * _SubMinuteCounter + heater) / (_SubMinuteCounter + 1);
        _RoomAvg = (_RoomAvg * _SubMinuteCounter + room) / (_SubMinuteCounter + 1);
        _SubMinuteCounter++;
        return (_SubMinuteCounter >= (60 * 1000) / LOG_HISTORY_INTERVAL_MS);
    }

    void SubMinuteHistory::Reset()
    {
        _SubMinuteCounter = _RoomAvg = _HeaterAvg = 0;
    }

    HistoryDataPoint SubMinuteHistory::GetDataPoint()
    {
        return HistoryDataPoint{.HeaterTemp{_HeaterAvg}, .RoomTemp{_HeaterAvg}};
    }

    void controlFans()
    {
        // get temp readings
        auto const report = Inputs::Read();
        _status->HeaterTemp = report.Temp1;
        _status->RoomTemp = report.Temp2;

        // t1 = heater, t2 = room
        _status->PowerRequestPerc = CalcFanPowerPerc(report.Temp1, report.Temp2);

        // manual override?
        if (_status->ManualSecondsLeft > 0)
        {
            // tick down!
            _status->ManualSecondsLeft -= 1;
            _status->PowerRequestPerc = _status->ManualPowerPerc;
        }

        // detect that a startup is necessary
        static int StartupCycles = 0;
        const int FANKICKER_MINUTES_COOLDOWN = 60; // limiter for 60 minutes
        // minutes -> seconds -> millis
        static CycleLimit::CycleLimit limitStartups{1000 * 60 * FANKICKER_MINUTES_COOLDOWN};
        // do not make startups too often, unless the last request was "stopped"
        if (limitStartups.IsCycleCooledDown())
            // add startup cycles
            StartupCycles = 1;

        // handle according to state
        if (StartupCycles > 0)
        {
            // full power
            StartupCycles--;
            _status->CurrentPowerPwm = 100;
        }
        else
        {
            // apply fan power with respect to parameters
            // make 0% == 0 PWM
            _status->CurrentPowerPwm = _status->PowerRequestPerc == 0
                                           ? 0
                                           : map(_status->PowerRequestPerc, 0, 100, _parameters->PMin, _parameters->PMax);
        }
        analogWrite(PWM_PIN, _status->CurrentPowerPwm);

        // printouts
        Serial.println(".");
    }

    void logHistory()
    {
        // get temp readings
        auto const report = Inputs::Read();

        // push to sub-minute history
        if (SubMinute.PushDatapoint(report.Temp1, report.Temp2))
        {
            // push to minute history
            MinutesReport.Enqueue(SubMinute.GetDataPoint());
            SubMinute.Reset();
        }
    }
}
