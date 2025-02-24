#include <Arduino.h>
#include "Sensors/PhReadingSensor.h"

PhReadingSensor phReadingSensor(A0);

void setup()
{
  Serial.begin(9600);
  Serial.println("Menu");
  Serial.println("1. Calibrar voltage 4");
  Serial.println("2. Calibrar voltage 6");
  Serial.println("3. Medir ph");
  Serial.println("4. Salir");
}

void loop()
{
  // menu para seleccionar la calibración o medir el ph

  int option = Serial.parseInt();

  if (option == 1)
  {
    phReadingSensor.calibrate(VOL_4);
  }
  else if (option == 2)
  {
    phReadingSensor.calibrate(VOL_6);
  }
  else if (option == 3)
  {
    phReadingSensor.calculateCalibration();
    Serial.println(phReadingSensor.getReadingFloat());
  }
}
