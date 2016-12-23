#include "Indicators.h"

namespace Indicators {
	
	CRGB buf[NUM_LEDS];

	void setup()
	{
		pinMode(FAN_R_PIN, OUTPUT);
		pinMode(FAN_G_PIN, OUTPUT);
		pinMode(FAN_B_PIN, OUTPUT);

		pinMode(PACK_R_PIN, OUTPUT);
		pinMode(PACK_G_PIN, OUTPUT);
		pinMode(PACK_B_PIN, OUTPUT);

		FastLED.addLeds<APA102, LED_DATA_PIN, LED_CLOCK_PIN, COLOR_ORDER, DATA_RATE_MHZ(6)>(buf, NUM_LEDS).setCorrection(TypicalLEDStrip);
	}

	void setSOC(uint8_t percentage)
	{
		

//		left side thingy
//		- 0 - 5
//		- 10 - 15
//
//		left side jut out
//		- 6-9
//
//		right side thingy
//		- 21, 20, 19, 18, 17, 16
//		- 31, 30, 29, 28, 27, 26
//
//		right side jut out
//		- 22-25 (reverse)
//
//		levels (top down)
//		1
//		- 32, 33
//		2
//		- 34, 36, 37, 35
//		3
//		- 38, 40, 41, 39
//		4
//		- 42, 44, 45, 43
//		5
//		- 46, 48, 49, 47
//		6
//		- 50, 52, 53, 51
//		7
//		- 54, 56, 57, 55
//		8
//		- 58, 59, 60, 61, 62
//		9
//		- 63, 64, 65, 66, 67
//		10
//		- 68, 69, 70, 71, 72
//		11
//		- 73, 74, 75, 76, 77
//		

	}

	void setSBXState(uint8_t sbx, bool state)
	{

	}


	void update()
	{
		// if(CANFoo::isCurrent()){

		// 	CANFoo::pack_t pack = CANFoo::getPackState();
		// 	CANFoo::temp_t temp = CANFoo::getTempState();
			
		// }else{
		// 	/* 
		// 		No CAN data or outdated data. Can't display state of charge, temperature, etc
		// 		Display error on display
		// 	*/
		// }

		FastLED.show();
		FastLED.delay(1000 / UPDATES_PER_SECOND);
		yield();

	}
};
