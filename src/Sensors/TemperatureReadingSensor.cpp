#include "TemperatureReadingSensor.h"

TemperatureReadingSensor::TemperatureReadingSensor()
    : wireBus(2), ds18b20(&wireBus) {}

void TemperatureReadingSensor::begin()
{
    Serial.begin(9600);
    ds18b20.begin();
}

float TemperatureReadingSensor::getReadingFloat()
{
    ds18b20.requestTemperatures();
    float temperature = ds18b20.getTempCByIndex(0);
    return temperature != DEVICE_DISCONNECTED_C ? temperature : NAN;
}