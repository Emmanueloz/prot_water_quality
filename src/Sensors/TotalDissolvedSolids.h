#include <Arduino.h>
#include "CQRobotTDS.h"

#pragma once

class TotalDissolvedSolids
{
private:
    int pin;
    CQRobotTDS tds;

public:
    TotalDissolvedSolids(int pin);
    void setup();
    String getReading(float temperature);
    float getReadingFloat(float temperature);
};
