#include <Arduino.h>
// Sensores
#include "Sensors/TurbidityReadingSensor.h"
#include "Sensors/PhReadingSensor.h"
#include "Sensors/TotalDissolvedSolids.h"
#include "Sensors/ColorTCS3200.h"
#include "Sensors/ConductivityReadingSensor.h"

// Estados del sistema
#include "StateManager.h"
#include "CommandManager.h"
#include "ConfigStoredROM.h"

// Pines de los sensores
// Analog
const int ANALOG_PIN_TURBIDITY = A0;
const int ANALOG_PIN_TDS = A1;
const int ANALOG_PIN_PH = A8;
const int ANALOG_PIN_CONDUCTIVITY = A3;
// Digital
const uint8_t DIGITAL_PIN_S0_COLOR = 8;
const uint8_t DIGITAL_PIN_S1_COLOR = 9;
const uint8_t DIGITAL_PIN_S2_COLOR = 10;
const uint8_t DIGITAL_PIN_S3_COLOR = 11;
const uint8_t DIGITAL_PIN_OUT_COLOR = 12;

// Instancias de los sensores
TurbidityReadingSensor sensorTurbidity(ANALOG_PIN_TURBIDITY);
TotalDissolvedSolids sensorTDS(ANALOG_PIN_TDS);
PhReadingSensor phReadingSensor(ANALOG_PIN_PH);
ConductivityReadingSensor sensorConductivity(ANALOG_PIN_CONDUCTIVITY);
ColorTCS3200 sensorColor(DIGITAL_PIN_S0_COLOR, DIGITAL_PIN_S1_COLOR, DIGITAL_PIN_S2_COLOR, DIGITAL_PIN_S3_COLOR,
                         DIGITAL_PIN_OUT_COLOR);

void setup()
{
  Serial.begin(115200);
  sensorTurbidity.setup();
  sensorConductivity.setup();
  sensorColor.setup();
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
