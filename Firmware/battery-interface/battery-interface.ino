#include <Scheduler.h>
#include "battery-interface.h"

void setup(void){

	Serial.begin(9600);
	
	Scheduler.start(CAN::setup, CAN::read);
//  Scheduler.start(Inputs::setup, Inputs::read);
//  Scheduler.start(Fans::setup, Fans::update);
//  Scheduler.start(Indicators::setup, Indicators::update);
//  Scheduler.start(Buzzer::setup, Buzzer::update);

}


void loop(void){
}

