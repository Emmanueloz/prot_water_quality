#pragma once
#define TemperatureReadingSensor_h

#include <OneWire.h>
#include <DallasTemperature.h>

class TemperatureReadingSensor
{
private:
    OneWire oneWire;           // Objeto OneWire
    DallasTemperature sensors; // Objeto DallasTemperature
    float getTemperature();    // Lectura de temperatura

public:
    TemperatureReadingSensor(uint8_t pin); // Constructor
    void begin();                          // Inicialización
    float readTemperatureC();              // Obtener temperatura en °C
};
