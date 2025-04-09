#include "Sensors/SerialComm.h"
#include <Arduino.h>

SerialComm comm(Serial2);
unsigned long lastSend = 0;

void setup()
{
    Serial.begin(115200);

#ifdef ESP32
    Serial2.begin(9600, SERIAL_8N1, 16, 17);
    Serial.println("ESP32 ready");
#else
    Serial2.begin(9600);
    Serial.println("Arduino Mega ready");
#endif
}

void loop()
{
    if (millis() - lastSend > 3000)
    {
        String message =
#ifdef ESP32
            "device=ESP32,temp=25.5";
#else
            "device=Mega,pH=6.4";
#endif

        comm.send(message);
        Serial.print("Sent: ");
        Serial.println(message);
        lastSend = millis();
    }

    KeyValue data[MAX_PAIRS];
    int count = comm.receive(data);

    for (int i = 0; i < count; i++)
    {
        Serial.print("Received → ");
        Serial.print(data[i].key);
        Serial.print(" = ");
        Serial.println(data[i].value);
    }

    delay(100);
}