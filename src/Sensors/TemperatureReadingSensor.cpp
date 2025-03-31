#include "TemperatureReadingSensor.h"

TemperatureReadingSensor::TemperatureReadingSensor(uint8_t pin)
    : wireBus(pin), ds18b20(&wireBus) {}

void TemperatureReadingSensor::begin()
{
    ds18b20.begin();
}

float TemperatureReadingSensor::getReadingFloat()
{
    ds18b20.requestTemperatures();
    float temperature = ds18b20.getTempCByIndex(0);
    // return temperature != DEVICE_DISCONNECTED_C ? temperature : NAN;
    return temperature;
}