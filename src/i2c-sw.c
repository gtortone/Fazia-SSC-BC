#include "i2c-sw.h"
#include "board.h"          // for delay_us

#include <p33Fxxxx.h>       // for delay_us
#include <libpic30.h>       // for delay_us

void I2C_dly() {
    __delay_us(5);
}

inline void I2C_bw(I2C_pin pin, BOOL s) {

    if (s == 1)
        (*(pin.tris) |= (1 << pin.npin));
    else
        (*(pin.tris) &= (~(1 << pin.npin)));
}

inline BOOL I2C_br(I2C_pin pin) {
    return ((*(pin.tris) >> pin.npin) & 1);
}

void I2C_init(I2C_param *p) {

    I2C_bw(p->SDA, 1);
    I2C_bw(p->SCL, 1);
}

void I2C_start(I2C_param *p) {
    I2C_bw(p->SDA, 1); // i2c start bit sequence
    I2C_dly();
    I2C_bw(p->SCL, 1);
    I2C_dly();
    I2C_bw(p->SDA, 0);
    I2C_dly();
    I2C_bw(p->SCL, 0);
    I2C_dly();
}

void I2C_stop(I2C_param *p) {
    I2C_bw(p->SDA, 0); // i2c stop bit sequence
    I2C_dly();
    I2C_bw(p->SCL, 1);
    I2C_dly();
    I2C_bw(p->SDA, 1);
    I2C_dly();
}

BYTE I2C_rx(I2C_param *p, char ack) {

    char x, d = 0;

    I2C_bw(p->SDA, 1);
    for (x = 0; x < 8; x++) {
        d <<= 1;
        do {
            I2C_bw(p->SCL, 1);
        } while (I2C_br(p->SCL) == 0); // wait for any SCL clock stretching
        I2C_dly();

        if (I2C_br(p->SDA)) d |= 1;
        I2C_bw(p->SCL, 0);
    }

    if (ack) I2C_bw(p->SDA, 0);
    else I2C_bw(p->SDA, 1);

    I2C_bw(p->SCL, 1);
    I2C_dly(); // send (N)ACK bit
    I2C_bw(p->SCL, 0);
    I2C_bw(p->SDA, 1);
    return d;
}

BOOL I2C_tx(I2C_param *p, unsigned char d) {

    char x;
    static BOOL b;

    for (x = 8; x; x--) {
        if (d & 0x80) I2C_bw(p->SDA, 1);
        else I2C_bw(p->SDA, 0);
        I2C_bw(p->SCL, 1);
        I2C_dly();
        d <<= 1;
        I2C_bw(p->SCL, 0);
        I2C_dly();
    }
    I2C_bw(p->SDA, 1);
    I2C_bw(p->SCL, 1);
    I2C_dly();
    b = I2C_br(p->SDA); // possible ACK bit
    I2C_bw(p->SCL, 0);
    return b;
}
