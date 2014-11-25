#include "uartisr.h"
#include "uarterr.h"
#include "cbuffer.h"
#include "uartbuf.h"
#include "setup.h"
#include "frame.h"
#include "board.h"

#include <stdio.h>      // for sscanf
#include <uart.h>
#include <libpic30.h>

//#define BRIDGE_MODE

extern CBuffer CB_MASTER_RX, CB_MASTER_TX;
extern CBuffer CB_SLAVE_RX, CB_SLAVE_TX;

UartErrLog uerrlog;

// ISR for UART Master (FPGA)

void __attribute__((__interrupt__, no_auto_psv)) _U1RXInterrupt(void) {

   static BOOL start_frame = FALSE;
   static BOOL store = FALSE;
   static unsigned char kw = 0;
   static char idb[4] = {0, 0, 0, '\0'};
   static BYTE i = 0;
   static UINT dstbuf;
   unsigned char ch;

   UINT IDB = 0;
   enum slaveid ids;

   while (DataRdyUART1()) {

      if (U1STAbits.OERR) { // reset overrun error flag
         U1STAbits.OERR = 0;
         uerrlog.uart1_oerr++;
      }

      if (U1STAbits.FERR) {
         U1RXREG = U1RXREG;
         U1RXREG = U1RXREG;
         U1RXREG = U1RXREG;
         uerrlog.uart1_ferr++;
      }

      ch = ReadUART1();

#ifndef BRIDGE_MODE

      if ((ch == KW_STX) || (ch == KW_ESC)) {

         start_frame = TRUE;
         kw = ch;
         i = 0;
         store = FALSE;
         continue;
      }

      if ((ch == KW_ACK) || (ch == KW_NAK) || (ch == KW_ERR)) {

         store = FALSE;
         continue;
      }

      if (store) {
         cbuffer_write(&CB_MASTER_RX, ch);
         continue;
      }

      if (start_frame && (ch != KW_STX) && (ch != KW_ESC)) {

         if (i < 3)
            idb[i] = ch;

         i++;

         if (i == 4) {

            sscanf(idb, "%X", &IDB);
            ids = ch;

            if ((IDB == get_bcid()) || (IDB == (UINT) BROADCAST_IDB) || in_bcgrp(IDB)) {

               store = TRUE;

                  cbuffer_write(&CB_MASTER_RX, kw);
                  cbuffer_write(&CB_MASTER_RX, idb[0]);
                  cbuffer_write(&CB_MASTER_RX, idb[1]);
                  cbuffer_write(&CB_MASTER_RX, idb[2]);
                  cbuffer_write(&CB_MASTER_RX, ids);

            }

            i = kw = 0;
            start_frame = FALSE;
         }

      } // end if(start_frame)

#else 

      uart_rawputch(SLAVE_TX, ch);

#endif

   } // end while(DataRdyUART1())

   IFS0bits.U1RXIF = 0; // interrupt reset
}

// ISR for UART Slave (FEE)

void __attribute__((__interrupt__, no_auto_psv)) _U2RXInterrupt(void) {

   unsigned char ch;

   while (DataRdyUART2()) {

      if (U2STAbits.OERR) { // ONLY reset overrun error flag
         U2STAbits.OERR = 0;
         uerrlog.uart2_oerr++;
      }

      if (U2STAbits.FERR) {
         U2RXREG = U2RXREG;
         U2RXREG = U2RXREG;
         U2RXREG = U2RXREG;
         uerrlog.uart2_ferr++;
      }

      ch = ReadUART2();

#ifndef BRIDGE_MODE

      CB_SLAVE_RX.data[CB_SLAVE_RX.wrp] = ch;
      CB_SLAVE_RX.wrp = (CB_SLAVE_RX.wrp + 1) % CB_SLAVE_RX.size;
      if (CB_SLAVE_RX.wrp == CB_SLAVE_RX.rdp) {
         CB_SLAVE_RX.rdp = (CB_SLAVE_RX.rdp + 1) % CB_SLAVE_RX.size; // full, overwrite
         (CB_SLAVE_RX.full)++;
      }

#else
      uart_rawputch(MASTER_TX, ch);
#endif
   }

   IFS1bits.U2RXIF = 0; // interrupt reset
}

// EOF
