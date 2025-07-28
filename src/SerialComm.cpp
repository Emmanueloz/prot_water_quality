#include "SerialComm.h"

SerialComm::SerialComm(HardwareSerial &serial) : serialPort(serial) {}

void SerialComm::begin(long baudRate)
{
    serialPort.begin(baudRate);
}

void SerialComm::send(const String &message)
{
    serialPort.println(message);
}

int SerialComm::receive(Command *data)
{
    if (!serialPort.available())
        return 0;

    String line = readLine();
    line.trim();

    int count = 0;
    int start = 0;

    while (start < static_cast<int>(line.length()) && count < MAX_PAIRS)
    {
        int commaIndex = line.indexOf(',', start);
        String pair = (commaIndex == -1) ? line.substring(start) : line.substring(start, commaIndex);
        int equalIndex = pair.indexOf('=');

        if (equalIndex != -1)
        {
            data[count].name = pair.substring(0, equalIndex);
            data[count].value = pair.substring(equalIndex + 1);
            count++;
        }

        if (commaIndex == -1)
        {
            data[count].name = pair;
            data[count].value = "";
            count++;
            break;
        }

        start = commaIndex + 1;
    }

    return count;
}

String SerialComm::readLine()
{
    if (serialPort)
    {
        return serialPort.readStringUntil('\n');
    }
    return "";
}
