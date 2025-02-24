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
        Serial.println("Setting voltage 4");
        vol4 = voltage;
        Serial.println(vol4);
    }
    else if (type == VOL_6)
    {
        Serial.println("Setting voltage 6");
        vol6 = voltage;
        Serial.println(vol6);
    }
}

void PhReadingSensor::calculateCalibration()
{
    slope = (6.86 - 4.01) / (vol6 - vol4); // Calcula la pendiente correctamente
    offset = 4.01 - (slope * vol4);        // Calcula el offset correctamente
}

String PhReadingSensor::resultCalibration()
{
    return String();
}

String PhReadingSensor::getReading()
{
    return String();
}

float PhReadingSensor::getReadingFloat()
{
    float voltage = readVoltage();
    return voltage * slope + offset;
}
