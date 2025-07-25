#include <Arduino.h>
#pragma once

struct Config
{
    char apiKey[300];
    float calibrationVol4;
    float calibrationVol6;
    char wifiSSID[100];
    char wifiPassword[100];
};

class ConfigStoredROM
{
private:
    static const int EEPROM_START = 0;
    static Config config;
    static bool loaded;
    static void saveToEEPROM();

public:
    static void setConfig(Config config);
    static Config getConfig();
    static void setApiKey(String apiKey);
    static void setCalibrationVol4(float calibrationVol4);
    static void setCalibrationVol6(float calibrationVol6);
    static void setWifiSSID(String wifiSSID);
    static void setWifiPassword(String wifiPassword);
    static bool isValidString(const char *str, size_t maxLen);
    static bool isValidJWT(const char *jwt, size_t maxLen);
    static bool isValidFloat(float value);
};
