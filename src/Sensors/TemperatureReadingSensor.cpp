#include "TemperatureReadingSensor.h"

// Constructor (inicializa bus OneWire y sensor)
TemperatureReadingSensor::TemperatureReadingSensor(uint8_t pin)
    : oneWire(pin), sensors(&oneWire) {}

// Inicializa el sensor
void TemperatureReadingSensor::begin()
{
    sensors.begin();
}

// Solicita y retorna la temperatura en °C
float TemperatureReadingSensor::readTemperatureC()
{
    sensors.requestTemperatures();
    return sensors.getTempCByIndex(0);
}