#include "TotalDissolvedSolids.h"

TotalDissolvedSolids::TotalDissolvedSolids(int pin) : pin(pin), tds(pin) {}

void TotalDissolvedSolids::setup()
{
    Serial.begin(115200);
}

float TotalDissolvedSolids::getReadingFloat(float temperature)
{
    return tds.update(temperature);
}

String TotalDissolvedSolids::getReading(float temperature)
{
    float tdsValue = getReadingFloat(temperature);
    return String(tdsValue, 0) + " ppm";
}
