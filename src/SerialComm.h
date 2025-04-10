#pragma once
#include <Arduino.h>

class SerialComm
{
public:
    SerialComm();
    void begin(HardwareSerial &serial, unsigned long baudRate);
    void send(const String &message);
    String receive();

private:
    HardwareSerial *serialPort;
};
