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

SerialComm comm(Serial2);

void initialize()
{
    Config config = ConfigStoredROM::getConfig();
    Serial.println("Initializing");
    if (!ConfigStoredROM::isValidJWT(config.apiKey, sizeof(config.apiKey)))
    {
        Serial.println("Invalid or missing API key");
        StateManager::setState(CONFIGURE);
    }
    else if (!ConfigStoredROM::isValidFloat(config.calibrationVol4) || !ConfigStoredROM::isValidFloat(config.calibrationVol6))
    {
        Serial.println("No calibration");
        StateManager::setState(CALIBRATE);
    }
    else if (
        !ConfigStoredROM::isValidString(config.wifiSSID, sizeof(config.wifiSSID)) ||
        !ConfigStoredROM::isValidString(config.wifiPassword, sizeof(config.wifiPassword)))
    {
        Serial.println("No WiFi");
        StateManager::setState(CONFIGURE);
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
    comm.begin(9600);

    Serial.println("Getting started");
    initialize();
}

void repose(Command *response, int count)
{
    if (Serial.available() || count > 0)
    {
        Command command;
        if (count > 0)
        {
            command.name = response[0].name;
            command.value = response[0].value;
        }
        else
        {
            command = CommandManager::getCommand();
        }

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
            Serial.print("WiFi SSID: ");
            Serial.println(config.wifiSSID);
            Serial.print("WiFi Password: ");
            Serial.println(config.wifiPassword);
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
        else if (command.name == "connectBluetooth")
        {
            Serial.println("Connecting to bluetooth");
            comm.send("command=connectBluetooth");
        }
        else if (command.name == "reading")
        {
            Serial.println("Reading started");
            Config config = ConfigStoredROM::getConfig();
            String apiKey = config.apiKey;
            String wifiSSID = config.wifiSSID;
            String wifiPassword = config.wifiPassword;

            comm.send("command=connectInit,apiKey=" + String(apiKey) + ",ssid=" + wifiSSID + ",password=" + wifiPassword);
            lastTime = millis();
        }
    }
}

void calibrate(Command *response, int count)
{
    if (Serial.available() || count > 0)
    {
        Command command;
        if (count > 0)
        {
            command.name = response[0].name;
            command.value = response[0].value;
        }
        else
        {
            command = CommandManager::getCommand();
        }

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
            sensorPH.calculateCalibration();
            Serial.println("Calibration result");
            Serial.print(sensorPH.resultCalibration());
            StateManager::setState(INITIALIZE);
        }
    }
}

void configure(Command *response, int count)
{
    if (Serial.available() || count > 0)
    {
        Command command;
        if (count > 0)
        {
            command.name = response[0].name;
            command.value = response[0].value;
        }
        else
        {
            command = CommandManager::getCommand();
        }

        Serial.println("Received command: " + command.name + " with value: " + command.value);

        if (command.name == "setApiKey")
        {
            Serial.println("Setting API key");
            Serial.println(command.value);
            ConfigStoredROM::setApiKey(command.value);
        }
        else if (command.name == "setWifiSsid")
        {
            Serial.println("Setting WiFi SSID");
            Serial.println(command.value);
            ConfigStoredROM::setWifiSSID(command.value);
        }
        else if (command.name == "setWifiPassword")
        {
            Serial.println("Setting WiFi Password");
            Serial.println(command.value);
            ConfigStoredROM::setWifiPassword(command.value);
        }

        else if (command.name == "configureFinished")
        {
            Serial.println("Configuration finished");
            StateManager::setState(INITIALIZE);
        }
    }
}

void reading(Command *response, int count)
{
    if (Serial.available() || count > 0)
    {
        Command command;
        if (count > 0)
        {
            command.name = response[0].name;
            command.value = response[0].value;
        }
        else
        {
            command = CommandManager::getCommand();
        }
        if (command.name == "readingFinished")
        {
            Serial.println("Reading finished");
            StateManager::setState(REPOSE);
            comm.send("command=seenFinished");
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

        String recordMessage = "command=seen,colorR=" + String(color.r) +
                               ",colorG=" + String(color.g) +
                               ",colorB=" + String(color.b) +
                               ",conductivity=" + String(conductivity) +
                               ",ph=" + String(ph) +
                               ",temperature=" + String(temperature) +
                               ",tds=" + String(tds) +
                               ",turbidity=" + String(turbidity);

        comm.send(recordMessage);

        readings++;
    }
}

void handleResponse(Command *response, int count)
{

    for (int i = 0; i < count; i++)
    {
        String key = response[i].name;
        String value = response[i].value;

        if (key == "response")
        {
            if (value == "seenSuccess")
            {
                Serial.println("Reading successful");
            }
            else if (value == "seenError")
            {
                Serial.println("Reading error");
                StateManager::setState(REPOSE);
            }
            else if (value == "connecting")
            {
                Serial.println("Connecting to WiFi");
            }
            else if (value == "connectWifiSuccess")
            {
                Serial.println("Connected WiFi successfully");
            }
            else if (value == "connectingSocket")
            {
                Serial.println("Connecting to socket");
            }
            else if (value == "socketConnected")
            {
                Serial.println("Connected to socket");
                StateManager::setState(READING);
            }
            else if (value == "socketDisconnected")
            {
                Serial.println("Disconnected from socket");
                StateManager::setState(REPOSE);
            }
            else if (value == "connectError")
            {
                Serial.println("Connection error");
                StateManager::setState(REPOSE);
            }
        }
    }
}

void loop()
{
    Command response[MAX_PAIRS];
    int count = comm.receive(response);

    handleResponse(response, count);

    switch (StateManager::getState())
    {
    case INITIALIZE:
        initialize();
        break;
    case REPOSE:
        repose(response, count);
        break;
    case CALIBRATE:
        calibrate(response, count);
        break;
    case CONFIGURE:
        configure(response, count);
        break;
    case READING:
        reading(response, count);
        break;
    }
}