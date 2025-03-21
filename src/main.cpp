#include <Arduino.h>
#include "Sensors/TotalDissolvedSolids.h"
#include "Sensors/TemperatureReadingSensor.h"
#include <DFRobot_EC.h> // Asegúrate de tener instalada la librería

// Instancias de sensores
// TotalDissolvedSolids sensorTDS(A0);
// TemperatureReadingSensor sensorTemp(2);
DFRobot_EC sensorEC; // Sensor EC de DFRobot
#define EC_PIN A1    // Pin analógico para EC

unsigned long timeout = 0;

void setup()
{
  Serial.begin(9600); // Inicializa Serial solo una vez
  // sensorTDS.setup();
  //  sensorTemp.begin();
  sensorEC.begin(); // Inicializa sensor EC
  delay(2000);      // Tiempo de estabilización
}

void loop()
{
  if (millis() > timeout)
  {
    timeout = millis() + 1000; // Actualiza timeout

    // Lectura de temperatura
    // float temp = sensorTemp.readTemperatureC();

    // Lectura de EC
    float voltageEC = analogRead(EC_PIN) * 5000.0 / 1024.0; // Convertir a mV
    float ecValue = sensorEC.readEC(voltageEC, temp);       // EC compensada

    // Mostrar lecturas
    // Serial.print("Temperatura: ");
    // Serial.print(temp, 1);
    // Serial.print(" °C | EC: ");
    Serial.print(ecValue, 2);
    Serial.println(" mS/cm");

    // Calibración por Serial (opcional)
    sensorEC.calibration(voltageEC, temp);
  }
}