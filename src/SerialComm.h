#pragma once
#include <Arduino.h>

#define MAX_PAIRS 10
struct Keyvalue
{
    String key;
    String value;
};
class SerialComm
{
public:
    SerialComm();
    void send(const String &message);
    int receive(Keyvalue *data);

private:
    HardwareSerial *serialPort;
    String readLine();
};
