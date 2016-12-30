#include "Indicators.h"

namespace Indicators {
    CRGB buf[NUM_LEDS];
    CRGB smoothedBuf[NUM_LEDS];

    // SOC Map
    LEDSection *socLeftBracket;     LEDSection *socLeftArrow;
    LEDSection *socRightBracket;    LEDSection *socRightArrow;
    LEDSection *levels[11];

    // SBX Map
    LEDSection *sbxRightUpper;      LEDSection *sbxRightLower;
    LEDSection *sbxLeftUpper;       LEDSection *sbxLeftLower;

    // ARROWS
    LEDSection *arrowRight;         LEDSection *arrowLeft;

    PowerChannel *sbxRight;
    PowerChannel *sbxLeft;

    // SmoothedControls
    float smoothedSOCPercentage = 0.;
    float smoothedSBXRightState = 0.;
    float smoothedSBXLeftState = 0.;
  
    void setup()
    {  
        pinMode(FAN_R_PIN, OUTPUT);
        pinMode(FAN_G_PIN, OUTPUT);
        pinMode(FAN_B_PIN, OUTPUT);

        pinMode(PACK_R_PIN, OUTPUT);
        pinMode(PACK_G_PIN, OUTPUT);
        pinMode(PACK_B_PIN, OUTPUT);

        FastLED.addLeds<APA102, LED_DATA_PIN, LED_CLOCK_PIN, COLOR_ORDER, DATA_RATE_MHZ(6)>(buf, NUM_LEDS).setCorrection(TypicalLEDStrip);
    
        // Mapping
        setupMapping();

        // Initialize Smoothed Controls
        smoothedSOCPercentage = 0.;
        smoothedSBXRightState = 0.;
        smoothedSBXLeftState = 0.;

        // Setup SBX Colors
        sbxRightUpper->setColor(CHSV(0,0,0));
        sbxRightLower->setColor(CHSV(0,0,0));
        sbxLeftUpper->setColor(CHSV(0,0,0));
        sbxLeftLower->setColor(CHSV(0,0,0));

        sbxRight = new PowerChannel(sbxRightLower, sbxRightUpper, socRightBracket, socRightArrow);
        sbxLeft = new PowerChannel(sbxLeftLower, sbxLeftUpper, socLeftBracket, socLeftArrow);
    }
  
    void setSOC(uint8_t percentage)
    { 
        float alpha = 0.0075;
        smoothedSOCPercentage = ((1-alpha) * smoothedSOCPercentage) + (alpha * (float)percentage);
        
        int batteryLevelIdx = smoothedSOCPercentage / 10 + 1;
        
        // Setup level colors
        for( int i = 0; i < 2; i++) levels[i]->setColor(CHSV(0,255,150));     // Red
        for( int i = 2; i < 3; i++) levels[i]->setColor(CHSV(60,255,150));    // Yellow
        for( int i = 3; i < 11; i++) levels[i]->setColor(CHSV(97,255,150));   // Green
            
        // SOC
        // Now turn off some of the levels (abstract to a draw later/next)
        for (int i = 0; i < 11; i++) {
          levels[i]->clear();
        }
        
        for (int i = 0; i <= batteryLevelIdx; i++) {
          levels[i]->render();
        }
    }
    
    /*
        Sets the 12V strip illuminating the fan area
        Visualizes the current pack temperature 
    */
    void setPackTemp(temp_t temp)
    {

    }

    /*
        Sets the 12V strip illuminating the battery pack main chamber
        Visulizes current flowing out of the pack
    */
    void setPackCurrent(float amps)
    {
        //Todo. cooler colours for lower amperages, warmer colors for higher amperages
        //Brightness?
        //Min 0, max should be the resonable max current consumption of the motors with buffer room.
        //Perhaps set to main pack fuse rating first
        //analogWrite(PACK_R_PIN, 0);
        //analogWrite(PACK_G_PIN, 0);
        //analogWrite(PACK_B_PIN, 0);
    }
  
    void update()
    {
        sbxRight->setInsertionState(Inputs::isSbxRightPresent());
        sbxLeft->setInsertionState(Inputs::isSbxLeftPresent());

        sbxRight->setContactorState(Inputs::isContactorRightClosed());
        sbxLeft->setContactorState(Inputs::isContactorLeftClosed());
        
        sbxRight->setPrechargeState(Inputs::isPrechargeRightOn());
        sbxLeft->setPrechargeState(Inputs::isPrechargeLeftOn());

        if(CAN::isCurrent()){
            pack_t pack = CAN::getPackState();

            setSOC(pack.soc);
            
            setPackTemp(CAN::getTempState());
        }else{
             /* 
                 No CAN data or outdated data. Can't display state of charge, temperature, etc
                 Display error on display
             */
            Serial.println("No CAN data!");
        }

        updateIndicators();

        FastLED.show();
        FastLED.delay(1000 / UPDATES_PER_SECOND);
        yield();
    }

  void updateIndicators()
  {

    // Update color 
    socLeftBracket->renderColorFill(levels[batteryLevelIdx]->color);
    socRightBracket->renderColorFill(levels[batteryLevelIdx]->color);
    
    socLeftArrow->renderColorFill(levels[batteryLevelIdx]->color);
    socRightArrow->renderColorFill(levels[batteryLevelIdx]->color); 
       
    // SBX
    sbxRightUpper->render();
    sbxRightLower->render();
    sbxLeftUpper->render();
    sbxLeftLower->render();

    // ARROWS
  }

    // LED MAPPING
  void setupMapping() {
    uint8_t i;

    // SBX (SBX is type of connector)  
    uint8_t sbxRightOffset = 0;   
    sbxRightUpper = new LEDSection(sbxRightOffset + 0, 23);
    sbxRightLower = new LEDSection(sbxRightOffset + 23, 24);

    uint8_t sbxLeftOffset = 125;
    sbxLeftUpper = new LEDSection(sbxLeftOffset + 0, 23);
    sbxLeftLower = new LEDSection(sbxLeftOffset + 23, 24);    

    // STATE OF CHARGE INDICATOR (SOC)
    uint8_t socOffset = 47;

    // LEFT BRACKET 
    socLeftBracket = new LEDSection(socOffset + 0, 12);
    // skips some LEDs, mapping adjust)
    for ( i = 6; i < 12; i++) socLeftBracket->map[i] = i+4;

    // LEFT ARROW
    socLeftArrow = new LEDSection(socOffset + 6, 4);

    // RIGHT BRACKET
    socRightBracket = new LEDSection(socOffset + 16, 12);
    
    // skips some LEDs, mapping adjust)
    for ( i = 6; i < 12; i++) socRightBracket->map[i] = i+4;

    // RIGHT ARROW
    socRightArrow = new LEDSection(socOffset + 22, 4);

    // LEVELS
    levels[0] = new LEDSection(socOffset + 32, 2);
    levels[1] = new LEDSection(socOffset + 34, 4);   
    levels[2] = new LEDSection(socOffset + 38, 4);  
    levels[3] = new LEDSection(socOffset + 42, 4);        
    levels[4] = new LEDSection(socOffset + 46, 4);
    levels[5] = new LEDSection(socOffset + 50, 4);
    levels[6] = new LEDSection(socOffset + 54, 4);
    levels[7] = new LEDSection(socOffset + 58, 5);   
    levels[8] = new LEDSection(socOffset + 63, 5);
    levels[9] = new LEDSection(socOffset + 68, 5);        
    levels[10] = new LEDSection(socOffset + 73, 5);
  }


  // --------------------------------------------------------------
  // LED SECTION

  LEDSection::LEDSection(uint16_t _offset, uint16_t _size){
    size = _size;
    offset = _offset;
    color = CHSV(0,0,0);
    map = new uint16_t[size];
    for (int i = 0; i < size; i++)  map[i] = i;
  }

  void LEDSection::setColor(CHSV _color){
    color = _color;    
  }

  void LEDSection::clear(){
    for(int i = 0; i < size; i++) {
      buf[offset + map[i]] = CHSV(0,0,0);   
    }    
  }

  void LEDSection::render(){
    for(int i = 0; i < size; i++) {
      buf[offset + map[i]] = color;   
    } 
  }

  void LEDSection::renderColorFill(CHSV _color){
    color = _color;
    for(int i = 0; i < size; i++) {
      buf[offset + map[i]] = _color;   
    } 
  }
  
  //PowerChannel
  PowerChannel::PowerChannel(LEDSection *sbxLower, LEDSection *sbxUpper, LEDSection *bracket, LEDSection *arrow) {
    _sbxLower = sbxLower;
    _sbxUpper = sbxUpper;
    _bracket = bracket;
    _arrow = arrow;
  }

  /*
   * Illuminates the lower SBX ring when SBX connector plugged in.
   * @Input bool
   */
  void PowerChannel::setInsertionState(bool state) {
    if(state){
      _sbxLower->setColor(CHSV(60,255,255));
    }else{
     _sbxLower->setColor(CHSV(0,0,0)); 
    }
  }

 /*
  * Illuminates the upper SBX ring when the contactor's secondary contact is closed.
  * This means the output is live.
  * @Input bool
  */ 
  void PowerChannel::setContactorState(bool state) {
    if(state){
      _sbxUpper->setColor(CHSV(0,255,150));
    }else{
     _sbxUpper->setColor(CHSV(0,0,0)); 
    }
  }

  /*
  * Illuminates arrow. Means the precharge is on
  * This means the output is live.
  * @Input bool
  */  
  void PowerChannel::setPrechargeState(bool state){
    
  }

   /*
  * Illuminates the upper SBX ring when the contactor's secondary contact is closed.
  * This means the output is live.
  * @Input bool
  */ 
  void PowerChannel::setChargedState(bool state){
    
  }


  
 };
