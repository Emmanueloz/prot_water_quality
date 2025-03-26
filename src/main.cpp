#include <Arduino.h>
#include "Sensors/TemperatureReadingSensor.h"

TemperatureReadingSensor sensor; // Única instancia global

void setup()
{
    sensor.begin(); // Inicializa todo el sistema
}

void loop()
{
    sensor.getReadingFloat(); // Lee y muestra la temperatura
}