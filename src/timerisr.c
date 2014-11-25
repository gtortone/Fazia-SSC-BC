#include "timerisr.h"

#include "p33Fxxxx.h"
#include "board.h"
#include "setup.h"
#include "uartbuf.h"
#include "frame.h"
#include "functions.h"
#include "diskio.h"
#include "ff.h"
#include "fpga.h"
#include "jt-ports.h"
#include "jt-micro.h"

#define UART1   uart_master_rawputch
#define UART2   uart_slave_rawputch

//extern CBuffer *Uart[6];

// TIMER1 ISR vars
//static BYTE retval = 0;
//static unsigned char framehpin[32], framehpout[32];
//static char kw;
//static UINT idb;
//static enum slaveid ids;
//static unsigned char cmd;
//static unsigned char seq;
//static char data[32], result[32];
//static UINT crc;
//static UINT flen, foffset;
//static UINT ferr;

void __attribute__((__interrupt__, no_auto_psv)) _T1Interrupt(void) {

   //
   //   ferr = cbuffer_getframe_length(Uart[MASTER_HPRX], &flen, &foffset);
   //
   //   if (ferr == ERR_FRAME_NONE) {
   //
   //      uartbuf_getframe(MASTER_HPRX, framehpin, flen, foffset);
   //
   //      kw = frame_getkw(framehpin);
   //      idb = frame_getidb(framehpin);
   //      ids = frame_getids(framehpin);
   //      cmd = frame_getcmd(framehpin);
   //      seq = frame_getseq(framehpin);
   //      frame_getdata(framehpin, data);
   //      crc = frame_getcrc(framehpin);
   //
   //      if (!frame_checkcrc(framehpin)) { // CRC fail
   //
   //         frame_build(KW_ERR, idb, ids, cmd, seq, data, framehpout);
   //
   //      } else { // CRC ok
   //
   //         retval = hpfunc_invoke(cmd, data, result);
   //
   //         if (retval == FUNC_CMD_OK) {
   //
   //            frame_build(KW_ACK, idb, ids, cmd, seq, result, framehpout); // send ACK
   //
   //         } else {
   //
   //            frame_build(KW_ERR, idb, ids, cmd, seq, data, framehpout); // send ERR
   //         }
   //
   //         uartbuf_putframe(MASTER_HPTX, framehpout); // send response on Master.TX buffer
   //      }
   //   }

   IFS0bits.T1IF = 0; // clear interrupt flag
}

void __attribute__((__interrupt__, no_auto_psv)) _T2Interrupt(void) {

   static char *fwname[] = {FPGA_STARTUP_FW, FPGA_BACKUP_FW, FPGA_RESCUE_FW};
   BYTE retval = 0;
   BYTE i = 0;
   FRESULT fres;

   extern BOOL extprog;
   extern FIL File;

   // TASK 1
   disk_timerproc(); // Drive timer procedure of low level disk I/O module

   // TASK 2
   if (fpgafw_isvalid() && (get_fpgasw() == FPGA_NOFW_VAL)) { // make FPGA status consistent...

      set_fpgasw(FPGA_DEFAULT_VAL); // a valid (default) firmware is already present on FPGA

   } else {

      if (!fpgafw_isvalid() && (!extprog)) { // check if JTAG program function is running...

         set_fpgasw(FPGA_NOFW_VAL); // FPGA not programmed

         fres = f_open(&File, fwname[i], FA_OPEN_EXISTING | FA_READ);

         if (fres == FR_OK) {

            jtagReset();
            setPort(TDI, 0);
            setPort(TCK, 0);
            setPort(TMS, 0);

            xsvf_setup();
            setPort(TMS, 1);
            retval = xsvfExecute();

            if ((retval == 0) && fpgafw_isvalid())
               set_fpgasw(2 << i); // FPGA programmed

            f_close(&File);
         }
      } // end if(!extprog)

      (i == (FPGA_FW_NUM - 1)) ? (i = 0) : i++;

   } // end if

   IFS0bits.T2IF = 0; // clear interrupt flag
}

// EOF
