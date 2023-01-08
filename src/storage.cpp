#include "storage.h"

#include <EEPROM.h>
#include <CRC.h>

namespace Storage
{
    void Setup()
    {
        EEPROM.begin(sizeof(Parameters::Parameters));
    }

    uint8_t _CrcOf(Parameters::Parameters const &input)
    {
        return crc8(reinterpret_cast<uint8_t const *>(&input), sizeof(input));
    }

    bool Load(Parameters::Parameters &output)
    {
        EEPROM.get(0, output);
        uint8_t const presentCrc = EEPROM.read(sizeof(output));

        return presentCrc == _CrcOf(output);
    }

    void Store(Parameters::Parameters const &parameters)
    {
        EEPROM.put(0, parameters);
        EEPROM.write(sizeof(parameters), _CrcOf(parameters));
        EEPROM.commit();
    }
}