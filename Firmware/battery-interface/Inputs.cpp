#include "Inputs.h"

namespace Inputs {
    
    bool sbx_sense_right;
    bool sbx_sense_left;
    bool contactor_sense_right;
    bool contactor_sense_left;
    bool precharge_en_sense_right;
    bool precharge_en_sense_left;
    bool charge_sense_right;
    bool charge_sense_left;

    Bounce bounce_sbx_sense_right = Bounce(SBX_SENSE_RIGHT_PIN, DEBOUNCE_TIME);
    Bounce bounce_sbx_sense_left = Bounce(SBX_SENSE_LEFT_PIN, DEBOUNCE_TIME);

    Bounce bounce_contactor_sense_right = Bounce(CONTACTOR_SENSE_RIGHT_PIN, DEBOUNCE_TIME);
    Bounce bounce_contactor_sense_left = Bounce(CONTACTOR_SENSE_LEFT_PIN, DEBOUNCE_TIME);

    Bounce bounce_precharge_en_sense_right = Bounce(PRECHARGE_EN_SENSE_RIGHT_PIN, DEBOUNCE_TIME);
    Bounce bounce_precharge_en_sense_left = Bounce(PRECHARGE_EN_SENSE_LEFT_PIN, DEBOUNCE_TIME);

    Bounce bounce_charge_sense_right = Bounce(CHARGE_SENSE_RIGHT_PIN, DEBOUNCE_TIME);
    Bounce bounce_charge_sense_left = Bounce(CHARGE_SENSE_LEFT_PIN, DEBOUNCE_TIME);
    
    void setup() {
        
        sbx_sense_right = false;
        sbx_sense_left = false;
        contactor_sense_right = false;
        contactor_sense_left = false;
        precharge_en_sense_right = false;
        precharge_en_sense_left = false;
        charge_sense_right = false;
        charge_sense_left = false;

        pinMode(SBX_SENSE_RIGHT_PIN, INPUT);
        pinMode(SBX_SENSE_LEFT_PIN, INPUT);

        pinMode(CONTACTOR_SENSE_RIGHT_PIN, INPUT);
        pinMode(CONTACTOR_SENSE_LEFT_PIN, INPUT);

        pinMode(PRECHARGE_EN_SENSE_RIGHT_PIN, INPUT);
        pinMode(PRECHARGE_EN_SENSE_LEFT_PIN, INPUT);

        pinMode(CHARGE_SENSE_RIGHT_PIN, INPUT);
        pinMode(CHARGE_SENSE_LEFT_PIN, INPUT);
    }

    void read() {

        bounce_sbx_sense_right.update();
        sbx_sense_right = !bounce_sbx_sense_right.read();

        bounce_sbx_sense_left.update();
        sbx_sense_left = !bounce_sbx_sense_left.read();

        bounce_contactor_sense_right.update();
        contactor_sense_right = !bounce_contactor_sense_right.read();

        bounce_contactor_sense_left.update();
        contactor_sense_left = !bounce_contactor_sense_left.read();

        bounce_precharge_en_sense_right.update();
        precharge_en_sense_right = bounce_precharge_en_sense_right.read();

        bounce_precharge_en_sense_left.update();
        precharge_en_sense_left = bounce_precharge_en_sense_left.read();

        bounce_charge_sense_right.update();
        charge_sense_right = !bounce_charge_sense_right.read();

        bounce_charge_sense_left.update();
        charge_sense_left = !bounce_charge_sense_left.read();

        yield();
    }

    /*
     * Returns true if the SBX Right connector is plugged in
     * @return bool
     */
    bool isSbxRightPresent(){
        return sbx_sense_right;
    }
    
    /*
     * Returns true if the SBX Left connector is plugged in
     * @return bool
     */
    bool isSbxLeftPresent(){
        return sbx_sense_left;
    }
    
    /*
     * Returns true if the contactor 1 is closed. Via secondary contact
     * @return bool
     */
    bool isContactorRightClosed(){
        return contactor_sense_right;
    }

    /*
     * Returns true if contactor 2 is closed. Via secondary contact
     * @return bool
     */
    bool isContactorLeftClosed(){
        return contactor_sense_left;
    }

    /*
     * Returns true if precharge 1 is on.
     * @return bool
     */
    bool isPrechargeRightOn(){
        return precharge_en_sense_right;
    }

    /*
     * Returns true if precharge 2 is on.
     * @return bool
     */
    bool isPrechargeLeftOn(){
        return precharge_en_sense_left;
    }

    /*
     * Returns true if circuit 1 (via SBX Right) is charged (precharge complete).
     * @return bool
     */
    bool isChargedRight(){
        return charge_sense_right;
    }

    /*
     * Returns true if circuit 2 (via SBX Left) is charged (precharge complete).
     * @return bool
     */
    bool isChargedLeft(){
        return charge_sense_left;
    }
};
