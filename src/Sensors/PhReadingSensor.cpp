#include "PhReadingSensor.h"

PhReadingSensor::PhReadingSensor(int analogPin)
{
    ANALOG_PIN = analogPin;
}

float PhReadingSensor::readVoltage()
{
    int sensorValue = analogRead(ANALOG_PIN);
    float voltage = sensorValue * 5.0 / 1024.0;
    return voltage;
}

float PhReadingSensor::calibrate(CalibrationVoltage voltage)
{
    if (voltage == VOL_4)
    {
        Serial.println("Calibrating voltage 4");
        vol4 = readVoltage();
        return vol4;
    }
    else if (voltage == VOL_6)
    {
        Serial.println("Calibrating voltage 6");
        vol6 = readVoltage();
        return vol6;
    }
    return 0;
}

void PhReadingSensor::setVoltage(CalibrationVoltage type, float voltage)
{
    if (type == VOL_4)
    {
        vol4 = voltage;
    }
    else if (type == VOL_6)
    {
        vol6 = voltage;
    }
}

void PhReadingSensor::calculateCalibration()
{
    slope = (6.86 - 4.01) / (vol6 - vol4); // Calcula la pendiente correctamente
    offset = 4.01 - (slope * vol4);        // Calcula el offset correctamente
}

String PhReadingSensor::resultCalibration()
{
    // Implementar para devolver información útil sobre la calibración
    return "Slope: " + String(slope) + ", Offset: " + String(offset);
}

String PhReadingSensor::getReading()
{
    // Implementar para devolver el valor de pH como String
    float ph = getReadingFloat();
    return "pH: " + String(ph, 2); // 2 decimales
}

float PhReadingSensor::getReadingFloat()
{
    float voltage = readVoltage();
    return voltage * slope + offset;
}
