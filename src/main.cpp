#include <Arduino.h>
// Sensores
#include "Sensors/TurbidityReadingSensor.h"
#include "Sensors/PhReadingSensor.h"
#include "Sensors/TotalDissolvedSolids.h"
#include "Sensors/ColorTCS3200.h"
#include "Sensors/TemperatureReadingSensor.h"
#include "Sensors/ConductivityReadingSensor.h"

// Estados del sistema
#include "StateManager.h"
#include "CommandManager.h"
#include "ConfigStoredROM.h"
#include "SerialComm.h"
// Pines de los sensores
// Analog
const int ANALOG_PIN_TURBIDITY = A1;
const int ANALOG_PIN_TDS = A0;
const int ANALOG_PIN_PH = A8;
const int ANALOG_PIN_CONDUCTIVITY = A3;
// Digital
const uint8_t DIGITAL_PIN_TEMP = 2;

const uint8_t DIGITAL_PIN_S0_COLOR = 8;
const uint8_t DIGITAL_PIN_S1_COLOR = 9;
const uint8_t DIGITAL_PIN_S2_COLOR = 10;
const uint8_t DIGITAL_PIN_S3_COLOR = 11;
const uint8_t DIGITAL_PIN_OUT_COLOR = 12;

// Constantes
const int WAIT_TIME = 5000;

// Variables
unsigned long lastTime = 0;
unsigned int readings = 1;

// Instancias de los sensores
ColorTCS3200 sensorColor(DIGITAL_PIN_S0_COLOR, DIGITAL_PIN_S1_COLOR, DIGITAL_PIN_S2_COLOR, DIGITAL_PIN_S3_COLOR,
                         DIGITAL_PIN_OUT_COLOR);
ConductivityReadingSensor sensorConductivity(ANALOG_PIN_CONDUCTIVITY);
PhReadingSensor sensorPH(ANALOG_PIN_PH);
TotalDissolvedSolids sensorTDS(ANALOG_PIN_TDS);
TemperatureReadingSensor sensorTemperature(DIGITAL_PIN_TEMP);
TurbidityReadingSensor sensorTurbidity(ANALOG_PIN_TURBIDITY);

SerialComm comm;

void initialize()
{
    Config config = ConfigStoredROM::getConfig();
    if (strlen(config.apiKey) == 0)
    {
        Serial.println("No API key");
        StateManager::setState(CONFIGURE);
    }
    else if (config.calibrationVol4 == 0.0 || config.calibrationVol6 == 0.0)
    {
        Serial.println("No calibration");
        StateManager::setState(CALIBRATE);
    }
    else
    {
        sensorPH.setVoltage(VOL_4, config.calibrationVol4);
        sensorPH.setVoltage(VOL_6, config.calibrationVol6);
        sensorPH.calculateCalibration();
        StateManager::setState(REPOSE);
    }

    Serial.print("State: ");
    Serial.println(StateManager::getStateString());
}

void setup()
{
    Serial.begin(115200);
    sensorTurbidity.setup();
    sensorConductivity.setup();
    sensorColor.setup();
    sensorTemperature.begin();

    comm.begin(Serial2, 9600);

    Serial.println("Getting started");
    initialize();
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
        else if (command.name == "resultCalibration")
        {
            Serial.print("Result Calibration: ");
            Serial.println(sensorPH.resultCalibration());
        }
        else if (command.name == "getStatus")
        {
            Serial.print("State: ");
            Serial.println(StateManager::getStateString());
        }
        else if (command.name == "configure")
        {
            Serial.println("Configure");
            StateManager::setState(CONFIGURE);
        }
        else if (command.name == "calibrate")
        {
            Serial.println("Calibrate");
            StateManager::setState(CALIBRATE);
        }
        else if (command.name == "reading")
        {
            Serial.println("Reading started");
            StateManager::setState(READING);
            lastTime = millis();
        }
    }
}

void calibrate()
{
    if (Serial.available())
    {
        Command command = CommandManager::getCommand();

        if (command.name == "phCalibrateVol4")
        {
            Serial.println("Calibrating vol4");
            float voltage = sensorPH.calibrate(VOL_4);
            ConfigStoredROM::setCalibrationVol4(voltage);
        }
        else if (command.name == "phCalibrateVol6")
        {
            Serial.println("Calibrating vol6");
            float voltage = sensorPH.calibrate(VOL_6);
            ConfigStoredROM::setCalibrationVol6(voltage);
        }
        else if (command.name == "phCalibrate")
        {
            Serial.println("Calibrating");
            sensorPH.calculateCalibration();
        }
        else if (command.name == "phCalibrateResult")
        {
            Serial.println("Calibration result");
            Serial.print(sensorPH.resultCalibration());
        }
        else if (command.name == "phSetVol4")
        {
            Serial.println("Setting vol4");
            sensorPH.setVoltage(VOL_4, command.value.toFloat());
            ConfigStoredROM::setCalibrationVol4(command.value.toFloat());
        }
        else if (command.name == "phSetVol6")
        {
            Serial.println("Setting vol6");
            sensorPH.setVoltage(VOL_6, command.value.toFloat());
            ConfigStoredROM::setCalibrationVol6(command.value.toFloat());
        }
        else if (command.name == "calibrateFinished")
        {
            Serial.println("Calibration finished");
            StateManager::setState(INITIALIZE);
        }
    }
}

void configure()
{
    if (Serial.available())
    {
        Command command = CommandManager::getCommand();

        if (command.name == "setApiKey")
        {
            Serial.println("Setting API key");
            Serial.println(command.value);
            ConfigStoredROM::setApiKey(command.value);
        }
        else if (command.name == "configureFinished")
        {
            Serial.println("Configuration finished");
            StateManager::setState(INITIALIZE);
        }
    }
}

void reading()
{
    if (Serial.available())
    {
        Command command = CommandManager::getCommand();
        if (command.name == "readingFinished")
        {
            Serial.println("Reading finished");
            StateManager::setState(REPOSE);
            readings = 1;
            return;
        }
    }

    if (millis() - lastTime > WAIT_TIME)
    {
        lastTime = millis();

        Serial.println("Reading " + String(readings));

        RGB color = sensorColor.getRGB();
        float conductivity = sensorConductivity.getReadingFloat();
        float ph = sensorPH.getReadingFloat();
        float temperature = sensorTemperature.getReadingFloat();
        float tds = sensorTDS.getReadingFloat(temperature);
        float turbidity = sensorTurbidity.getReadingFloat();

        Serial.print("Color = ");
        Serial.println(String(color.r) + "," + String(color.g) + "," + String(color.b));
        Serial.print("Conductivity = ");
        Serial.println(String(conductivity));
        Serial.print("PH = ");
        Serial.println(String(ph));
        Serial.print("Temperature = ");
        Serial.println(String(temperature));
        Serial.print("TDS = ");
        Serial.println(String(tds));
        Serial.print("Turbidity = ");
        Serial.println(String(turbidity));
        comm.send("tds=" + String(tds));

        readings++;
    }
}

void loop()
{
    switch (StateManager::getState())
    {
    case INITIALIZE:
        initialize();
        break;
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