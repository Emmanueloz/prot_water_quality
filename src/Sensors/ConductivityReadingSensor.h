#include <Arduino.h>
#pragma once

class ConductivityReadingSensor
{
public:
    ConductivityReadingSensor();
    void setup();
    void calibrate();
    String resultCalibrate();
    String getReading();
    int getReadingInt();
};