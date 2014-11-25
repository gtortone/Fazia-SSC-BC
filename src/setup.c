#include <p33Fxxxx.h>
#include "setup.h"
#include "board.h"
#include "spi-dev.h"
#include "i2c-dev.h"
#include "diskio.h"
#include "ff.h"
#include "functions.h"
#include "fpga.h"
#include "jt-ports.h"
#include "uarterr.h"

#include <stdio.h>      // for sscanf
#include <string.h>     // for memset
#include <uart.h>
#include <pps.h>

#include "fpga.h"

#define BAUDRATE     115200
#define BRGVAL       ((FCY/BAUDRATE)/16)-1

static UINT MY_IDB = 0;

static union { // multicast groups [ F00 ... FFD ]
    BOOL bits[0xFF];
    BYTE octets[32]; // 32 octets of 8 bits = 256 bits
} MY_GRP;

FATFS Fatfs; // file system data structure for each logical drive
DIR dir; // directory data structure
FILINFO Finfo;
FIL File;

extern UartErrLog uerrlog;

void set_bcid(UINT id) {

   if (id <= UNICAST_MAX_IDB) {
      MY_IDB = id;
      // write BCID to FPGA registers
      fpga_write((id & 0x00FF), 0x10);
      fpga_write(((id & 0x0F00)>>8), 0x11);
   }
}

void refresh_bcid(void) {
   // write BCID to FPGA registers
   set_bcid(MY_IDB);
}

UINT get_bcid(void) {
   return MY_IDB;
}

void init_bcgrp(void) {
   memset(MY_GRP.bits, 0, (MULTICAST_MAX_IDB - MULTICAST_BASE_IDB));
}

void add_bcgrp(UINT grp) {
   if (grp >= MULTICAST_BASE_IDB)
      MY_GRP.bits[grp - MULTICAST_BASE_IDB] = TRUE;
}

void del_bcgrp(UINT grp) {
   if (grp >= MULTICAST_BASE_IDB)
      MY_GRP.bits[grp - MULTICAST_BASE_IDB] = FALSE;
}

BOOL in_bcgrp(UINT grp) {
   if (grp >= MULTICAST_BASE_IDB)
      return (MY_GRP.bits[grp - MULTICAST_BASE_IDB]);
   else return (FALSE);
}

void ucsetup(void) {

   // Configure Oscillator to operate the device at 40Mhz
   // Fosc= Fin*M/(N1*N2), Fcy=Fosc/2
   // Fosc= 7.37*43/(2*2)=79.23MHz
   PLLFBD = 41; // M=43
   CLKDIVbits.PLLPOST = 0; // N1=2
   CLKDIVbits.PLLPRE = 0; // N2=2

   // Disable Watch Dog Timer
   RCONbits.SWDTEN = 0;

   // SETUP PIN DIRECTION

   // global SPI clock
   _TRISB4 = 0;

   // global SCL clock
   _TRISC4 = 0;

   // ADC
   _TRISA0 = 1; // VREF+
   _TRISA1 = 1; // AN1

   // MUX (SPI)
   _TRISB4 = 0; // SCK
   _TRISA4 = 0; // SS
   _TRISB3 = 0; // device SDI

   // FPGA (SPI)
   _TRISA7 = 0; // SS
   _TRISB2 = 1; // device SDO

   // VCXO 50 MHz (I2C)
   _TRISC0 = 1; // SDA

   // VCXO 150 MHz (I2C)
   _TRISC1 = 1; // SDA

   // VCXO 25 MHz (I2C)
   _TRISC2 = 1; // SDA

   // VCXO 125 MHz (I2C)           [ not used]
   _TRISC3 = 1; // SDA
   _TRISC5 = 0; // SCL

   // PLL 25 MHz (SPI)
   _TRISA8 = 0; // SS

   // PLL 50 MHz (SPI)
   _TRISA9 = 0; // SS

   // PLL 150 MHz (SPI)
   _TRISA10 = 0; // SS

   // ADC gain (SPI)
   _TRISB1 = 0; // SS

   // PICkit
   _TRISB0 = 1; // EMUD

   // JTAG
   _TRISB5 = 0; // device TDI
   _TRISB6 = 1; // device TDO
   _TRISB7 = 0; // TMS
   _TRISB8 = 0; // TCK
   _TRISB9 = 0; // REPROGRAM
   _TRISB10 = 1; // C_DONE

   // microSD (SPI)
   _TRISB11 = 1; // presence switch
   _TRISB12 = 0; // SS
   _TRISB13 = 0; // SCK
   _TRISB14 = 1; // device SDO
   _TRISB15 = 0; // device SDI

   // FPGA serial link
   _TRISC6 = 1; // device TX
   _TRISC7 = 0; // device RX

   // FEE serial link
   _TRISC8 = 0; // device RX
   _TRISC9 = 1; // device TX

   // Wait for PLL to lock
   while (OSCCONbits.LOCK != 1) {
   };

   AD1PCFGL = 0x1FFC; // Make analoug pins digital - AN0 and AN1 are analog

   AD1CON1bits.AD12B = 1; // 12 bit resolution
   AD1CON2bits.VCFG = 1; // select vref+
   AD1CHS0bits.CH0SA = 1; // select AN1
   AD1CON1bits.ADON = 1; // power on ADC

   PPSUnLock; // Unlock Registers

   PPSOutput(PPS_U1TX, PPS_RP23); // UART1 MASTER (from FPGA)
   PPSInput(PPS_U1RX, PPS_RP22);
   PPSOutput(PPS_U2TX, PPS_RP24); // UART2 SLAVE (to Front End Card)
   PPSInput(PPS_U2RX, PPS_RP25);

   PPSInput(PPS_SDI1, PPS_RP14); // SPI1 setup for uSD
   PPSOutput(PPS_SCK1, PPS_RP13);
   PPSOutput(PPS_SDO1, PPS_RP15);

   PPSLock; // Lock Registers

   // INTCON1bits.NSTDIS = 1; // nested interrupts disabled

   ConfigIntUART1(
           UART_RX_INT_EN & //attivazione interrupt RX1
           UART_RX_INT_PR6 & //con priorità 6 (7=max)
           UART_TX_INT_DIS); //int TX disabilitato

//   ConfigIntUART2(
//           UART_RX_INT_EN & //attivazione interrupt RX2
//           UART_RX_INT_PR5 & //con priorità 5 (7=max)
//           UART_TX_INT_DIS); //int TX disabilitato

   U1BRG = BRGVAL;
   U1MODE = 0x8000; // Reset UART to 8-n-1, alt pins, and enable
   U1STA = 0x0440; // Reset status register and enable TX & RX

//   U2BRG = BRGVAL;
//   U2MODE = 0x8000; // Reset UART to 8-n-1, alt pins, and enable
//   U2STA = 0x0440; // Reset status register and enable TX & RX

   TMR1 = 0; // clear timer 1
   PR1 = 0xFFFF; // interrupt every 400ms
   IFS0bits.T1IF = 0; // clr interrupt flag
   IEC0bits.T1IE = 1; // set interrupt enable bit
   T1CON = 0x8030; // 1:256 prescale, start TMR1

   TMR2 = 0; // clear timer 2
   PR2 = 0xFFFF; // interrupt every 400ms
   IFS0bits.T2IF = 0; // clr interrupt flag
   IEC0bits.T2IE = 1; // set interrupt enable bit
   T2CON = 0x8030; // 1:256 prescale, start TMR2
}

void memsetup(void) {

   vcxodev_t VCXO25M;
   vcxodev_t VCXO50M;
   vcxodev_t VCXO150M;

   plldev_t PLL25M;
   plldev_t PLL50M;
   plldev_t PLL150M;

   FRESULT fres;
   BYTE buff[32];
   UINT br;

   UINT id;
   int nconv;

   //VCXO init
   VCXO25M.I2Cp.SDA.port = &PORTC;
   VCXO25M.I2Cp.SDA.tris = &TRISC;
   VCXO25M.I2Cp.SDA.npin = 2;
   VCXO25M.I2Cp.SCL.port = &PORTC;
   VCXO25M.I2Cp.SCL.tris = &TRISC;
   VCXO25M.I2Cp.SCL.npin = 4;
   VCXO25M.dcodiv = 28; // 25 MHz
   VCXO25M.clkdiv = HS_7;
   VCXO25M.freq = 11511583772LL;

   VCXO50M.I2Cp.SDA.port = &PORTC;
   VCXO50M.I2Cp.SDA.tris = &TRISC;
   VCXO50M.I2Cp.SDA.npin = 0;
   VCXO50M.I2Cp.SCL.port = &PORTC;
   VCXO50M.I2Cp.SCL.tris = &TRISC;
   VCXO50M.I2Cp.SCL.npin = 4;
   VCXO50M.dcodiv = 14; // 50 MHz
   VCXO50M.clkdiv = HS_7;
   VCXO50M.freq = 11515648220LL;

   VCXO150M.I2Cp.SDA.port = &PORTC;
   VCXO150M.I2Cp.SDA.tris = &TRISC;
   VCXO150M.I2Cp.SDA.npin = 1;
   VCXO150M.I2Cp.SCL.port = &PORTC;
   VCXO150M.I2Cp.SCL.tris = &TRISC;
   VCXO150M.I2Cp.SCL.npin = 4;
   VCXO150M.dcodiv = 4; // 150 MHz
   VCXO150M.clkdiv = HS_9;
   VCXO150M.freq = 12683788729LL;

   //PLL init
   PLL25M.SPIp.SDO.port = &PORTB; // 25 MHz
   PLL25M.SPIp.SDO.tris = &TRISB;
   PLL25M.SPIp.SDO.npin = 3;
   PLL25M.SPIp.SDI.port = &LATB;
   PLL25M.SPIp.SDI.tris = &TRISB;
   PLL25M.SPIp.SDI.npin = 2;
   PLL25M.SPIp.SCK.port = &LATB;
   PLL25M.SPIp.SCK.tris = &TRISB;
   PLL25M.SPIp.SCK.npin = 4;
   PLL25M.SPIp.SS.port = &LATA;
   PLL25M.SPIp.SS.tris = &TRISA;
   PLL25M.SPIp.SS.npin = 8;
   PLL25M.SPIp.tx_bitsize = 32;
   PLL25M.SPIp.delay_us = 5;
   PLL25M.ncmd = 12;
   PLL25M.cmds[0] = 0x80000000; // RESET
   PLL25M.cmds[1] = 0x00010100; // R0
   PLL25M.cmds[2] = 0x00010101; // R1
   PLL25M.cmds[3] = 0x00010102; // R2
   PLL25M.cmds[4] = 0x00010103; // R3
   PLL25M.cmds[5] = 0x00000104; // R4
   PLL25M.cmds[6] = 0x00000105; // R5
   PLL25M.cmds[7] = 0x00000106; // R6
   PLL25M.cmds[8] = 0x00000107; // R7
   PLL25M.cmds[9] = 0x0082000B; // R11
   PLL25M.cmds[10] = 0x2930010E; // R14
   PLL25M.cmds[11] = 0x4000010F; // R15

   PLL50M.SPIp.SDO.port = &PORTB; // 50 MHz
   PLL50M.SPIp.SDO.tris = &TRISB;
   PLL50M.SPIp.SDO.npin = 3;
   PLL50M.SPIp.SDI.port = &LATB;
   PLL50M.SPIp.SDI.tris = &TRISB;
   PLL50M.SPIp.SDI.npin = 2;
   PLL50M.SPIp.SCK.port = &LATB;
   PLL50M.SPIp.SCK.tris = &TRISB;
   PLL50M.SPIp.SCK.npin = 4;
   PLL50M.SPIp.SS.port = &LATA;
   PLL50M.SPIp.SS.tris = &TRISA;
   PLL50M.SPIp.SS.npin = 10;
   PLL50M.SPIp.tx_bitsize = 32;
   PLL50M.SPIp.delay_us = 5;
   PLL50M.ncmd = 12;
   PLL50M.cmds[0] = 0x80000000; // RESET
   PLL50M.cmds[1] = 0x00010100; // R0
   PLL50M.cmds[2] = 0x00010101; // R1
   PLL50M.cmds[3] = 0x00000102; // R2
   PLL50M.cmds[4] = 0x00000103; // R3
   PLL50M.cmds[5] = 0x00010104; // R4
   PLL50M.cmds[6] = 0x00000105; // R5
   PLL50M.cmds[7] = 0x00000106; // R6
   PLL50M.cmds[8] = 0x00000107; // R7
   PLL50M.cmds[9] = 0x0082800B; // R11
   PLL50M.cmds[10] = 0x2930010E; // R14
   PLL50M.cmds[11] = 0x2000020F; // R15

   PLL150M.SPIp.SDO.port = &PORTB; // 150 MHz
   PLL150M.SPIp.SDO.tris = &TRISB;
   PLL150M.SPIp.SDO.npin = 3;
   PLL150M.SPIp.SDI.port = &LATB;
   PLL150M.SPIp.SDI.tris = &TRISB;
   PLL150M.SPIp.SDI.npin = 2;
   PLL150M.SPIp.SCK.port = &LATB;
   PLL150M.SPIp.SCK.tris = &TRISB;
   PLL150M.SPIp.SCK.npin = 4;
   PLL150M.SPIp.SS.port = &LATA;
   PLL150M.SPIp.SS.tris = &TRISA;
   PLL150M.SPIp.SS.npin = 9;
   PLL150M.SPIp.tx_bitsize = 32;
   PLL150M.SPIp.delay_us = 5;
   PLL150M.ncmd = 12;
   PLL150M.cmds[0] = 0x80000000; // RESET
   PLL150M.cmds[1] = 0x00010100; // R0
   PLL150M.cmds[2] = 0x00010101; // R1
   PLL150M.cmds[3] = 0x00010102; // R2
   PLL150M.cmds[4] = 0x00010103; // R3
   PLL150M.cmds[5] = 0x00000104; // R4
   PLL150M.cmds[6] = 0x00000105; // R5
   PLL150M.cmds[7] = 0x00000106; // R6
   PLL150M.cmds[8] = 0x00000107; // R7
   PLL150M.cmds[9] = 0x0082800B; // R11
   PLL150M.cmds[10] = 0x2930010E; // R14
   PLL150M.cmds[11] = 0x2000060F; // R15

   mux_init();
   mux_select(1); // useful to avoid glitches on first mux switch

   adcgain_init();

   fpga_init();
   sfp_init();

   vcxo_enable(&VCXO25M);
   vcxo_enable(&VCXO50M);
   vcxo_enable(&VCXO150M);

   pll_enable(&PLL25M);
   pll_enable(&PLL50M);
   pll_enable(&PLL150M);

   disk_initialize(0);
   f_mount(0, &Fatfs);

   // setup Block Card ID
   fres = f_open(&File, ID_USD_FILENAME, FA_READ);
   if (fres != 0)
      set_bcid(DEFAULT_IDB);
   else {
      fres = f_read(&File, buff, sizeof (buff), &br);
      if ((fres != 0) || (br == 0))
         set_bcid(DEFAULT_IDB);
      else {
         nconv = sscanf((const char *) buff, "%X", &id);
         if (nconv == 0)
            set_bcid(DEFAULT_IDB);
         else
            set_bcid(id);
      }
   }
   f_close(&File);

   // init Block Card GROUPs
   init_bcgrp();

   ConfigIntUART2(
           UART_RX_INT_EN & //attivazione interrupt RX2
           UART_RX_INT_PR5 & //con priorità 5 (7=max)
           UART_TX_INT_DIS); //int TX disabilitato

   U2BRG = BRGVAL;
   U2MODE = 0x8000; // Reset UART to 8-n-1, alt pins, and enable
   U2STA = 0x0440; // Reset status register and enable TX & RX

   // reset UART error log
   uerrlog.uart1_ferr = 0;
   uerrlog.uart1_oerr = 0;
   uerrlog.uart2_ferr = 0;
   uerrlog.uart2_oerr = 0;
}

// EOF
