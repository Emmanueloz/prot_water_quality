#include <Arduino.h>
#include "Sensors/ConductivityReadingSensor.h"

ConductivityReadingSensor sensor;

void setup()
{
  Serial.begin(9600);
  sensor.setup();
}

void loop()
{
  Serial.println(sensor.getReading());
  delay(1000);
}
