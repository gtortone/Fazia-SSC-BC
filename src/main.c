#include <p33Fxxxx.h>
#include <stdio.h>
#include <Generic.h>
#include <reset.h>

#include "board.h"
#include "setup.h"
#include "uartisr.h"
#include "cbuffer.h"
#include "uartbuf.h"
#include "xprintf.h"
#include "frame.h"
#include "functions.h"
#include "fpga.h"

_FOSCSEL(FNOSC_PRIPLL & // Select Primary OSC = XT + PLL
        IESO_OFF) // Startup With User Select OSC

_FOSC(FCKSM_CSDCMD & // Clock Switch Disabled
        OSCIOFNC_OFF & // OSC2 Pin = Clock O/P
        POSCMD_XT) // Primary OSC = XT

_FWDT(FWDTEN_OFF & // Disable Watchdog Timer
        WINDIS_OFF & // Disabled Windowed WDT
        WDTPRE_PR128 &
        WDTPOST_PS32768)

_FICD(ICS_PGD1 & // Comm Channel Select (Communicate on PGC1/EMUC1 and PGD1/EMUD1)
        JTAGEN_OFF) // JTAG Port Enable (JTAG is disabled)

_FPOR(FPWRT_PWR128) // Power-on Reset Value = 128ms

#define UART1           uart_master_rawputch
#define UART2           uart_slave_rawputch
//#define MAX_TRY_RECV    65000    // for high latency commands
#define MAX_TRY_RECV    130000    // for high latency commands

//#define DEBUG

extern CBuffer CB_MASTER_RX;
extern CBuffer CB_MASTER_TX;
extern CBuffer CB_SLAVE_RX;
extern CBuffer CB_SLAVE_TX;

int main(void) {

   BOOL swreset = FALSE;
   BOOL hwreset = FALSE;

   char kw;
   UINT idb;
   enum slaveid ids;
   unsigned char cmd;
   unsigned char seq;
   char data[MAX_DATA_SIZE], result[MAX_DATA_SIZE];
   UINT i, crc, docrc;
   UINT flen, foffset;
   UINT ferr;
   char fpre[10];
   BOOL frame_toslave = FALSE;

   unsigned char fMasterIn[MAX_FRAME_SIZE], frameout[MAX_FRAME_SIZE];;
   BYTE retval, cmdres, funcres;
   UINT32 try_recv = 0;
   char filename[64];

   ucsetup();
   memsetup();

   swreset = isSWR();
   hwreset = isPOR();

   uartbuf_alloc();
   uartbuf_init();

   // loop until FPGA is programmed with default, startup, backup or rescue firmware
   set_fpgasw(FPGA_NOFW_VAL);
   while (get_fpgasw() == FPGA_NOFW_VAL);

   // now it is time to set BC id in FPGA...
   refresh_bcid();

   // initial setup for FPGA registers from "/conf/fpga.ini"
   sprintf(filename, "/conf/%s", FPGA_INI_FILE);
   fpga_loadconf(filename);

   //memsetup();    // to avoid FPGA post-programming without modules setup (PLL, VCXO, etc.)

#ifdef DEBUG

   if (hwreset) {
      xfprintf(UART1, "\n# # # # # # # # # # # #");
      //xfprintf(UART2, "\n # # # # # # # # # # # #");
   }

   xfprintf(UART1, "\n\nProgram started - BC id = %d (0x%03X) - UART Master\n", get_bcid(), get_bcid());
   xfprintf(UART1, "\tSWR = %d - HWR = %d\n", swreset, hwreset);
   xfprintf(UART1, "\tFPGA firmware release: %d\n", get_fpgasw());
   xfprintf(UART1, "\tFPGA firmware version: 0x%03X\n", fpga_read(FPGA_FW_VERSION));
   //xfprintf(UART2, "\n\nProgram started - BC id = %d (0x%03X) - UART Slave\n", get_bcid(), get_bcid());
   //xfprintf(UART2, "\tSWR = %d - HWR = %d\n", swreset, hwreset);

#endif

   frame_init(fMasterIn);
   frame_init(frameout);

   func_init();

   while (1) {

#ifndef BRIDGE_MODE

      ferr = cbuffer_getframe_length(&CB_MASTER_RX, &flen, &foffset);

      if (ferr == ERR_FRAME_NONE) {

         uartbuf_getframe(MASTER_RX, fMasterIn, flen, foffset);

         kw = frame_getkw(fMasterIn);
         idb = frame_getidb(fMasterIn);
         ids = frame_getids(fMasterIn);
         cmd = frame_getcmd(fMasterIn);
         seq = frame_getseq(fMasterIn);
         frame_getdata(fMasterIn, data);
         crc = frame_getcrc(fMasterIn);

         if (seq)
            sprintf(fpre, "%03X%c%c%c%c", idb, ids, cmd, seq, SEQNUM_DELIMITER);
         else
            sprintf(fpre, "%03X%c%c", idb, ids, cmd);

         if ((ids < '0') || (ids > 'F')) { // IDS not valid

            sprintf((char *) fMasterIn, "%c%s%s%c", KW_ERR, fpre, data, KW_END);
            crc = frame_docrc(fMasterIn);
            sprintf((char *) frameout, "%s%X", fMasterIn, crc);

            uartbuf_putframe(MASTER_TX, frameout);
            continue;
         }

         if (ids == BC) {

            docrc = 0;
            for (i = 0; fMasterIn[i] != KW_END; i++)
               docrc = docrc ^ fMasterIn[i];

            if ((docrc != crc) || (kw != KW_STX)) { // CRC fail

               sprintf((char *) fMasterIn, "%c%s%s%c", KW_ERR, fpre, data, KW_END);
               crc = frame_docrc(fMasterIn);
               sprintf((char *) frameout, "%s%X", fMasterIn, crc);

               uartbuf_putframe(MASTER_TX, frameout);
               continue;
            }

            cmdres = func_invoke(cmd, data, result);

            if (cmdres == FUNC_CMD_OK) { // command exists

               sscanf(result, "%d[^|]", &funcres);

               while (funcres == FUNC_EXEC_INPROGRESS) {

                  sprintf((char *) fMasterIn, "%c%s%s%c", KW_ETB, fpre, data, KW_END);
                  crc = frame_docrc(fMasterIn);
                  sprintf((char *) frameout, "%s%X", fMasterIn, crc);

                  uartbuf_putframe(MASTER_TX, frameout);
                  uartbuf_flush(MASTER_TX);

                  cmdres = func_invoke(cmd, data, result);
                  sscanf(result, "%d|", &funcres);
               }

               if (funcres == FUNC_EXEC_OK) { // function execution OK

                  sprintf((char *) fMasterIn, "%c%s%s%c", KW_ACK, fpre, result, KW_END);

               } else {

                  sprintf((char *) fMasterIn, "%c%s%s%c", KW_NAK, fpre, result, KW_END);
               }

            } else { // command does not exist

               sprintf((char *) fMasterIn, "%c%s%s%c", KW_ERR, fpre, data, KW_END);
            }

            crc = frame_docrc(fMasterIn);
            sprintf((char *) frameout, "%s%X", fMasterIn, crc);
            uartbuf_putframe(MASTER_TX, frameout);

         } else { // (ids != BC)

            uartbuf_putframe(SLAVE_TX, fMasterIn);
            frame_toslave = TRUE;

         }

      } // end if (ferr)

      if (frame_toslave) {

         frame_toslave = FALSE;

         //          ###########################
         //          ### SLAVE FRAME HANDLER ###
         //          ###########################

         // SPURIOUS frame detection
         ferr = cbuffer_getframe_length(&CB_SLAVE_RX, &flen, &foffset);

         if (ferr == ERR_FRAME_NONE) // a SPURIOUS frame is received from SLAVE_RX
            uartbuf_routeframe(SLAVE_RX, MASTER_TX, flen, foffset);

         uartbuf_reset(SLAVE_RX);
         //

         ferr = uartbuf_frameflush(SLAVE_TX);

         if (ferr == ERR_FRAME_NONE) {

            // sent succedeed now start polling on SLAVE_RX

            try_recv = 0;

            while (try_recv < MAX_TRY_RECV) {

               ferr = cbuffer_getframe_length(&CB_SLAVE_RX, &flen, &foffset);

               if (ferr == ERR_FRAME_NONE) {

                  uartbuf_routeframe(SLAVE_RX, MASTER_TX, flen, foffset);
                  break;

               } else {

                  __delay_us(2);
                  try_recv++;
               }

            } // end of while

            if (try_recv == MAX_TRY_RECV) { // timeout from slave

               idb = frame_getidb(fMasterIn);
               ids = frame_getids(fMasterIn);
               cmd = frame_getcmd(fMasterIn);
               seq = frame_getseq(fMasterIn);
               frame_getdata(fMasterIn, data);

               sprintf((char *) fMasterIn, "%c%s%s%c", KW_TOUT, fpre, data, KW_END);
               crc = frame_docrc(fMasterIn);
               sprintf((char *) frameout, "%s%X", fMasterIn, crc);

               uartbuf_putframe(MASTER_TX, frameout);
            }
         }

      } // end if(frame_toslave)

      //      uartbuf_flush(MASTER_HPTX);
      uartbuf_flush(MASTER_TX);

#endif

   } // end while

   return (0); // never reached ...
}

// EOF
