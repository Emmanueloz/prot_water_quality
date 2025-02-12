#include <Arduino.h>
#pragma once

class PhReadingSensor
{
public:
    PhReadingSensor(int analogPin);
    void calibrate(CalibrationVoltage voltage);
    void calculateCalibration();
    String resultCalibration();
    String getReading();
    float getReadingFloat();

private:
    int ANALOG_PIN;
    float vol4, vol6, slope, offset;
    float readVoltage();
};

enum CalibrationVoltage
{
    VOL_4,
    VOL_6
};