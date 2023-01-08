#include "storage.h"

#include <EEPROM.h>

namespace Storage
{

    void Setup()
    {
        EEPROM.begin(sizeof(Parameters::Parameters));
    }

    Parameters::Parameters Load()
    {
        Parameters::Parameters result;
        EEPROM.get(0, result);
        return result;
    }

    void Store(Parameters::Parameters const &parameters)
    {
        EEPROM.put(0, parameters);
        EEPROM.commit();
    }
}