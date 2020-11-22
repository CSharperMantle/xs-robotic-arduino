#include <Arduino.h>

#define PIN_SENSOR A0
#define PIN_RELAY 2
#define VALVE_HUM 512

void setup() {
    pinMode(PIN_RELAY, OUTPUT);
    digitalWrite(PIN_RELAY, LOW);
}

void loop() {
    if (analogRead(PIN_SENSOR) >= VALVE_HUM)
    {
        digitalWrite(PIN_RELAY, LOW);
    }
    else
    {
        digitalWrite(PIN_RELAY, HIGH);
    }
    delay(100);
}