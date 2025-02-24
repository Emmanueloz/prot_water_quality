#include <Arduino.h>
#include "Sensors/TurbidityReadingSensor.h"
#include "Sensors/PhReadingSensor.h"
#include "Sensors/TotalDissolvedSolids.h"

TurbidityReadingSensor sensor;
TotalDissolvedSolids sensorTDS(A0);
unsigned long timeout = 0;
PhReadingSensor phReadingSensor(A0);

void setup()
{
  Serial.begin(9600);
  sensor.setup();
  sensorTDS.setup();
  Serial.begin(9600);
  Serial.println("Menu");
  Serial.println("1. Calibrar voltage 4");
  Serial.println("2. Calibrar voltage 6");
  Serial.println("3. Set calibrate vol 4");
  Serial.println("4. Set calibrate vol 6");
  Serial.println("5. Medir ph");
}

void loop()
{
  if (timeout < millis())
  {
    Serial.println(sensorTDS.getReading(6.0));
    timeout = millis() + 1000;
  }

  // menu para seleccionar la calibración o medir el ph

  if (Serial.available())
  {

    String command = Serial.readStringUntil('\n');

    int option = command.substring(0, command.indexOf(',')).toInt();
    float voltage = command.substring(command.indexOf(',') + 1).toFloat();

    if (option == 1)
    {
      float voltage = phReadingSensor.calibrate(VOL_4);
      Serial.println(voltage);
    }
    else if (option == 2)
    {
      float voltage = phReadingSensor.calibrate(VOL_6);
      Serial.println(voltage);
    }
    else if (option == 3)
    {
      phReadingSensor.setVoltage(VOL_4, voltage);
    }
    else if (option == 4)
    {
      phReadingSensor.setVoltage(VOL_6, voltage);
    }
    else if (option == 5)
    {
      phReadingSensor.calculateCalibration();
      Serial.println(phReadingSensor.getReadingFloat());
    }
  }
}

Serial.println(sensor.getReading());
delay(500);
}
