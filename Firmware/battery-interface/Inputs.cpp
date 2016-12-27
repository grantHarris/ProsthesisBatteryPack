#include "Inputs.h"

namespace Inputs {
    
    bool sbx_sense_1;
    bool sbx_sense_2;
    bool contactor_sense_1;
    bool contactor_sense_2;
    bool precharge_en_sense_1;
    bool precharge_en_sense_2;
    bool charge_sense_1;
    bool charge_sense_2;

    Bounce bounce_sbx_sense_1 = Bounce(SBX_SENSE_1_PIN, DEBOUNCE_TIME);
    Bounce bounce_sbx_sense_2 = Bounce(SBX_SENSE_2_PIN, DEBOUNCE_TIME);

    Bounce bounce_contactor_sense_1 = Bounce(CONTACTOR_SENSE_1_PIN, DEBOUNCE_TIME);
    Bounce bounce_contactor_sense_2 = Bounce(CONTACTOR_SENSE_2_PIN, DEBOUNCE_TIME);

    Bounce bounce_precharge_en_sense_1 = Bounce(PRECHARGE_EN_SENSE_1_PIN, DEBOUNCE_TIME);
    Bounce bounce_precharge_en_sense_2 = Bounce(PRECHARGE_EN_SENSE_1_PIN, DEBOUNCE_TIME);

    Bounce bounce_charge_sense_1 = Bounce(CHARGE_SENSE_1_PIN, DEBOUNCE_TIME);
    Bounce bounce_charge_sense_2 = Bounce(CHARGE_SENSE_2_PIN, DEBOUNCE_TIME);
    
    void setup() {
        
        sbx_sense_1 = false;
        sbx_sense_2 = false;
        contactor_sense_1 = false;
        contactor_sense_2 = false;
        precharge_en_sense_1 = false;
        precharge_en_sense_2 = false;
        charge_sense_1 = false;
        charge_sense_2 = false;

        pinMode(SBX_SENSE_1_PIN, INPUT);
        pinMode(SBX_SENSE_2_PIN, INPUT);

        pinMode(CONTACTOR_SENSE_1_PIN, INPUT);
        pinMode(CONTACTOR_SENSE_2_PIN, INPUT);

        pinMode(PRECHARGE_EN_SENSE_1_PIN, INPUT);
        pinMode(PRECHARGE_EN_SENSE_2_PIN, INPUT);

        pinMode(CHARGE_SENSE_1_PIN, INPUT);
        pinMode(CHARGE_SENSE_2_PIN, INPUT);
    }

    void read() {

        bounce_sbx_sense_1.update();
        sbx_sense_1 = !bounce_sbx_sense_1.read();

        bounce_sbx_sense_2.update();
        sbx_sense_2 = !bounce_sbx_sense_2.read();

        bounce_contactor_sense_1.update();
        contactor_sense_1 = !bounce_contactor_sense_1.read();

        bounce_contactor_sense_2.update();
        contactor_sense_2 = !bounce_contactor_sense_2.read();

        bounce_precharge_en_sense_1.update();
        precharge_en_sense_1 = !bounce_precharge_en_sense_1.read();

        bounce_precharge_en_sense_2.update();
        precharge_en_sense_2 = !bounce_precharge_en_sense_2.read();

        bounce_charge_sense_1.update();
        charge_sense_1 = !bounce_charge_sense_1.read();

        bounce_charge_sense_2.update();
        charge_sense_2 = !bounce_charge_sense_2.read();

        yield();
    }

    /*
     * Returns true if the SBX 1 connector is plugged in
     * @return bool
     */
    bool isSbx1Present(){
        return sbx_sense_1;
    }
    
    /*
     * Returns true if the SBX 2 connector is plugged in
     * @return bool
     */
    bool isSbx2Present(){
        return sbx_sense_2;
    }
    
    /*
     * Returns true if the contactor 1 is closed. Via secondary contact
     * @return bool
     */
    bool isContactor1Closed(){
        return contactor_sense_1;
    }

    /*
     * Returns true if contactor 2 is closed. Via secondary contact
     * @return bool
     */
    bool isContactor2Closed(){
        return contactor_sense_2;
    }

    /*
     * Returns true if precharge 1 is on.
     * @return bool
     */
    bool isPrecharge1On(){
        return precharge_en_sense_1;
    }

    /*
     * Returns true if precharge 2 is on.
     * @return bool
     */
    bool isPrecharge2On(){
        return precharge_en_sense_2;
    }

    /*
     * Returns true if circuit 1 (via SBX 1) is charged (precharge complete).
     * @return bool
     */
    bool isCharged1(){
        return charge_sense_1;
    }

    /*
     * Returns true if circuit 2 (via SBX 2) is charged (precharge complete).
     * @return bool
     */
    bool isCharged2(){
        return charge_sense_2;
    }
};
