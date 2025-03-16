#include "ConductivityReadingSensor.h"

ConductivityReadingSensor::ConductivityReadingSensor(int pin) : sensorPin(pin)
{
}

void ConductivityReadingSensor::setup()
{
    pinMode(sensorPin, INPUT);
}

String ConductivityReadingSensor::getReading()
{
    int sensorValue = getReadingInt();
    float voltage = getReadingFloat();

    String result = "Valor del sensor: " + String(sensorValue);
    result += "  - Voltaje: " + String(voltage) + " V";

    return result;
}

int ConductivityReadingSensor::getReadingInt()
{
    return analogRead(sensorPin);
}

float ConductivityReadingSensor::getReadingFloat()
{
    int sensorValue = analogRead(sensorPin);
    float voltage = sensorValue * (5.0 / 1023.0);
    return voltage;
}
