#include "storage.h"

#include <EEPROM.h>
#include <CRC.h>

namespace Storage
{
    void Setup()
    {
        // EEPROM contains Parameters PLUS CRC
        EEPROM.begin(sizeof(Parameters::Parameters) + 1);
    }

    byte _CrcOf(Parameters::Parameters const &input)
    {
        return calcCRC8(reinterpret_cast<byte const *>(&input), sizeof(input));
    }

    bool Load(Parameters::Parameters &output)
    {
        EEPROM.get(0, output);

        return EEPROM.read(sizeof(output)) == _CrcOf(output);
    }

    void Store(Parameters::Parameters const &parameters)
    {
        EEPROM.put(0, parameters);
        EEPROM.put(sizeof(parameters), _CrcOf(parameters));

        EEPROM.commit();
    }
}