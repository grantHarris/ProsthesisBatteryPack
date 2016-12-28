#ifndef __Inputs_H__
#define __Inputs_H__

#include <Arduino.h>
#include <Bounce.h>
#include "Pins.h"

#define DEBOUNCE_TIME 250

namespace Inputs {
	void setup();
  	void read();
    bool isSbxRightPresent();
    bool isSbxLeftPresent();
    bool isContactorRightClosed();
    bool isContactorLeftClosed();
    bool isPrechargeRightOn();
    bool isPrechargeLeftOn();
    bool isChargedRight();
    bool isChargedLeft();
};

#endif // __Inputs_H__

