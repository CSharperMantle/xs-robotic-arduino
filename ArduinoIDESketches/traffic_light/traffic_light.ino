#include <Arduino.h>

#define LIGHT_RED 0
#define LIGHT_YELLOW 1
#define LIGHT_GREEN 2

#define PIN_LED_RED 12
#define PIN_LED_YELLOW 11
#define PIN_LED_GREEN 10

void initLEDs() {
  pinMode(PIN_LED_RED, OUTPUT);
  pinMode(PIN_LED_YELLOW, OUTPUT);
  pinMode(PIN_LED_GREEN, OUTPUT);
}

void setAllLEDs(int level) {
  digitalWrite(PIN_LED_RED, level);
  digitalWrite(PIN_LED_YELLOW, level);
  digitalWrite(PIN_LED_GREEN, level);
}

int getPin(int light) {
  switch (light) {
  case LIGHT_RED:
    return PIN_LED_RED;
  case LIGHT_YELLOW:
    return PIN_LED_YELLOW;
  case LIGHT_GREEN:
    return PIN_LED_GREEN;
  default:
    return -1;
  }
}

void timedLightLED(int light, unsigned int duration) {
  setAllLEDs(LOW);
  digitalWrite(getPin(light), HIGH);
  delay(duration);
  setAllLEDs(LOW);
}

void pulseLEDs(int light,
    unsigned int times,
    unsigned int high_duration,
    unsigned int low_duration,
    bool time_last_low) {
  setAllLEDs(LOW);
  for (unsigned int i = 0; i < times - 1; i++) {
    timedLightLED(light, high_duration);
    setAllLEDs(LOW);
    delay(low_duration);
  }
  timedLightLED(light, high_duration);
  setAllLEDs(LOW);
  if (time_last_low) {
    delay(low_duration);
  }
}

void setup() {
  initLEDs();
}

void loop() {
  timedLightLED(LIGHT_RED, 5000);
  pulseLEDs(LIGHT_RED, 5, 500, 500, false);
  timedLightLED(LIGHT_GREEN, 5000);
  pulseLEDs(LIGHT_GREEN, 5, 500, 500, false);
  timedLightLED(LIGHT_YELLOW, 2000);
}
