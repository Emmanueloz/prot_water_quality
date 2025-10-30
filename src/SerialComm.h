#pragma once
#include <Arduino.h>
#include "CommandManager.h"

#define MAX_PAIRS 10 // Máximo de pares clave=valor por mensaje

class SerialComm
{
public:
    SerialComm(HardwareSerial &serial);
    void begin(long baudRate);
    void send(const String &message);
    int receive(Command *data);

private:
    HardwareSerial &serialPort;
    String readLine();
};
