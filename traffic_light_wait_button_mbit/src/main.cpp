#include <Arduino.h>
#include <Protothread.h>

#define PIN_RED 12
#define PIN_YELLOW 11
#define PIN_GREEN 10
#define PIN_BUTTON 5

#define DEFAULT_RED_DURATION 10000
#define DEFAULT_YELLOW_DURATION 2000
#define DEFAULT_GREEN_DURATION 5000
#define FLASH_INTERVAL 500
#define FLASH_TIMES 5
#define BUTTON_PRESS_DURATION_DELTA 5000

static unsigned int redLightDuration = DEFAULT_RED_DURATION;
static bool isRedLightOn = false;
static bool isButtonPressed = false;

void initButton() {
  pinMode(PIN_BUTTON, INPUT);
}

void initLEDs() {
  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_YELLOW, OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
}

void offLEDs() {
  digitalWrite(PIN_RED, LOW);
  digitalWrite(PIN_YELLOW, LOW);
  digitalWrite(PIN_GREEN, LOW);
}

class FlashLightThread : public Protothread {
public:
    virtual bool Run();

private:
    int redOnMillis = 0;
};

bool FlashLightThread::Run() {
    PT_BEGIN();

    // Steady red light
    offLEDs();
    redOnMillis = millis();
    digitalWrite(PIN_RED, HIGH);
    isRedLightOn = true;
    isButtonPressed = false;
    PT_WAIT_UNTIL(millis() - redOnMillis >= redLightDuration); // Wait until red light expires
    offLEDs();
    // Reset red light duration
    redLightDuration = DEFAULT_RED_DURATION;
    isRedLightOn = false;
    // Flash red light
    for (int i = 0; i < FLASH_TIMES; i++) {
        offLEDs();
        delay(FLASH_INTERVAL);
        digitalWrite(PIN_RED, HIGH);
        delay(FLASH_INTERVAL);
    }
    offLEDs();
    // Steady green light
    digitalWrite(PIN_GREEN, HIGH);
    delay(DEFAULT_GREEN_DURATION);
    offLEDs();
    // Flash green light
    for (int i = 0; i < FLASH_TIMES; i++) {
        offLEDs();
        delay(FLASH_INTERVAL);
        digitalWrite(PIN_GREEN, HIGH);
        delay(FLASH_INTERVAL);
    }
    offLEDs();
    // Steady yellow light
    digitalWrite(PIN_YELLOW, HIGH);
    delay(DEFAULT_YELLOW_DURATION);
    offLEDs();

    PT_RESTART();
    PT_END();
}

class ButtonThread : public Protothread {
public:
    virtual bool Run();
};

bool ButtonThread::Run() {
    PT_BEGIN();

    PT_WAIT_UNTIL(isRedLightOn);
    if (digitalRead(PIN_BUTTON) == LOW && !isButtonPressed) {
        redLightDuration -= BUTTON_PRESS_DURATION_DELTA;
        isButtonPressed = true;
    }

    PT_RESTART();
    PT_END();
}

static FlashLightThread flashLightThread {};
static ButtonThread buttonThread {};

void setup() {
    initLEDs();
    initButton();
}

void loop() {
    flashLightThread.Run();
    buttonThread.Run();
}
