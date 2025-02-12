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

void PhReadingSensor::calibrate(CalibrationVoltage voltage)
{

    if (voltage == VOL_4)
    {
        Serial.println("Calibrating voltage 4");
        vol4 = readVoltage();
    }
    else if (voltage == VOL_6)
    {
        Serial.println("Calibrating voltage 6");
        vol6 = readVoltage();
    }
}

void PhReadingSensor::calculateCalibration()
{
    slope = (6.86 - 4.01) / (vol6 - vol4);
    offset = vol4 - (4.01 - slope);
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
