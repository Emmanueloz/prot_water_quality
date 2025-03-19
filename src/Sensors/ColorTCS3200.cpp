#include "ColorTCS3200.h"

ColorTCS3200::ColorTCS3200(uint8_t s0, uint8_t s1, uint8_t s2, uint8_t s3, uint8_t out)
    : _s0(s0), _s1(s1), _s2(s2), _s3(s3), _out(out) {}

void ColorTCS3200::setup()
{
    Serial.begin(9600);
    pinMode(_s0, OUTPUT);
    pinMode(_s1, OUTPUT);
    pinMode(_s2, OUTPUT);
    pinMode(_s3, OUTPUT);
    pinMode(_out, INPUT);

    digitalWrite(_s0, HIGH);
    digitalWrite(_s1, HIGH);
}

float ColorTCS3200::readFrequency(uint8_t s2State, uint8_t s3State)
{
    digitalWrite(_s2, s2State);
    digitalWrite(_s3, s3State);

    delayMicroseconds(200); // Espera reducida acorde al datasheet

    unsigned long pulseWidth = pulseIn(_out, digitalRead(_out) == HIGH ? LOW : HIGH, 100000);
    if (pulseWidth == 0)
        return 0;
    return 1000000.0 / (pulseWidth * 2); // Período completo
}

void ColorTCS3200::getFrequencies(float &redFreq, float &greenFreq, float &blueFreq)
{
    // Configuraciones típicas:
    // Rojo: S2 = LOW, S3 = LOW
    // Azul: S2 = LOW, S3 = HIGH
    // Verde: S2 = HIGH, S3 = HIGH
    redFreq = readFrequency(LOW, LOW);
    blueFreq = readFrequency(LOW, HIGH);
    greenFreq = readFrequency(HIGH, HIGH);
}

String ColorTCS3200::detectColor(float redFreq, float greenFreq, float blueFreq)
{
    const float whiteThreshold = 40000;
    const float diffThreshold = 5000;

    if (redFreq > whiteThreshold && greenFreq > whiteThreshold && blueFreq > whiteThreshold &&
        abs(redFreq - greenFreq) < diffThreshold &&
        abs(redFreq - blueFreq) < diffThreshold &&
        abs(greenFreq - blueFreq) < diffThreshold)
    {
        return "White";
    }

    if (redFreq > blueFreq && redFreq > greenFreq)
        return "Red";
    if (blueFreq > redFreq && blueFreq > greenFreq)
        return "Blue";
    if (greenFreq > redFreq && greenFreq > blueFreq)
        return "Green";

    return "Unknown";
}
static uint8_t mapFloat(float x, float in_min, float in_max, float out_min, float out_max)
{
    if (x < in_min)
        x = in_min;
    if (x > in_max)
        x = in_max;
    return (uint8_t)(((x - in_min) * (out_max - out_min) / (in_max - in_min)) + out_min);
}

RGB ColorTCS3200::getRGB()
{
    float redFreq, greenFreq, blueFreq;
    getFrequencies(redFreq, greenFreq, blueFreq);

    // Valores de calibración (mínimo y máximo) para cada canal.
    const float redMin = 2500.0, redMax = 20000.0;
    const float greenMin = 2000.0, greenMax = 15000.0;
    const float blueMin = 2500.0, blueMax = 12000.0;

    uint8_t r = mapFloat(redFreq, redMin, redMax, 0, 255);
    uint8_t g = mapFloat(greenFreq, greenMin, greenMax, 0, 255);
    uint8_t b = mapFloat(blueFreq, blueMin, blueMax, 0, 255);

    RGB rgb = {r, g, b};
    return rgb;
}