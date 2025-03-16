#include <Arduino.h>
#pragma once

class ConductivityReadingSensor
{

private:
    int sensorPin;

public:
    ConductivityReadingSensor(int pin = A0);
    void setup();
    String getReading();
    int getReadingInt();
    float getReadingFloat();
};