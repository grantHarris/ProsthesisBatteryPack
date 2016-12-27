#include "CAN.h"

namespace CAN {
	
	temp_t temp;
	pack_t pack;
	heartbeat_t heartbeat;

    FlexCAN CANbus(CAN_SPEED);
    CAN_message_t rx_msg;

	void setup()
	{
	    heartbeat.timestamp = 0;
	    CANbus.begin();
	}

	void setHeartbeat(uint8_t rolling_counter){
	    if(heartbeat.last_value != rolling_counter){
	        heartbeat.last_value = rolling_counter;
	        heartbeat.timestamp = millis();
	    }
	}
	/*
	    pack soc, pack amphours, pack health, relay state
	    high/low/avg temp, req fan speed
	    pack current, current adc1/adc2

	    read the pack stage of charge
	    read the pack current consumption (overall)
	    read the output1 current
	    read the output2 current
	    read the pack temp avg/max
	    read requested fan speed
	    pack state of health
	*/
	void read()
	{
	    while (CANbus.read(rx_msg)) {
	        switch(rx_msg.id){
	            case ROLLING_COUNTER_ADDR:
	                /*
	                    The BMS sends a heartbeat every 100ms.
	                    If the heartbeat is missing we know the CAN bus has locked up.
	                */
	                setHeartbeat(rx_msg.buf[0]);
	            break;
	            case TEMP_ADDR:
	                temp.avg = rx_msg.buf[0];
	                temp.low = rx_msg.buf[1];
	                temp.high = rx_msg.buf[2];
	                temp.speed = rx_msg.buf[3];
	            break;
	            case PACK_ADDR:
	                pack.soc = rx_msg.buf[0];
	                pack.health = rx_msg.buf[1];
	                pack.voltage = rx_msg.buf[2];
	                pack.current = rx_msg.buf[3];
	                pack.current_adc1 = rx_msg.buf[4];
	                pack.current_adc2 = rx_msg.buf[5];
	            break;

	        }
	    }
	    yield();
	}

	/*
	 * Get the latest avg, low, and high pack temp
	 * @return temp_t
	 */
	temp_t getTempState()
	{
	    return temp;
	}

	/*
	 * Get the soc, health, voltage, current, current_adc1, current_adc2
	 * @return pack_t
	 */
	pack_t getPackState()
	{
	    return pack;
	}
 
  /* 
   * Return age of last heartbeat
   * @return unsigned long
   */
  unsigned long heartbeatAge(){
    return millis() - heartbeat.timestamp;
  }

	/* 
   * Return currentness of CAN data
	 * @return bool
	 */
	bool isCurrent(){
	    if(heartbeatAge() < HEARTBEAT_TIMEOUT){
	        return true;
	    }else{
	        return false;
	    }
	}
}

