#ifndef __Fans_H__
#define __Fans_H__

#include <Arduino.h>
#include "Pins.h"

namespace Fans {

	void setup()
	{
		pinMode(FAN_PWM_PIN, OUTPUT);
	}

	void update()
	{
		yield();
	}

};
#endif // __Fans_H__