#ifndef __Indicators_H__
#define __Indicators_H__

#include <Arduino.h>
#include <FastLED.h>

#include "Pins.h"
#include "CAN.h"

#define NUM_LEDS    188
#define BRIGHTNESS  192
#define COLOR_ORDER GRB
#define UPDATES_PER_SECOND 100

namespace Indicators {

	CRGB indicator_buffer[NUM_LEDS];
	
	void setup()
	{
		pinMode(FAN_R_PIN, OUTPUT);
		pinMode(FAN_G_PIN, OUTPUT);
		pinMode(FAN_B_PIN, OUTPUT);

		pinMode(PACK_R_PIN, OUTPUT);
		pinMode(PACK_G_PIN, OUTPUT);
		pinMode(PACK_B_PIN, OUTPUT);

		FastLED.addLeds<APA102, LED_DATA_PIN, LED_CLOCK_PIN, COLOR_ORDER>(indicator_buffer, NUM_LEDS).setCorrection(TypicalLEDStrip);
		FastLED.setBrightness(BRIGHTNESS);
	}

	void setTemp(uint8_t temp)
	{

	}

	void setSOC(uint8_t percentage)
	{

	}

	void setSBXState(uint8_t sbx, bool state)
	{

	}


	void update()
	{	
		//Read state of charge from CAN
		//setSOC();

		FastLED.show();
		FastLED.delay(1000 / UPDATES_PER_SECOND);
		yield();

	}
};


#endif // __Indicators_H__
