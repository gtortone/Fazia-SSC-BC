#ifndef _SW_I2C_H_
#define _SW_I2C_H_

#include <Generic.h>

typedef struct {
	volatile UINT *port;
	volatile UINT *tris;
	BYTE npin;
} I2C_pin;

typedef struct {
    I2C_pin SDA;
    I2C_pin SCL;
} I2C_param;

void I2C_dly();
inline void I2C_bw(I2C_pin pin, BOOL s);
inline BOOL I2C_br(I2C_pin pin);
void I2C_init(I2C_param *p);
void I2C_start(I2C_param *p);
void I2C_stop(I2C_param *p);
BYTE I2C_rx(I2C_param *p, char ack);
BOOL I2C_tx(I2C_param *p, unsigned char d);

#endif

// EOF
