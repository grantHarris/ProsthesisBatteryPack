#ifndef __Indicators_H__
#define __Indicators_H__

#include <Arduino.h>
#include <FastLED.h>

#include "Pins.h"
#include "CAN.h"

#define NUM_LEDS 188

#define COLOR_ORDER GRB
#define UPDATES_PER_SECOND 100

namespace Indicators {	
	void setup();
	void setSOC(uint8_t percentage);
	void setSBXState(uint8_t sbx, bool state);
	void update();
};


#endif // __Indicators_H__
