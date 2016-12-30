#ifndef __Indicators_H__
#define __Indicators_H__

#include <Arduino.h>
#include <FastLED.h>

#include "Pins.h"
#include "CAN.h"
#include "Inputs.h"

#define NUM_LEDS 188

#define COLOR_ORDER BGR
#define UPDATES_PER_SECOND 100

namespace Indicators {	
	void setup();
  void setupMapping();
  
  void update();
  void updateIndicators();
  
	void setSOC(uint8_t percentage);
	void setSBXState(uint8_t sbx, bool state);

  void setPackCurrent(float amps);
  void setPackTemp(temp_t temp);
  
  class LEDSection {
    public:
      LEDSection(uint16_t _offset, uint16_t _size);
      void setColor(CHSV _color);
      void render();
      void renderColorFill(CHSV _color);
      void clear();

      CHSV color;
      uint16_t *map;
      
    private:
      uint16_t offset;
      uint16_t size;
  };

  class PowerChannel {
    public:
      PowerChannel(LEDSection *sbxLower, LEDSection *sbxUpper, LEDSection *bracket, LEDSection *arrow);
      
      //Is the SBX (big red connector) plugged in? 
      void setInsertionState(bool state);
      void setContactorState(bool state);
      void setPrechargeState(bool state);
      void setChargedState(bool state);
    private:
      LEDSection *_sbxLower;
      LEDSection *_sbxUpper;
      LEDSection *_arrow;
      LEDSection *_bracket
  };
}
#endif // __Indicators_H__

