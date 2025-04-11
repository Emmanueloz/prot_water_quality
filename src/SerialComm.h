#pragma once
#include <Arduino.h>

struct Keyvalue
{
    String key;
    String value;
};
class SerialComm
{
public:
    SerialComm();
    void begin(HardwareSerial &serial, unsigned long baudRate);
    void send(const String &message);
    String receive(Keyvalue *data);

private:
    HardwareSerial *serialPort;
    String readLine();
};
