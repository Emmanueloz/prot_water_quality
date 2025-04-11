#include "SerialComm.h"

SerialComm::SerialComm() : serialPort(nullptr) {}

void SerialComm::begin(HardwareSerial &serial, unsigned long baudRate)
{
    serialPort = &serial;
    serialPort->begin(baudRate);
}

void SerialComm::send(const String &message)
{
    if (serialPort)
    {
        serialPort->println(message);
    }
}

String SerialComm::receive()
{
    String line = "";
    if (serialPort)
    {
        line = serialPort->readStringUntil('\n');
        line.trim();
    }
    return line;
}

String SerialComm::readLine()
{
    if (serialPort)
    {
        return serialPort->readStringUntil('\n');
    }
    return "";
}
