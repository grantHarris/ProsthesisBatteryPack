#ifndef __Buzzer_H__
#define __Buzzer_H__

#include <Arduino.h>
#include "Pins.h"

namespace Buzzer {
	static bool state;

	void setup()
	{
		pinMode(BUZZER_PIN, OUTPUT);
	}

	void toggle(bool state_in)
	{
		state = state_in;
	}

	void update()
	{
		if(state){
			tone(BUZZER_PIN, 2408);
			delay(500);
			tone(BUZZER_PIN, 0);
			delay(500);
		}else{
			tone(BUZZER_PIN, 0);
		}
		yield();
	}

	bool getState(){
		return state;
	}
}

#endif // __Fans_H__
