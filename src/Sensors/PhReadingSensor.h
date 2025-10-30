#include <Arduino.h>
#pragma once

enum CalibrationVoltage
{
    VOL_4,
    VOL_6
};

class PhReadingSensor
{
public:
    PhReadingSensor(int analogPin);
    float calibrate(CalibrationVoltage voltage);
    void setVoltage(CalibrationVoltage type, float voltage);
    void calculateCalibration();
    String resultCalibration();
    String getReading();
    float getReadingFloat();

private:
    int ANALOG_PIN;
    float vol4, vol6, slope, offset;
    float readVoltage();
};
