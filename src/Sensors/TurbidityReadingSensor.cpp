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

// Nueva función: convierte voltaje a NTU
float TurbidityReadingSensor::voltageToNTU(float voltage)
{
    // Fórmula empírica para el sensor de turbidez
    float ntu = -1120.4 * voltage * voltage + 5742.3 * voltage - 4352.9;

    // Asegurar que el valor no sea negativo
    if (ntu < 0) ntu = 0;

    return ntu;
}

String TurbidityReadingSensor::getReading()
{
    int sensorValue = getReadingInt();
    float voltage = getReadingFloat();
    float ntu = voltageToNTU(voltage);

    return "Raw: " + String(sensorValue) +
           " | Voltage: " + String(voltage, 2) + " V" +
           " | NTU: " + String(ntu, 2);
}
