#include "fpga.h"
#include "ff.h"
#include "spi-dev.h"

#include <p33Fxxxx.h>
#include <Generic.h>
#include <stdio.h>
#include <string.h>

// FPGA firmware type status register
// 0: none      (firmware not present)
// 1: default   (firmware already present on FPGA)
// 2: startup   (startup firmware loaded from microSD)
// 4: backup    (startup firmware loaded from microSD)
// 8: rescue    (startup firmware loaded from microSD)
//16: command   (firmware loaded from SSC command)
static union {

    BYTE rel;

    struct {
        BOOL def : 1;
        BOOL startup : 1;
        BOOL backup : 1;
        BOOL rescue : 1;
        BOOL command : 1;
        BOOL: 3;
    };
} fpgasw;

BOOL extprog = FALSE;

fpgareg_t fpgareg[FPGA_REG_NUM] = {
   { 0x00, "; SFP          - (8 bit) SFP control", TRUE },
   { 0x01, "; PLL          - (8 bit) PLL and power supplies", TRUE },
   { 0x10, "; BlockIDL     - (8 bit) Block ID (low part)", FALSE },
   { 0x11, "; BlockIDH     - (4 bit) Block ID (high part)", FALSE },
   { 0x12, "; EN_ISER      - (8 bit) enable ISERDES", TRUE },
   { 0x13, "; ERR_ISERL    - (8 bit) ISERDES 7..0 alignement error", FALSE },
   { 0x14, "; ERR_ISERH    - (8 bit) ISERDES 15..8 alignement error", FALSE },
   { 0x15, "; ALL_ISER     - (8 bit) ISERDES control", TRUE },
   { 0x16, "; Dat_MoniL    - (8 bit) FIFO Monitor 7..0 data", FALSE },
   { 0x17, "; Dat_MoniH    - (8 bit) FIFO Monitor 15..8 data", FALSE },
   { 0x18, "; LocFifHF     - (8 bit) FIFO FEE half full flag set", FALSE },
   { 0x19, "; LocFifEmp    - (8 bit) FIFO FEE empty flag set", FALSE },
   { 0x1A, "; SEL_MUX      - (4 bit) MUX sel value" , FALSE },
   { 0x1B, "; VARIEFIFO    - (5 bit) FIFO ADC and global flag set", FALSE },
   { 0x20, "; TRGPatternL  - (8 bit) FEE trigger pattern (low part)", TRUE },
   { 0x21, "; TRGPatternH  - (8 bit) FEE trigger pattern (high part)", TRUE },
   { 0x22, "; Busy_Mux     - (5 bit) frequency meter control", TRUE },
   { 0x23, "; FreqLOW      - (8 bit) frequency value (low part)", FALSE },
   { 0x24, "; FreqHIGH     - (8 bit) frequency value (high part)", FALSE },
   { 0x25, "; START        - (2 bit) start sampling", TRUE },
   { 0x30, "; StatoGTX     - (6 bit) GTX status", TRUE },
   { 0x40, "; ADC_L        - (8 bit) fake ADC value (low part)", TRUE },
   { 0x41, "; ADC_H        - (8 bit) fake ADC value (high part)", TRUE },
   { 0x50, "; RRESET       - (3 bit) reset control", TRUE },
   { 0x51, "; VERSIONE     - (8 bit) firmware version number", FALSE }
};

extern FIL File;

BOOL fpga_isrunning(void) {
   return (!FPGA_RUNNING);
}

BOOL fpgafw_isvalid(void) {

   UINT32 fwver = 0;
   fwver = fpga_read(FPGA_FW_VERSION);
   return( (fwver > 0x00) && (fwver < 0xFF) );
}

BYTE get_fpgasw(void) {
   return(fpgasw.rel);
}

void set_fpgasw(BYTE type) {
   fpgasw.rel = type;
}

FRESULT fpga_loadconf(char *filename) {

   FRESULT fres;
   char buf[128];
   UINT16 addr, value;
   char pre[32];
   BYTE nconv;
   BYTE i;

   fres = f_open(&File, filename, FA_OPEN_EXISTING | FA_READ);
   if (fres == 0) {

      while (!f_eof(&File)) {

         f_gets(buf, sizeof (buf), &File);
         nconv = sscanf(buf, "%s0x%X%*s=%*s0x%X", pre, &addr, &value);

         if (strchr(pre, ';'))
            continue;
         else {
            if (nconv == 3) {

               for(i=0;i<FPGA_REG_NUM;i++) {
                  if( (fpgareg[i].addr == addr) && (fpgareg[i].persistent) )
                     fpga_write(value, addr);
               }
            }
         }
      }
   }

   f_close(&File);

   return(fres);
}

// EOF
