#include "TemperatureReadingSensor.h"

TempReader::TempReader()
    : wireBus(2), ds18b20(&wireBus), sensorOK(false) {}

void TempReader::begin()
{
    Serial.begin(9600);
    ds18b20.begin();
    checkSensor();
}

void TempReader::checkSensor()
{
    sensorOK = (ds18b20.getDS18Count() > 0);
    if (!sensorOK)
        Serial.println("¡Sensor no detectado!");
}

float TempReader::readTemp()
{
    ds18b20.requestTemperatures();
    float t = ds18b20.getTempCByIndex(0);
    return t != DEVICE_DISCONNECTED_C ? t : NAN;
}

void TempReader::monitor()
{
    static uint32_t lastRead = 0;

    if (millis() - lastRead >= 2000)
    {
        if (sensorOK)
        {
            float temp = readTemp();
            if (!isnan(temp))
            {
                Serial.print("Temperatura: ");
                Serial.print(temp);
                Serial.println(" °C");
            }
            else
            {
                Serial.println("Lectura inválida");
            }
        }
        lastRead = millis();
    }
}