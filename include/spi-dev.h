#ifndef _SPI_DEV_H
#define _SPI_DEV_H

#include <Generic.h>
#include "spi-sw.h"

#define MUX_CHAN_TEMP1      0
#define MUX_CHAN_TEMP2      1
#define MUX_CHAN_1V0        2
#define MUX_CHAN_1V8        4
#define MUX_CHAN_2V5        5
#define MUX_CHAN_3V3        6
#define MUX_CHAN_3V6        7

#define ADDR_SFP_TEMPMSB    0x160
#define ADDR_SFP_TEMPLSB    0x161

typedef struct {
    SPI_param SPIp;
    UINT8 ncmd;             // number of commands
    UINT32 cmds[16];        // command sequence
} plldev_t;

typedef struct {
    SPI_param SPIp;
    SPI_pin DOUT;
} muxdev_t;

typedef struct {
    SPI_param SPIp;
} adcgain_t;

typedef struct {
    SPI_param SPIp;
} fpga_t;

typedef struct {
    SPI_param SPIp;
} sfp_t;

void pll_enable(plldev_t *dev);

void mux_init(void);
void mux_select(BYTE channel);
UINT mux_getout(BYTE channel);

void adcgain_init(void);
void adcgain_write(UINT8 data);

void fpga_init(void);
UINT32 fpga_read(UINT16 addr);
void fpga_write(UINT16 data, UINT16 addr);

void sfp_init(void);
UINT32 sfp_read(UINT16 addr);

#endif

// EOF

