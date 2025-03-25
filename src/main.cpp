#include <Arduino.h>
#include "Sensors/TemperatureReadingSensor.h"

TempReader sensor; // Única instancia global

void setup()
{
    sensor.begin(); // Inicializa todo el sistema
}

void loop()
{
    sensor.monitor(); // Lee y muestra la temperatura
}