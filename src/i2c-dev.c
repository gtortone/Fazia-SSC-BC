#include "i2c-dev.h"
#include "typedef.h"

BYTE vcxo_init(vcxodev_t *v) {

    BYTE V_HSDiv;
    BYTE V_N1;
    UINT64_VAL V_RFreq;
    BYTE Error = 0;

    V_HSDiv = v->clkdiv;
    V_N1 = v->dcodiv - 1; //N1 value calculated by excel sheet{1,128} V_N1 value to the register!! {0, 127}
    V_RFreq.Val = v->freq;

    //Freeze M
    I2C_start(&(v->I2Cp));
    Error += I2C_tx(&(v->I2Cp), SI571_I2C_ADD); //SLAVE ADDRESS
    Error += I2C_tx(&(v->I2Cp), A_RFMC); //REGISTER ADDRESS
    Error += I2C_tx(&(v->I2Cp), 0b01100000); //DATA
    I2C_stop(&(v->I2Cp));

    //Freeze DCO
    I2C_start(&(v->I2Cp));
    Error += I2C_tx(&(v->I2Cp), SI571_I2C_ADD); //SLAVE ADDRESS
    Error += I2C_tx(&(v->I2Cp), A_FDCO); //REGISTER ADDRESS
    Error += I2C_tx(&(v->I2Cp), 0b00010000); //DATA
    I2C_stop(&(v->I2Cp));

    //Change RFreq
    I2C_start(&(v->I2Cp));
    Error += I2C_tx(&(v->I2Cp), SI571_I2C_ADD); //SLAVE ADDRESS

    Error += I2C_tx(&(v->I2Cp), A_HS_N1); //REGISTER ADDRESS
    Error += I2C_tx(&(v->I2Cp), D_HS_N1); //DATA

    Error += I2C_tx(&(v->I2Cp), D_N1_RFREQ4);
    Error += I2C_tx(&(v->I2Cp), D_RFREQ3);
    Error += I2C_tx(&(v->I2Cp), D_RFREQ2);
    Error += I2C_tx(&(v->I2Cp), D_RFREQ1);
    Error += I2C_tx(&(v->I2Cp), D_RFREQ0);

    Error += I2C_tx(&(v->I2Cp), D_HS_N1_7PPM);
    Error += I2C_tx(&(v->I2Cp), D_N1_RFREQ4_7PPM);
    Error += I2C_tx(&(v->I2Cp), D_RFREQ3_7PPM);
    Error += I2C_tx(&(v->I2Cp), D_RFREQ2_7PPM);
    Error += I2C_tx(&(v->I2Cp), D_RFREQ1_7PPM);
    Error += I2C_tx(&(v->I2Cp), D_RFREQ0_7PPM);
    I2C_stop(&(v->I2Cp));

    //UnFreeze DCO
    I2C_start(&(v->I2Cp));
    Error += I2C_tx(&(v->I2Cp), SI571_I2C_ADD); //SLAVE ADDRESS
    Error += I2C_tx(&(v->I2Cp), A_FDCO); //REGISTER ADDRESS
    Error += I2C_tx(&(v->I2Cp), 0b00000000); //DATA
    I2C_stop(&(v->I2Cp));

    //Unfreeze M
    I2C_start(&(v->I2Cp));
    Error += I2C_tx(&(v->I2Cp), SI571_I2C_ADD); //SLAVE ADDRESS
    Error += I2C_tx(&(v->I2Cp), A_RFMC); //REGISTER ADDRESS
    Error += I2C_tx(&(v->I2Cp), 0b01000000); //DATA
    I2C_stop(&(v->I2Cp));

    return Error;
}

void vcxo_enable(vcxodev_t *dev) {

    BYTE i = 0;

    I2C_init(&(dev->I2Cp)); //init I2C port

    i = 0; //reset error counter
    while (((vcxo_init(dev) != 0) && (++i < 5))) ; // I2C setup routine
}
