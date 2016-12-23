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
#define ROLLING_COUNTER_ADDR 0x502

#define HEARTBEAT_TIMEOUT 500
  
struct temp_t {
    int avg;
    int low;
    int high;
    int speed;
};

struct pack_t {
    unsigned int soc;
    unsigned int health;
    int voltage;
    int current;
    int current_adc1;
    int current_adc2;
};

struct heartbeat_t {
    unsigned int last_value;
    unsigned long age;
};

namespace CAN {
    void setup();
    void setHeartbeat(uint8_t rolling_counter);
    void read();
    temp_t getTempState();
    pack_t getPackState();
    bool isCurrent();
};

#endif // __CAN_H__
