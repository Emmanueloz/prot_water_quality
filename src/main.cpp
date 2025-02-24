#include <Arduino.h>
#include "Sensors/TotalDissolvedSolids.h"

TotalDissolvedSolids sensorTDS(A0);
unsigned long timeout = 0;

void setup()
{
  sensorTDS.setup();
}

void loop()
{
  if (timeout < millis())
  {
    Serial.println(sensorTDS.getReading(6.0));
    timeout = millis() + 1000;
  }
}