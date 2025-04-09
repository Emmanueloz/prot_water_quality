#ifndef SERIALCOMM_H
#define SERIALCOMM_H

#include <Arduino.h>

#define MAX_PAIRS 10 // Máximo de pares clave=valor por mensaje

struct KeyValue
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
    int receive(KeyValue *data); // Llena el array y devuelve cuántos pares encontró

private:
    HardwareSerial &serialPort;
    String readLine();
};

#endif