#include "ConfigStoredROM.h"
#include <EEPROM.h>

Config ConfigStoredROM::config;
bool ConfigStoredROM::loaded = false;

void ConfigStoredROM::saveToEEPROM()
{
    EEPROM.put(EEPROM_START, config);
}

void ConfigStoredROM::setConfig(Config newConfig)
{
    config = newConfig;
    saveToEEPROM();
}

Config ConfigStoredROM::getConfig()
{
    if (!loaded)
    {
        EEPROM.get(EEPROM_START, config);
        loaded = true;
    }

    return config;
}

void ConfigStoredROM::setApiKey(String apiKey)
{
    strncpy(config.apiKey, apiKey.c_str(), 100);
    saveToEEPROM();
}

void ConfigStoredROM::setCalibrationVol4(float calibrationVol4)
{
    config.calibrationVol4 = calibrationVol4;
    saveToEEPROM();
}

void ConfigStoredROM::setCalibrationVol6(float calibrationVol6)
{
    config.calibrationVol6 = calibrationVol6;
    saveToEEPROM();
}
