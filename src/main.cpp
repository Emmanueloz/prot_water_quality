#include <Arduino.h>
#include "Sensors/TurbidityReadingSensor.h"
#include "Sensors/PhReadingSensor.h"
#include "Sensors/TotalDissolvedSolids.h"
#include "StateManager.h"
#include "ConfigStoredROM.h"

TurbidityReadingSensor sensorTurbidity;
TotalDissolvedSolids sensorTDS(A0);
unsigned long timeout = 0;
PhReadingSensor phReadingSensor(A0);

int counterMessage = 0;

void setup()
{
  Serial.begin(115200);
  Serial.println("Getting started");
}

void repose()
{
  if (Serial.available())
  {
    String command = Serial.readStringUntil('\n');
    command.trim();
    int separator = command.indexOf(':');
    String commandName = command.substring(0, separator);
    String commandValue = command.substring(separator + 1);

    if (commandName == "getConfig")
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
    else if (commandName == "setApiKey")
    {
      ConfigStoredROM::setApiKey(commandValue);
    }
    else if (commandName == "phCalibrateVol4")
    {
      ConfigStoredROM::setCalibrationVol4(commandValue.toFloat());
    }
    else if (commandName == "phCalibrateVol6")
    {
      ConfigStoredROM::setCalibrationVol6(commandValue.toFloat());
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
