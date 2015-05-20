#include "spi-dev.h"

#include "board.h"
#include <p33Fxxxx.h>
#include <libpic30.h>

static muxdev_t mux;
static adcgain_t adcgain;
static fpga_t fpga;
static sfp_t sfp;

void pll_enable(plldev_t *dev) {

   UINT8 i;

   SPI_init(&(dev->SPIp));
   for (i = 0; i < dev->ncmd; i++)
      SPI_tx(&(dev->SPIp), dev->cmds[i]);
}

void mux_init(void) {

   //MUX init
   mux.SPIp.SDO.port = &PORTB;
   mux.SPIp.SDO.tris = &TRISB;
   mux.SPIp.SDO.npin = 3;
   mux.SPIp.SDI.port = &LATB;
   mux.SPIp.SDI.tris = &TRISB;
   mux.SPIp.SDI.npin = 2;
   mux.SPIp.SCK.port = &LATB;
   mux.SPIp.SCK.tris = &TRISB;
   mux.SPIp.SCK.npin = 4;
   mux.SPIp.SS.port = &LATA;
   mux.SPIp.SS.tris = &TRISA;
   mux.SPIp.SS.npin = 4;
   mux.SPIp.tx_bitsize = 8;
   mux.SPIp.delay_us = 5;
   mux.DOUT.port = &LATA;
   mux.DOUT.tris = &TRISA;
   mux.DOUT.npin = 1;

   SPI_init(&(mux.SPIp));
}

void mux_select(BYTE channel) {

   SPI_tx(&(mux.SPIp), (1 << channel));
   __delay_ms(5); // time for output stability
}

UINT mux_getout(BYTE channel) {

   mux_select(channel);

   AD1CON1bits.SAMP = 1;
   __delay_us(10);
   AD1CON1bits.SAMP = 0;

   while (!AD1CON1bits.DONE) ;

   return (ADC1BUF0);
}

void adcgain_init(void) {

   //ADC init
   adcgain.SPIp.SDO.port = &PORTB;
   adcgain.SPIp.SDO.tris = &TRISB;
   adcgain.SPIp.SDO.npin = 3;
   adcgain.SPIp.SCK.port = &LATB;
   adcgain.SPIp.SCK.tris = &TRISB;
   adcgain.SPIp.SCK.npin = 4;
   adcgain.SPIp.SS.port = &LATB;
   adcgain.SPIp.SS.tris = &TRISB;
   adcgain.SPIp.SS.npin = 1;
   adcgain.SPIp.tx_bitsize = 8;
   adcgain.SPIp.delay_us = 5;

   SPI_init(&(adcgain.SPIp));
}

void adcgain_write(UINT8 data) {

   SPI_tx(&(adcgain.SPIp), data);
}

void fpga_init(void) {

   // FPGA init
   fpga.SPIp.SDO.port = &PORTB;
   fpga.SPIp.SDO.tris = &TRISB;
   fpga.SPIp.SDO.npin = 3;
   fpga.SPIp.SDI.port = &PORTB;
   fpga.SPIp.SDI.tris = &TRISB;
   fpga.SPIp.SDI.npin = 2;
   fpga.SPIp.SCK.port = &LATB;
   fpga.SPIp.SCK.tris = &TRISB;
   fpga.SPIp.SCK.npin = 4;
   fpga.SPIp.SS.port = &LATA;
   fpga.SPIp.SS.tris = &TRISA;
   fpga.SPIp.SS.npin = 7;
   fpga.SPIp.tx_bitsize = 14;
   fpga.SPIp.rx_bitsize = 8;
   fpga.SPIp.delay_us = 1;

   SPI_init(&(fpga.SPIp));
}

void sfp_init(void) {

   // SFP init
   sfp.SPIp.SDO.port = &PORTB;
   sfp.SPIp.SDO.tris = &TRISB;
   sfp.SPIp.SDO.npin = 3;
   sfp.SPIp.SDI.port = &PORTB;
   sfp.SPIp.SDI.tris = &TRISB;
   sfp.SPIp.SDI.npin = 2;
   sfp.SPIp.SCK.port = &LATB;
   sfp.SPIp.SCK.tris = &TRISB;
   sfp.SPIp.SCK.npin = 4;
   sfp.SPIp.SS.port = &LATA;
   sfp.SPIp.SS.tris = &TRISA;
   sfp.SPIp.SS.npin = 7;
   sfp.SPIp.tx_bitsize = 14;
   sfp.SPIp.rx_bitsize = 8;
   sfp.SPIp.delay_us = 5;

   //SPI_init(&(sfp.SPIp));
}


UINT32 fpga_read(UINT16 addr) {

   UINT32 word = 0;
   UINT16 del = fpga.SPIp.delay_us;

   addr = (0b01 << 12) | addr;
   SPI_tx(&(fpga.SPIp), addr);

   SPI_dly(del);

   SPI_bw(fpga.SPIp.SS, 0); //clear Slave Select, start SPI

   SPI_bw(fpga.SPIp.SDO,1);
   SPI_bw(fpga.SPIp.SCK, 0); //clock clear
   SPI_dly(del);
   SPI_bw(fpga.SPIp.SCK, 1); //clock set
   SPI_dly(del);
   SPI_bw(fpga.SPIp.SCK, 0); //clock clear

   SPI_bw(fpga.SPIp.SDO,0);
   SPI_bw(fpga.SPIp.SCK, 0); //clock clear
   SPI_dly(del);
   SPI_bw(fpga.SPIp.SCK, 1); //clock set
   SPI_dly(del);
   SPI_bw(fpga.SPIp.SCK, 0); //clock clear

   word = SPI_rx(&(fpga.SPIp));

   return (word);
}

void fpga_write(UINT16 data, UINT16 addr) {

   UINT16 del = fpga.SPIp.delay_us;

   addr = (0b01 << 12) | addr;
   SPI_tx(&(fpga.SPIp), addr);

   SPI_dly(del);

   SPI_bw(fpga.SPIp.SS, 0); //clear Slave Select, start SPI

   SPI_bw(fpga.SPIp.SDO,1);
   SPI_bw(fpga.SPIp.SCK, 0); //clock clear
   SPI_dly(del);
   SPI_bw(fpga.SPIp.SCK, 1); //clock set
   SPI_dly(del);
   SPI_bw(fpga.SPIp.SCK, 0); //clock clear

   SPI_bw(fpga.SPIp.SDO,1);
   SPI_bw(fpga.SPIp.SCK, 0); //clock clear
   SPI_dly(del);
   SPI_bw(fpga.SPIp.SCK, 1); //clock set
   SPI_dly(del);
   SPI_bw(fpga.SPIp.SCK, 0); //clock clear

   SPI_tx(&(fpga.SPIp), data);
}

UINT32 sfp_read(UINT16 addr) {

   UINT32 word = 0;
   UINT16 del = sfp.SPIp.delay_us;

   addr = (0b00 << 12) | addr;
   SPI_tx(&(sfp.SPIp), addr);

   SPI_dly(del);

   SPI_bw(sfp.SPIp.SS, 0); //clear Slave Select, start SPI

   SPI_bw(sfp.SPIp.SDO,1);
   SPI_bw(sfp.SPIp.SCK, 0); //clock clear
   SPI_dly(del);
   SPI_bw(sfp.SPIp.SCK, 1); //clock set
   SPI_dly(del);
   SPI_bw(sfp.SPIp.SCK, 0); //clock clear

   SPI_bw(sfp.SPIp.SDO,0);
   SPI_bw(sfp.SPIp.SCK, 0); //clock clear
   SPI_dly(del);
   SPI_bw(sfp.SPIp.SCK, 1); //clock set
   SPI_dly(del);
   SPI_bw(sfp.SPIp.SCK, 0); //clock clear

   word = SPI_rx(&(sfp.SPIp));

   return (word);
}

// EOF

