
#ifndef __Inputs_H__
#define __Inputs_H__

#include <Arduino.h>
#include <Bounce.h>
#include "Pins.h"

#define DEBOUNCE_TIME 20

namespace Inputs {
  void setup();
  void read();
};

#endif // __Inputs_H__

