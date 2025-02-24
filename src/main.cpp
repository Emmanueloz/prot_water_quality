#include <Arduino.h>
#include "Sensors/TotalDissolvedSolids.h"
#include "Sensors/TemperatureReadingSensor.h"

// TotalDissolvedSolids sensorTDS(A0);
TemperatureReadingSensor sensorTemp(2);

unsigned long timeout = 0;

void setup()
{
  // sensorTDS.setup();
  sensorTemp.begin();
}

void loop()
{
  if (timeout < millis())
  {
    // Serial.println(sensorTDS.getReading(6.0));
    // timeout = millis() + 1000;
    float temp = sensorTemp.readTemperatureC();
    Serial.print("Temperatura = ");
    Serial.print(temp);
    Serial.println(" °C");
  }
}