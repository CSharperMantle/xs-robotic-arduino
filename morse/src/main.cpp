/**
 * Demonstrate the most simple usage: send one Morse Code message, once,
 * while blocking (not doing anything else).
 */

#include <Arduino.h>
#include <morse.h>

#define PIN_STATUS	13

static LEDMorseSender cqSender{PIN_STATUS};

void setup()
{
	cqSender.setup();
}

void loop()
{
	String str = Serial.readStringUntil('$');
	cqSender.setMessage(str);
	cqSender.sendBlocking();
}
