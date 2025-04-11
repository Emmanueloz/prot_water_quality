#pragma once
#include <Arduino.h>

class SerialComm
{
public:
    SerialComm();
    void begin(HardwareSerial &serial, unsigned long baudRate);
    void send(const String &message);
    String receive();

    String readLine();

private:
    HardwareSerial *serialPort;
};
