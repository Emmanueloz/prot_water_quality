#include <Arduino.h>
#include "Sensors/TotalDissolvedSolids.h"
#include "Sensors/ColorTCS3200.h"

// TotalDissolvedSolids sensorTDS(A0);
ColorTCS3200 sensorColor(8, 9, 10, 11, 12);
unsigned long timeout = 0;
const unsigned long READ_INTERVAL = 1000;
unsigned long previousMillis = 0;

void setup()
{
  // sensorTDS.setup();
  sensorColor.setup();
}

void loop()
{
  unsigned long currentMillis = millis();
  // if (timeout < millis())
  // {
  //   Serial.println(sensorTDS.getReading(6.0));
  //   timeout = millis() + 1000;
  // }
  if (currentMillis - previousMillis >= READ_INTERVAL)
  {
    previousMillis = currentMillis;

    RGB color = sensorColor.getRGB();

    Serial.print("Rojo: ");
    Serial.print(color.r);
    Serial.print(" | Verde: ");
    Serial.print(color.g);
    Serial.print(" | Azul: ");
    Serial.println(color.b);

    Serial.println("---------------------------");
  }
}