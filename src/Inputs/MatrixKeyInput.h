#include <Arduino.h>
#include <Keypad.h>
#pragma once

class MatrixKeyInput
{
public:
    MatrixKeyInput(
        byte *pinRows,
        byte *pinCols);
    char getKey();

    bool equalMessage(String message);
    void clearMessage();

private:
    static const byte ROWS = 4;
    static const byte COLS = 4;
    char keys[ROWS][COLS] = {
        {'1', '2', '3', 'A'},
        {'4', '5', '6', 'B'},
        {'7', '8', '9', 'C'},
        {'*', '0', '#', 'D'}};
    byte *pinRows;
    byte *pinCols;
    Keypad *keypad;
    String message;
};