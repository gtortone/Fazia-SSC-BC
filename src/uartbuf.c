#include "cbuffer.h"
#include "uartbuf.h"
#include "frame.h"

#include <string.h>     // for strlen
#include <stdlib.h>     // for malloc
#include <uart.h>

#ifdef DEBUG
#include "xprintf.h"
#include <string.h>

#define UART1   uart_master_rawputch
#define UART2   uart_slave_rawputch

#endif

CBuffer CB_MASTER_RX, CB_MASTER_TX;
CBuffer CB_SLAVE_RX, CB_SLAVE_TX;

void uart_rawputch(UINT channel, unsigned char d) {

   if (channel == MASTER_TX) { // Master UART

      while (BusyUART1());
      putcUART1(d);

   } else if (channel == SLAVE_TX) { // Slave UART

      while (BusyUART2());
      putcUART2(d);
   }
}

void uart_master_rawputch(unsigned char d) { // for xprintf.c functions
   while (BusyUART1());
   putcUART1(d);
}

void uart_slave_rawputch(unsigned char d) { // for xprintf.c functions
   while (BusyUART2());
   putcUART2(d);
}

void uartbuf_alloc(void) {

   cbuffer_alloc(&CB_MASTER_RX, 300);
   cbuffer_alloc(&CB_MASTER_TX, 300);
//   cbuffer_alloc(Uart[MASTER_HPRX], 100);
//   cbuffer_alloc(Uart[MASTER_HPTX], 100);
   cbuffer_alloc(&CB_SLAVE_RX, 300);
   cbuffer_alloc(&CB_SLAVE_TX, 300);
}

void uartbuf_init(void) {

   cbuffer_init(&CB_MASTER_RX);
   cbuffer_init(&CB_MASTER_TX);
//   cbuffer_init(Uart[MASTER_HPRX]);
//   cbuffer_init(Uart[MASTER_HPTX]);
   cbuffer_init(&CB_SLAVE_RX);
   cbuffer_init(&CB_SLAVE_TX);
}

void uartbuf_reset(UINT channel) {
   if(channel == MASTER_TX)
      cbuffer_init(&CB_MASTER_TX);
   else if(channel == MASTER_RX)
      cbuffer_init(&CB_MASTER_RX);
   else if(channel == SLAVE_TX)
      cbuffer_init(&CB_SLAVE_TX);
   else if(channel == SLAVE_RX)
      cbuffer_init(&CB_SLAVE_RX);
}

void uartbuf_flush(UINT channel) {

   unsigned char ch;

   //if ((channel == MASTER_TX) || (channel == MASTER_HPTX)) {
   if (channel == MASTER_TX) {

      while (!cbuffer_isempty(&CB_MASTER_TX)) {
         cbuffer_read(&CB_MASTER_TX, &ch);
         uart_rawputch(MASTER_TX, ch);
      }

   } else if (channel == SLAVE_TX) {

      while (!cbuffer_isempty(&CB_SLAVE_TX)) {
         cbuffer_read(&CB_SLAVE_TX, &ch);
         uart_rawputch(SLAVE_TX, ch);
      }
   }
}

UINT16 uartbuf_frameflush(UINT channel) {

   UINT i;
   UINT flen, foffset;
   UINT ferr;
   unsigned char ch;
   CBuffer *cb;

   if(channel == MASTER_TX)
      cb = &CB_MASTER_TX;
   else if(channel == MASTER_RX)
      cb = &CB_MASTER_RX;
   else if(channel == SLAVE_TX)
      cb = &CB_SLAVE_TX;
   else if(channel == SLAVE_RX)
      cb = &CB_SLAVE_RX;

   ferr = cbuffer_getframe_length(cb, &flen, &foffset);

   if (ferr == ERR_FRAME_NONE) {    // there is a frame to send to slave...

      for(i=0;i<(foffset-1);i++)
         cbuffer_read(cb, &ch);

      for (i=0;i<flen;i++) {
         cbuffer_read(cb, &ch);
         uart_rawputch(channel, ch);
      }
   }

   return (ferr);
}

void uartbuf_getframe(UINT channel, unsigned char *f, UINT flen, UINT foffset) {

   UINT i;
   unsigned char ch;
   CBuffer *cb;

   if(channel == MASTER_TX)
      cb = &CB_MASTER_TX;
   else if(channel == MASTER_RX)
      cb = &CB_MASTER_RX;
   else if(channel == SLAVE_TX)
      cb = &CB_SLAVE_TX;
   else if(channel == SLAVE_RX)
      cb = &CB_SLAVE_RX;

   i = 0;
   while(i < (foffset - 1)) {
      cbuffer_read(cb, &ch);
      i++;
   }

   i = 0;
   while(i < flen) {
      cbuffer_read(cb, &ch);
      f[i++] = ch;
   }

   f[i] = '\0';
}

void uartbuf_putframe(UINT channel, unsigned char *f) {

   UINT i;
   UINT fsize = strlen((char *)f);
   CBuffer *cb;

   if(channel == MASTER_TX)
      cb = &CB_MASTER_TX;
   else if(channel == MASTER_RX)
      cb = &CB_MASTER_RX;
   else if(channel == SLAVE_TX)
      cb = &CB_SLAVE_TX;
   else if(channel == SLAVE_RX)
      cb = &CB_SLAVE_RX;

   for (i = 0;i < fsize;i++) {
      cbuffer_write(cb, f[i]);
   }

   cbuffer_write(cb, '\n');
}

void uartbuf_routeframe(UINT chsrc, UINT chdst, UINT flen, UINT foffset) {

   UINT i;
   unsigned char ch;
   CBuffer *cbsrc, *cbdst;

   if(chsrc == MASTER_TX)
      cbsrc = &CB_MASTER_TX;
   else if(chsrc == MASTER_RX)
      cbsrc = &CB_MASTER_RX;
   else if(chsrc == SLAVE_TX)
      cbsrc = &CB_SLAVE_TX;
   else if(chsrc == SLAVE_RX)
      cbsrc = &CB_SLAVE_RX;

   if(chdst == MASTER_TX)
      cbdst = &CB_MASTER_TX;
   else if(chdst == MASTER_RX)
      cbdst = &CB_MASTER_RX;
   else if(chdst == SLAVE_TX)
      cbdst = &CB_SLAVE_TX;
   else if(chdst == SLAVE_RX)
      cbdst = &CB_SLAVE_RX;

   for(i=0;i<(foffset-1);i++)
      cbuffer_read(cbsrc, &ch);

   for(i=0; i<flen; i++) {

      cbuffer_read(cbsrc, &ch);
      cbuffer_write(cbdst, ch);
   }

   cbuffer_write(cbdst, '\n');
}

// EOF
