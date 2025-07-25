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
    strncpy(config.apiKey, apiKey.c_str(), apiKey.length() + 1);
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

void ConfigStoredROM::setWifiSSID(String wifiSSID)
{
    strncpy(config.wifiSSID, wifiSSID.c_str(), 100);
    saveToEEPROM();
}

void ConfigStoredROM::setWifiPassword(String wifiPassword)
{
    strncpy(config.wifiPassword, wifiPassword.c_str(), 100);
    saveToEEPROM();
}

bool ConfigStoredROM::isValidString(const char *str, size_t maxLen)
{
    for (size_t i = 0; i < maxLen; ++i)
    {
        char c = str[i];
        if (c == '\0')
            return true; // fin de cadena normal
        if (c < 32 || c > 126)
            return false;
    }
    return false; // no se encontró null terminator dentro del límite
}

bool ConfigStoredROM::isValidJWT(const char *jwt, size_t maxLen)
{
    if (jwt == nullptr || jwt[0] == '\0')
    {
        Serial.println("JWT is null or empty");
        return false;
    }

    size_t len = strnlen(jwt, maxLen);
    if (len == 0 || len > maxLen)
    {
        Serial.print("JWT length: ");
        Serial.println(len);
        Serial.print("maxLen: ");
        Serial.println(maxLen);
        Serial.println("JWT length is invalid");
        return false;
    }

    // JWT debe tener al menos 2 puntos (3 partes separadas por .)
    int dots = 0;
    for (size_t i = 0; i < len; i++)
    {
        char c = jwt[i];
        // Serial.print(c);

        if (c == '.')
        {
            dots++;
        }
        else if (!((c >= 'A' && c <= 'Z') ||
                   (c >= 'a' && c <= 'z') ||
                   (c >= '0' && c <= '9') ||
                   c == '+' || c == '/' || c == '-' || c == '_'))
        {
            Serial.println("Invalid character in JWT");
            return false; // Carácter inválido para JWT
        }
    }

    return dots == 2; // JWT válido debe tener exactamente 2 puntos
}

bool ConfigStoredROM::isValidFloat(float value)
{
    Serial.println(value);
    Serial.println(isnan(value));
    Serial.println(isfinite(value));
    return !isnan(value) && isfinite(value) && value > 0.0 && value < 20.0;
}
