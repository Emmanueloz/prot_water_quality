#include <Arduino.h>
#include "Sensors/TurbidityReadingSensor.h"
#include "Sensors/PhReadingSensor.h"
#include "Sensors/TotalDissolvedSolids.h"
#include "StateManager.h"
#include "ConfigStoredROM.h"
#include "CommandManager.h"
#include "Sensors/ColorTCS3200.h"

TurbidityReadingSensor sensorTurbidity;
TotalDissolvedSolids sensorTDS(A0);
// TotalDissolvedSolids sensorTDS(A0);
ColorTCS3200 sensorColor(8, 9, 10, 11, 12);
unsigned long timeout = 0;
PhReadingSensor phReadingSensor(A0);

int counterMessage = 0;
#include "Sensors/ConductivityReadingSensor.h"

ConductivityReadingSensor sensor;

void setup()
{
  Serial.begin(115200);
  Serial.println("Getting started");
}

void repose()
{
  if (Serial.available())
  {
    Command command = CommandManager::getCommand();

    if (command.name == "getConfig")
    {
      Serial.println("Config");
      Config config = ConfigStoredROM::getConfig();
      Serial.print("API Key: ");
      Serial.println(config.apiKey);
      Serial.print("Calibration Vol4: ");
      Serial.println(config.calibrationVol4);
      Serial.print("Calibration Vol6: ");
      Serial.println(config.calibrationVol6);
    }
    else if (command.name == "setApiKey")
    {
      ConfigStoredROM::setApiKey(command.value);
    }
    else if (command.name == "phCalibrateVol4")
    {
      ConfigStoredROM::setCalibrationVol4(command.value.toFloat());
    }
    else if (command.name == "phCalibrateVol6")
    {
      ConfigStoredROM::setCalibrationVol6(command.value.toFloat());
    }
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
