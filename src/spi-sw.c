#include "spi-sw.h"

#include "board.h"
#include <p33Fxxxx.h>
#include <libpic30.h>

inline void SPI_dly(UINT16 time_us) {
   __delay_us(time_us);
}

inline void SPI_bw(SPI_pin pin, BOOL s) {

   if (s == 1)
      (*(pin.port) |= (1 << pin.npin));
   else
      (*(pin.port) &= (~(1 << pin.npin)));
}

inline BOOL SPI_br(SPI_pin pin) {
   return(PORTBbits.RB2);
   //return (*(pin.port) >> pin.npin) & 1;
}

void SPI_init(SPI_param *p) {

   SPI_bw(p->SS, 1); //output high on each SS pin
   SPI_bw(p->SDO, 1);
   SPI_bw(p->SCK, 1);
}

void SPI_tx(SPI_param *p, UINT32 data) {

   int i;
   BOOL b;
   UINT16 del = p->delay_us;

   SPI_bw(p->SS, 0); //clear Slave Select, start SPI

   for (i = (p->tx_bitsize) - 1; i >= 0; i--) {
      b = (BOOL) (data >> i) & 1; //data bit
      SPI_bw(p->SDO, b); //data out

      SPI_bw(p->SCK, 0); //clock clear
      SPI_dly(del);
      SPI_bw(p->SCK, 1); //clock set
      SPI_dly(del);
      SPI_bw(p->SCK, 0); //clock clear
   }

   SPI_bw(p->SS, 1); //set Slave Select, end SPI
}

UINT32 SPI_rx(SPI_param *p) {

   int i;
   UINT16 del = p->delay_us;
   UINT32 tmp = 0;
   UINT32 RData = 0;

   SPI_bw(p->SS, 0); //clear Slave Select, start SPI

   for (i = (p->rx_bitsize - 1); i >= 0; i--) {
      
      tmp = SPI_br(p->SDI);
      RData |= (tmp << i); //data in

      SPI_bw(p->SCK, 0); //clock clear
      SPI_dly(del);
      SPI_bw(p->SCK, 1); //clock set
      SPI_dly(del);
      SPI_bw(p->SCK, 0); //clock clear
   }

   SPI_bw(p->SS, 1);
   return RData;
}

// EOF

