#include <Arduino.h>
#include "Sensors/TurbidityReadingSensor.h"

TurbidityReadingSensor sensor;

void setup()
{
  Serial.begin(9600);
  sensor.setup();
}

void loop()
{
  Serial.println(sensor.getReading());
  delay(500);
}
