#pragma once

namespace Inputs
{
    /// @brief Combines all data gathered from connected inputs
    struct Report
    {
        /// @brief degrees
        float Temp1;

        /// @brief degrees
        float Temp2;
    };

    /// @brief Initializes this module (necessary)
    void Setup();

    /// @brief Gathers data from inputs
    /// @return a report
    Report Read();

}