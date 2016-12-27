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
        sbx_sense_1 = bounce_sbx_sense_1.read();

        bounce_sbx_sense_2.update();
        sbx_sense_2 = bounce_sbx_sense_2.read();

        bounce_contactor_sense_1.update();
        contactor_sense_1 = bounce_contactor_sense_1.read();

        bounce_contactor_sense_2.update();
        contactor_sense_2 = bounce_contactor_sense_2.read();

        bounce_precharge_en_sense_1.update();
        precharge_en_sense_1 = bounce_precharge_en_sense_1.read();

        bounce_precharge_en_sense_2.update();
        precharge_en_sense_2 = bounce_precharge_en_sense_2.read();

        bounce_charge_sense_1.update();
        charge_sense_1 = bounce_charge_sense_1.read();

        bounce_charge_sense_2.update();
        charge_sense_2 = bounce_charge_sense_2.read();

        yield();
    }
};

