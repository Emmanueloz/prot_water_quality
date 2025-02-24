#include <Arduino.h>
#include <Keypad.h>

class MatrixKeyInput
{
public:
    MatrixKeyInput();
    void setup();
    String getReading();
};