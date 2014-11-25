#ifndef _I2C_DEV_H
#define _I2C_DEV_H

#include <Generic.h>
#include "typedef.h"
#include "i2c-sw.h"

enum Si571_REG {
    A_HS_N1 = 7,
    A_N1_RFREQ4,
    A_RFREQ3,
    A_RFREQ2,
    A_RFREQ1,
    A_RFREQ0,

    A_HS_N1_7PPM,
    A_N1_RFREQ4_7PPM,
    A_RFREQ3_7PPM,
    A_RFREQ2_7PPM,
    A_RFREQ1_7PPM,
    A_RFREQ0_7PPM,

    A_RFMC = 135,
    A_FDCO = 137
};

enum HS_DIV_lst {
    HS_4 = 0,
    HS_5, //1
    HS_6, //2
    HS_7, //3
    HS_9 = 5,
    HS_11 = 7
};

typedef struct {
    I2C_param I2Cp;
    BYTE dcodiv;
    BYTE clkdiv;
    UINT64 freq;
} vcxodev_t;

#define SI571_I2C_ADD	 (0x49 << 1 )		// I2C slave address 8bit= (7bit<<1) + 0

#define D_HS_N1 	 (((V_HSDiv & 0x07) << 5)  |  ( V_N1 >> 2  ))
#define D_N1_RFREQ4	 (((V_N1 & 0x03) << 6)  |  ( V_RFreq.v[4]))
#define D_RFREQ3	 (V_RFreq.v[3])
#define D_RFREQ2	 (V_RFreq.v[2])
#define D_RFREQ1	 (V_RFreq.v[1])
#define D_RFREQ0         (V_RFreq.v[0])

#define D_HS_N1_7PPM 	 D_HS_N1
#define D_N1_RFREQ4_7PPM D_N1_RFREQ4
#define D_RFREQ3_7PPM	 D_RFREQ3
#define D_RFREQ2_7PPM	 D_RFREQ2
#define D_RFREQ1_7PPM	 D_RFREQ1
#define D_RFREQ0_7PPM    D_RFREQ0

BYTE vcxo_init(vcxodev_t *v);
void vcxo_enable(vcxodev_t *dev);

#endif

// EOF

