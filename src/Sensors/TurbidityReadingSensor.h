#pragma once
#include <Arduino.h>

class TurbidityReadingSensor
{
private:
    int sensorPin;

public:
    TurbidityReadingSensor(int pin = A0); // Constructor con pin por defecto
    void setup();
    void calibrate();
    String resultCalibration();
    String getReading();
    int getReadingInt();
    float getReadingFloat();
};
