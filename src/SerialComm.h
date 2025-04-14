#pragma once
#include <Arduino.h>

#define MAX_PAIRS 10 // Máximo de pares clave=valor por mensaje

struct Keyvalue
{
    String key;
    String value;
};

class SerialComm
{
public:
    SerialComm(HardwareSerial &serial);
    void begin(long baudRate);
    void send(const String &message);
    int receive(Keyvalue *data);

private:
    HardwareSerial &serialPort;
    String readLine();
};
