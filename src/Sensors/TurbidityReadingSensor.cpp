#include "TurbidityReadingSensor.h"

TurbidityReadingSensor::TurbidityReadingSensor(int pin) : sensorPin(pin)
{
}

void TurbidityReadingSensor::setup()
{
    pinMode(sensorPin, INPUT);
}

void TurbidityReadingSensor::calibrate()
{
    // Implementar calibración aquí si es necesario
}

String TurbidityReadingSensor::resultCalibration()
{
    return "Calibración no implementada";
}

int TurbidityReadingSensor::getReadingInt()
{
    return analogRead(sensorPin);
}

float TurbidityReadingSensor::getReadingFloat()
{
    int sensorValue = analogRead(sensorPin);
    return sensorValue * (5.0 / 1024.0);
}

String TurbidityReadingSensor::getReading()
{
    int sensorValue = getReadingInt();
    float voltage = getReadingFloat();

    return "Raw: " + String(sensorValue) + " | Voltage: " + String(voltage) + " V";
}
