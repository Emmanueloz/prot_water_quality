#include <Arduino.h>
#include "Sensors/TurbidityReadingSensor.h"
#include "Sensors/PhReadingSensor.h"
#include "Sensors/TotalDissolvedSolids.h"
#include "StateManager.h"

TurbidityReadingSensor sensorTurbidity;
TotalDissolvedSolids sensorTDS(A0);
unsigned long timeout = 0;
PhReadingSensor phReadingSensor(A0);

int counterMessage = 0;

void setup()
{
  Serial.begin(115200);
  Serial.println("Getting started");
  // StateManager::setState(CALIBRATE);
}

void repose()
{
  if (counterMessage == 0)
  {
    Serial.println("Repose");
    counterMessage++;
  }
}

void calibrate()
{
  Serial.println("Calibrate");
}

void configure()
{
  Serial.println("Configure");
}

void reading()
{
  Serial.println("Reading");
}

void loop()
{
  switch (StateManager::getState())
  {
  case REPOSE:
    repose();
    break;
  case CALIBRATE:
    calibrate();
    break;
  case CONFIGURE:
    configure();
    break;
  case READING:
    reading();
    break;
  }
}
