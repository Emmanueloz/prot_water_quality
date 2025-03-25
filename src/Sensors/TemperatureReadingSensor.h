#pragma once
#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

class TempReader
{
public:
    TempReader();
    void begin();   // Combina inicialización y chequeo
    void monitor(); // Maneja lectura y despliegue

private:
    OneWire wireBus;
    DallasTemperature ds18b20;
    bool sensorOK;

    float readTemp();
    void checkSensor();
};