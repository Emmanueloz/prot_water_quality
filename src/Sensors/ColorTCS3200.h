#include <Arduino.h>

#pragma once
struct RGB
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

class ColorTCS3200
{
public:
    ColorTCS3200(uint8_t s0, uint8_t s1, uint8_t s2, uint8_t s3, uint8_t out);

    void setup();
    void getFrequencies(float &redFreq, float &greenFreq, float &blueFreq);
    String detectColor(float redFreq, float greenFreq, float blueFreq);
    RGB getRGB();

private:
    uint8_t _s0, _s1, _s2, _s3, _out;
    float readFrequency(uint8_t s2State, uint8_t s3State);
};
