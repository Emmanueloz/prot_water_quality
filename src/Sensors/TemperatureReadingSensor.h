#pragma once
#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

class TemperatureReadingSensor
{
public:
    TemperatureReadingSensor(uint8_t pin);
    void begin();
    float getReadingFloat();
    OneWire wireBus;
    DallasTemperature ds18b20;
};