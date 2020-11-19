/**
 * Demonstrate the most simple usage: send one Morse Code message, once,
 * while blocking (not doing anything else).
 */

#include <Arduino.h>
#include <morse.h>

#define PIN_STATUS	10

static SpeakerMorseSender cqSender{PIN_STATUS};

void setup()
{
	Serial.begin(115200);
	cqSender.setup();
}

void loop()
{
	while (!Serial.available()) {
		;
	}
	String str = Serial.readStringUntil('$');
	cqSender.setMessage(str);
	cqSender.sendBlocking();
}
