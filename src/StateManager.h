#include <Arduino.h>
#pragma once

enum State
{
    INITIALIZE,
    REPOSE,
    CALIBRATE,
    CONFIGURE,
    READING
};

class StateManager
{
private:
    static State _state;

public:
    static void setState(State state);
    static State getState();
    static String getStateString();
};
