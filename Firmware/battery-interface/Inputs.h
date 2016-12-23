
#ifndef __Inputs_H__
#define __Inputs_H__

#include <Arduino.h>
#include <Bounce.h>
#include "Pins.h"

#define DEBOUNCE_TIME 20

namespace Inputs {
	void setup();
  	void read();
    bool isSbx1Present();
    bool isSbx2Present();
    bool isContactor1Closed();
    bool isContactor2Closed();
    bool isPrecharge1On();
    bool isPrecharge2On();
    bool isCharged1();
    bool isCharged2();
};

#endif // __Inputs_H__
