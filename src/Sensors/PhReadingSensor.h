#include <Arduino.h>
#pragma once

class PhReadingSensor
{
public:
    PhReadingSensor();
    void setup();
    void calibrate();
    String resultCalibration();
    String getReading();
    int getReadingInt();
};