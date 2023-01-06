#include "inputs.h"

#include <DHT.h>

// DHT11 at pin 2 & 3
DHT dht1(D1, DHT11);
DHT dht2(D2, DHT11);

namespace Inputs
{
    void Setup()
    {
        dht1.begin();
        dht2.begin();
    }

    Report Read()
    {
        Report result = {};
        result.Temp1 = dht1.readTemperature();
        result.Temp2 = dht2.readTemperature();
        return result;
    }

}