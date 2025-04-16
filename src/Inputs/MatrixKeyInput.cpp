#include "MatrixKeyInput.h"

MatrixKeyInput::MatrixKeyInput(byte *pinRows, byte *pinCols)
{
    MatrixKeyInput::pinRows = pinRows;
    MatrixKeyInput::pinCols = pinCols;

    this->keypad = new Keypad(makeKeymap(keys), pinRows, pinCols, ROWS, COLS);
}

char MatrixKeyInput::getKey()
{
    return this->keypad->getKey();
}

bool MatrixKeyInput::equalMessage(String message)
{
    char key = this->getKey();

    if (key == NO_KEY)
    {
        return false;
    }

    message += key;

    return message == this->message;
}

void MatrixKeyInput::clearMessage()
{
    this->message = "";
}
