#ifndef __CAN_H__
#define __CAN_H__

#include <Arduino.h>
#include <FlexCAN.h>

#define CAN_SPEED 500000

/*
0 - avg temp
1 - low temp
2 - high temp
3 - req fan speed
*/
#define TEMP_ADDR 0x500

/*
0 - pack soc
1 - pack health
2 - pack summed v
3 - pack current
4 - current adc1
5 - current adc2
6 - relay state
*/
#define PACK_ADDR 0x501
#define HEARTBEAT_ADDR 0x502
  
namespace CAN {

    struct temp_t {
        int avg;
        int low;
        int high;
        int speed;
    } temp;

    struct pack_t{
        int soc;
        int health;
        int voltage;
        int current;
        int current_adc1;
        int current_adc2;
    } pack;

    bool is_fresh;

    FlexCAN CANbus(CAN_SPEED);
    static CAN_message_t rx_msg;

    void setup()
    {   is_fresh = false;
        CANbus.begin();
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
                case HEARTBEAT_ADDR:

                break;

            }
        }
        yield();
    }

    /*
     * Get the latest avg, low, and high pack temp
     * @return temp_t struct
     */
    temp_t getTemp()
    {
        return temp;
    }

    /*
     * Get the soc, health, voltage, current, current_adc1, current_adc2
     * @return pack_t struct
     */
    pack_t getPack()
    {
        return pack;
    }

    bool isFresh(){
        return is_fresh;
    }

};

#endif // __CAN_H__
