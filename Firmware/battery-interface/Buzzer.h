#ifndef __Buzzer_H__
#define __Buzzer_H__

#include <Arduino.h>
#include "Pins.h"

namespace Buzzer {
	void setup();
	void toggle(bool state_in);
	void update();
	bool getState();
}

#endif // __Fans_H__
