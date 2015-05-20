#include "functions.h"
#include "frame.h"
#include "uartbuf.h"
#include "setup.h"
#include "timerisr.h"   // for extprog flag
#include "spi-dev.h"
#include "diskio.h"
#include "ff.h"
#include "base64.h"
#include "fpga.h"
#include "jt-ports.h"
#include "jt-micro.h"
#include "uarterr.h"
#include "board.h"

#include <stdio.h>
#include <string.h>
#include <p33Fxxxx.h>

typedef BYTE(*func_p)(char *, char *);

func_p hpfunc[] = {&f_reset, &f_clear, &f_echo};

func_p fplist[MAX_FUNC_NUM];

#define Reset() {__asm__ volatile ("reset");}

extern BOOL extprog;
extern FATFS Fatfs;
extern DIR dir;
extern FILINFO Finfo;
extern FIL File;
extern fpgareg_t fpgareg[FPGA_REG_NUM];
extern UartErrLog uerrlog;

const char *strres =
        "OK\0" "DISK_ERR\0" "INT_ERR\0" "NOT_READY\0" "NO_FILE\0" "NO_PATH\0"
        "INVALID_NAME\0" "DENIED\0" "EXIST\0" "INVALID_OBJECT\0" "WRITE_PROTECTED\0"
        "INVALID_DRIVE\0" "NOT_ENABLED\0" "NO_FILE_SYSTEM\0" "MKFS_ABORTED\0" "TIMEOUT\0"
        "LOCKED\0" "NOT_ENOUGH_CORE\0" "TOO_MANY_OPEN_FILES\0";

void func_init(void) {

   fplist[0] = &f_setbcid; // 0x83
   fplist[1] = &f_setbcgrp; // 0x84
   fplist[2] = &f_getvoltage; // 0x85
   fplist[3] = &f_gettemp; // 0x86
   fplist[4] = &f_usd_init; // 0x87
   fplist[5] = &f_usd_mount; // 0x88
   fplist[6] = &f_fat_ls; // 0x89
   fplist[7] = &f_fat_cd; // 0x8A
   fplist[8] = &f_fat_pwd; // 0x8B
   fplist[9] = &f_fat_mkdir; // 0x8C
   fplist[10] = &f_fat_rm; // 0x8D
   fplist[11] = &f_fat_mv; // 0x8E
   fplist[12] = &f_fat_cp; // 0x8F
   fplist[13] = &f_fat_fopen; // 0x90
   fplist[14] = &f_fat_fclose; // 0x91
   fplist[15] = &f_fat_fseek; // 0x92
   fplist[16] = &f_fat_fread; // 0x93
   fplist[17] = &f_fat_fwrite; // 0x94
   fplist[18] = &f_fpga_read; // 0x95
   fplist[19] = &f_fpga_write; //0x96
   fplist[20] = &f_jtag_prog; //0x97
   fplist[21] = &f_fpga_status; //0x98
   fplist[22] = &f_fpga_loadconf; //0x99
   fplist[23] = &f_fpga_saveconf; // 0x9A
   fplist[24] = &f_adc_write; // 0x9B
   fplist[25] = &f_sfp_read; // 0x9C
   fplist[26] = &f_getuerr; // 0x9D
   fplist[27] = &f_resetuart; // 0x9E
   fplist[28] = &f_readrate; // 0x9F
}

BYTE func_invoke(unsigned char code, char *data, char *result) {
   if (code < BASE_CMD_ID)
      return FUNC_CMD_NOT_VALID;

   if ((code - BASE_CMD_ID) >= MAX_FUNC_NUM)
      return FUNC_CMD_NOT_VALID;

   if (fplist[code - BASE_CMD_ID] == NULL)
      return FUNC_CMD_NOT_DEFINED;

   return (fplist[code - BASE_CMD_ID](data, result));
}

BYTE hpfunc_invoke(unsigned char code, char *data, char *result) {
   if (code < BASE_HPCMD_ID)
      return FUNC_CMD_NOT_VALID;

   if ((code - BASE_HPCMD_ID) >= MAX_HPFUNC_NUM)
      return FUNC_CMD_NOT_VALID;

   if (hpfunc[code - BASE_HPCMD_ID] == NULL)
      return FUNC_CMD_NOT_DEFINED;

   return (hpfunc[code - BASE_HPCMD_ID](data, result));
}

static const char *put_rc(FRESULT rc) {

   const char *str =
           "OK\0" "DISK_ERR\0" "INT_ERR\0" "NOT_READY\0" "NO_FILE\0" "NO_PATH\0"
           "INVALID_NAME\0" "DENIED\0" "EXIST\0" "INVALID_OBJECT\0" "WRITE_PROTECTED\0"
           "INVALID_DRIVE\0" "NOT_ENABLED\0" "NO_FILE_SYSTEM\0" "MKFS_ABORTED\0" "TIMEOUT\0"
           "LOCKED\0" "NOT_ENOUGH_CORE\0" "TOO_MANY_OPEN_FILES\0";
   FRESULT i;

   for (i = 0; i != rc && *str; i++) {
      while (*str++);
   }

   return (str);
}

BYTE f_reset(char *data, char *result) {
   Reset();
   return FUNC_CMD_OK; // never reached...
}

BYTE f_clear(char *data, char *result) {

   BYTE retval;

   uartbuf_init();
   memsetup(); // clock reset
   init_bcgrp();

   // reset UART error log
   uerrlog.uart1_ferr = 0;
   uerrlog.uart1_oerr = 0;
   uerrlog.uart2_ferr = 0;
   uerrlog.uart2_oerr = 0;

   retval = FUNC_EXEC_OK;
   sprintf(result, "%d|", retval);

   return FUNC_CMD_OK;
}

BYTE f_echo(char *data, char *result) {

   BYTE retval;

   retval = FUNC_EXEC_OK;
   sprintf(result, "%d|%s", retval, data);

   return FUNC_CMD_OK;
}

BYTE f_setbcid(char *data, char *result) {

   UINT id;
   int nconv = 0;
   int retval = 0;
   FRESULT fres;
   UINT br;

   nconv = sscanf(data, "%X", &id);

   if (nconv != 1) {

      retval = FUNC_EXEC_BAD_ARGS_TYPE;
      sprintf(result, "%d|", retval);
      return FUNC_CMD_OK;
   }

   if ((id >= 0) && (id <= UNICAST_MAX_IDB)) {

      set_bcid(id);

      f_unlink(ID_USD_FILENAME);

      fres = f_open(&File, ID_USD_FILENAME, FA_CREATE_ALWAYS | FA_WRITE);
      if (fres == 0)
         fres = f_write(&File, data, strlen(data), &br);

      f_close(&File);

      sprintf(result, "%d,%s|", (UINT) fres, put_rc(fres));

   } else {

      retval = FUNC_EXEC_BAD_ARGS_VALUE;
      sprintf(result, "%d|", retval);
   }

   return FUNC_CMD_OK;
}

BYTE f_setbcgrp(char *data, char *result) {

   UINT grp;
   int nconv = 0;
   int retval = 0;

   nconv = sscanf(data, "%X", &grp);

   if (nconv != 1) {

      retval = FUNC_EXEC_BAD_ARGS_TYPE;
      sprintf(result, "%d|", retval);
      return FUNC_CMD_OK;
   }

   if ((grp >= MULTICAST_BASE_IDB) && (grp <= MULTICAST_MAX_IDB)) {

      retval = FUNC_EXEC_OK;
      sprintf(result, "%d|", retval);
      add_bcgrp(grp);
   } else {

      retval = FUNC_EXEC_BAD_ARGS_VALUE;
      sprintf(result, "%d|", retval);
   }

   return FUNC_CMD_OK;
}

BYTE f_getvoltage(char *data, char *result) {

   UINT adcval1, adcval2, adcval3, adcval4, adcval5;
   double v10, v18, v25, v33, v36;

   adcval1 = adcval2 = adcval3 = adcval4 = adcval5 = 0;
   v10 = v18 = v25 = v33 = v36 = 0;

   adcval1 = mux_getout(MUX_CHAN_1V0);
   adcval2 = mux_getout(MUX_CHAN_1V8);
   adcval3 = mux_getout(MUX_CHAN_2V5);
   adcval4 = mux_getout(MUX_CHAN_3V3);
   adcval5 = mux_getout(MUX_CHAN_3V6);

   v10 = (adcval1 * 0.732) / 1000;
   v18 = (adcval2 * 0.732) / 1000;
   v25 = (adcval3 * 0.732) / 1000;
   v33 = (adcval4 * 1.142) / 1000;
   v36 = (adcval5 * 1.142) / 1000;

   sprintf(result, "%d|%.2f,%.2f,%.2f,%.2f,%.2f", FUNC_EXEC_OK, v10, v18, v25, v33, v36);

   return FUNC_CMD_OK;
}

BYTE f_gettemp(char *data, char *result) {

   UINT adcval1, adcval2;
   double temp1, temp2;
   UINT32 sfptemp_msb, sfptemp_lsb;

   adcval1 = adcval2 = 0;
   temp1 = temp2 = 0;

   adcval1 = mux_getout(MUX_CHAN_TEMP1);
   adcval2 = mux_getout(MUX_CHAN_TEMP2);

   temp1 = ((adcval1 * 0.732) - 600) / 10;
   temp2 = ((adcval2 * 0.732) - 600) / 10;

   sfptemp_msb = sfp_read(ADDR_SFP_TEMPMSB);
   sfptemp_lsb = sfp_read(ADDR_SFP_TEMPLSB) / 10;

   sprintf(result, "%d|%.2f,%.2f,%lu.%lu", FUNC_EXEC_OK, temp1, temp2, sfptemp_msb, sfptemp_lsb);

   return FUNC_CMD_OK;
}

BYTE f_usd_init(char *data, char *result) {

   BYTE retval = 0;

   retval = disk_initialize(0);

   sprintf(result, "%d|", retval);

   return FUNC_CMD_OK;
}

BYTE f_usd_mount(char *data, char *result) {

   FRESULT fres;

   fres = f_mount(0, &Fatfs);

   sprintf(result, "%d,%s|", (UINT) fres, put_rc(fres));

   return FUNC_CMD_OK;
}

BYTE f_fat_ls(char *data, char *result) {

#if _USE_LFN
   char Lfname[512];
   Finfo.lfname = Lfname;
   Finfo.lfsize = sizeof (Lfname);
#endif

   FRESULT fres;
   char tresult[512] = {'\0'};

   fres = f_opendir(&dir, (const TCHAR *) data);

   if (fres) {

      sprintf(result, "%d,%s|", (UINT) fres, put_rc(fres));

   } else {

      while (1) {

         fres = f_readdir(&dir, &Finfo);
         if ((fres != FR_OK) || !Finfo.fname[0])
            break;

         if (!strlen(Lfname))
            strcat(tresult, Finfo.fname);
         else
            strcat(tresult, Lfname);

         strcat(tresult, ",");
      }

      sprintf(result, "%d,%s|%s", (UINT) fres, put_rc(fres), tresult);

   }

   return FUNC_CMD_OK;
}

BYTE f_fat_cd(char *data, char *result) {

   FRESULT fres;

   fres = f_chdir(data);

   sprintf(result, "%d,%s|", (UINT) fres, put_rc(fres));

   return FUNC_CMD_OK;
}

BYTE f_fat_pwd(char *data, char *result) {

   FRESULT fres;
   char cwd[128];

   fres = f_getcwd(cwd, sizeof (cwd));

   sprintf(result, "%d,%s|%s", (UINT) fres, put_rc(fres), cwd);

   return FUNC_CMD_OK;
}

BYTE f_fat_mkdir(char *data, char *result) {

   FRESULT fres;
   BYTE retval;

   fres = f_mkdir(data);
   retval = fres;

   sprintf(result, "%d,%s|", retval, put_rc(fres));

   return FUNC_CMD_OK;
}

BYTE f_fat_rm(char *data, char *result) {

   FRESULT fres;

   fres = f_unlink(data);

   sprintf(result, "%d,%s|", (UINT) fres, put_rc(fres));

   return FUNC_CMD_OK;
}

BYTE f_fat_mv(char *data, char *result) {

   FRESULT fres;

   BYTE retval;
   int nconv = 0;
   char oldname[128], newname[128];

   nconv = sscanf(data, "%s,%s", oldname, newname);

   if (nconv != 2) {
      retval = FUNC_EXEC_BAD_ARGS_TYPE;
      sprintf(result, "%d|", retval);
      return FUNC_CMD_OK;
   }

   fres = f_rename(oldname, newname);

   sprintf(result, "%d,%s|", (UINT) fres, put_rc(fres));

   return FUNC_CMD_OK;
}

BYTE f_fat_cp(char *data, char *result) {

   FRESULT fres;
   FIL file1, file2;
   BYTE Buff[4096];
   UINT s1, s2;

   BYTE retval;
   int nconv = 0;
   char source[128], dest[128];

   nconv = sscanf(data, "%s,%s", source, dest);

   if (nconv != 2) {
      retval = FUNC_EXEC_BAD_ARGS_TYPE;
      sprintf(result, "%d|", retval);
      return FUNC_CMD_OK;
   }

   fres = f_open(&file1, source, FA_OPEN_EXISTING | FA_READ);

   if (fres) {

      sprintf(result, "%d,%s|", (UINT) fres, put_rc(fres));
      return FUNC_CMD_OK;
   }

   fres = f_open(&file2, dest, FA_CREATE_ALWAYS | FA_WRITE);

   if (fres) {

      sprintf(result, "%d,%s|", (UINT) fres, put_rc(fres));
      return FUNC_CMD_OK;
   }

   while (1) {
      fres = f_read(&file1, Buff, sizeof (Buff), &s1);
      if (fres || s1 == 0) break; // error or eof
      fres = f_write(&file2, Buff, s1, &s2);
      if (fres || s2 < s1) break; // error or disk full
   }

   f_close(&file1);
   f_close(&file2);

   sprintf(result, "%d,%s|", (UINT) fres, put_rc(fres));

   return FUNC_CMD_OK;
}

BYTE f_fat_fopen(char *data, char *result) {

   FRESULT fres;
   char fname[128];
   BYTE mode, retval;
   int nconv = 0;

   nconv = sscanf(data, "%d,%s", &mode, fname);

   if (nconv != 2) {
      retval = FUNC_EXEC_BAD_ARGS_TYPE;
      sprintf(result, "%d|", retval);
      return FUNC_CMD_OK;
   }

   fres = f_open(&File, fname, mode);

   sprintf(result, "%d,%s|", (UINT) fres, put_rc(fres));

   return FUNC_CMD_OK;
}

BYTE f_fat_fclose(char *data, char *result) {

   FRESULT fres;

   fres = f_close(&File);

   sprintf(result, "%d,%s|", (UINT) fres, put_rc(fres));

   return FUNC_CMD_OK;
}

BYTE f_fat_fseek(char *data, char *result) {

   FRESULT fres;
   int nconv = 0;
   BYTE retval;
   long p1;

   nconv = sscanf(data, "%ld", &p1);

   if (nconv != 1) {
      retval = FUNC_EXEC_BAD_ARGS_TYPE;
      sprintf(result, "%d|", retval);
      return FUNC_CMD_OK;
   }

   fres = f_lseek(&File, p1);

   sprintf(result, "%d,%s|", (UINT) fres, put_rc(fres));

   return FUNC_CMD_OK;
}

BYTE f_fat_fread(char *data, char *result) {

   FRESULT fres;
   unsigned char buff[MAX_DATA_SIZE / 2];
   char str[MAX_DATA_SIZE];
   UINT br;

   fres = f_read(&File, buff, (MAX_DATA_SIZE / 2) - 1, &br);

   if (fres) {
      sprintf(result, "%d|", FUNC_EXEC_BAD_ARGS_TYPE);
      return FUNC_CMD_OK;
   }

   base64_encode((unsigned char const *) buff, str, br);

   if (fres || br == 0)
      sprintf(result, "%d|%s", FUNC_EXEC_OK, str);
   else
      sprintf(result, "%d|%s", FUNC_EXEC_INPROGRESS, str);

   return FUNC_CMD_OK;
}

BYTE f_fat_fwrite(char *data, char *result) {

   FRESULT fres;
   char buf[MAX_DATA_SIZE];
   UINT len;
   UINT bw;

   base64_decode((unsigned char const *) data, buf, &len);

   fres = f_write(&File, buf, len, &bw);

   sprintf(result, "%d,%s|", (UINT) fres, put_rc(fres));

   return FUNC_CMD_OK;
}

BYTE f_fpga_read(char *data, char *result) {

   int nconv = 0;
   BYTE retval;
   UINT16 addr = 0;
   UINT32 value = 0;

   nconv = sscanf(data, "%X", &addr);

   if (nconv != 1) {

      retval = FUNC_EXEC_BAD_ARGS_TYPE;
      sprintf(result, "%d|", retval);
      return FUNC_CMD_OK;
   }

   value = fpga_read(addr);
   sprintf(result, "%d|0x%lX", FUNC_EXEC_OK, value);

   return FUNC_CMD_OK;
}

BYTE f_fpga_write(char *data, char *result) {

   int nconv = 0;
   BYTE retval;
   UINT16 value, addr;

   nconv = sscanf(data, "%X,%X", &value, &addr);

   if (nconv != 2) {

      retval = FUNC_EXEC_BAD_ARGS_TYPE;
      sprintf(result, "%d|", retval);
      return FUNC_CMD_OK;
   }

   fpga_write(value, addr);

   sprintf(result, "%d|0x%X,0x%X", FUNC_EXEC_OK, value, addr);

   return FUNC_CMD_OK;
}

BYTE f_jtag_prog(char *data, char *result) {

   BYTE retval;

   extprog = TRUE; // lock for Timer1

   jtagReset();
   setPort(TDI, 0);
   setPort(TCK, 0);
   setPort(TMS, 0);
   xsvf_setup();
   setPort(TMS, 1);
   retval = xsvfExecute(); // 0 = success , >0 = failed

   if (retval == 0) {
      set_fpgasw(FPGA_COMMAND_VAL);

      // reprogram FPGA from EEPROM

      FPGA_REPROGRAM = 1;
      FPGA_REPROGRAM = 0;
   }

   extprog = FALSE; // unlock for Timer1

   sprintf(result, "%d|", retval);

   return FUNC_CMD_OK;
}

BYTE f_fpga_status(char *data, char *result) {

   sprintf(result, "%d|%d,0x%03lX", FUNC_EXEC_OK, get_fpgasw(), fpga_read(FPGA_FW_VERSION));

   return FUNC_CMD_OK;
}

BYTE f_fpga_loadconf(char *data, char *result) {

   FRESULT fres;
   char filename[64];

   if (strlen(data) == 0) // no input file - take default
      sprintf(filename, "/conf/%s", FPGA_INI_FILE);
   else
      sprintf(filename, "/conf/%s", data);

   fres = fpga_loadconf(filename);

   sprintf(result, "%d,%s|", (UINT) fres, put_rc(fres));

   return FUNC_CMD_OK;
}

BYTE f_fpga_saveconf(char *data, char *result) {

   int i;
   UINT32 regval;
   FRESULT fres;
   char filename[64];

   if (strlen(data) == 0) // no output file - take default
      sprintf(filename, "/conf/%s", FPGA_INI_FILE);
   else
      sprintf(filename, "/conf/%s", data);

   f_unlink(filename);

   fres = f_open(&File, filename, FA_CREATE_ALWAYS | FA_WRITE);
   if (fres == 0) {

      f_printf(&File, "; === FPGA registers init file ===\n");
      f_printf(&File, "; syntax:  <FPGA addr> '=' <value> ';' <comments>\n");
      f_printf(&File, "; \n");

      for (i = 0; i < FPGA_REG_NUM; i++) {

         if (fpgareg[i].persistent) { // register to save

            regval = fpga_read(fpgareg[i].addr);
            f_printf(&File, "0x%02X = 0x%02X", fpgareg[i].addr, (UINT16) regval);
            f_printf(&File, "\t %s\n", fpgareg[i].comment);
         }
      }
   }

   f_close(&File);

   sprintf(result, "%d,%s|", (UINT) fres, put_rc(fres));

   return FUNC_CMD_OK;
}

BYTE f_adc_write(char *data, char *result) {

   int nconv = 0;
   UINT8 value;

   nconv = sscanf(data, "%X", &value);

   if (nconv != 1) {

      sprintf(result, "%d|", FUNC_EXEC_BAD_ARGS_TYPE);
      return FUNC_CMD_OK;
   }

   adcgain_write(value);
   sprintf(result, "%d|", FUNC_EXEC_OK);

   return FUNC_CMD_OK;
}

BYTE f_sfp_read(char *data, char *result) {

   int nconv = 0;
   BYTE retval;
   UINT16 addr = 0;
   UINT32 value = 0;

   nconv = sscanf(data, "%X", &addr);

   if (nconv != 1) {

      retval = FUNC_EXEC_BAD_ARGS_TYPE;
      sprintf(result, "%d|", retval);
      return FUNC_CMD_OK;
   }

   value = sfp_read(addr);
   sprintf(result, "%d|0x%lX", FUNC_EXEC_OK, value);

   return FUNC_CMD_OK;
}

BYTE f_getuerr(char *data, char *result) {

   static UINT16 counter = 0;

   sprintf(result, "%d|U1FERR=%d,U1OERR=%d,U2FERR=%d,U2OERR=%d,COUNTER=%d", FUNC_EXEC_OK, uerrlog.uart1_ferr, uerrlog.uart1_oerr,
           uerrlog.uart2_ferr, uerrlog.uart2_oerr, counter++);

   return FUNC_CMD_OK;
}

BYTE f_resetuart(char *data, char *result) {

   PORTCbits.RC6 = 0;
   PORTCbits.RC7 = 0;

   __delay_ms(100);

   sprintf(result, "0|");

   return FUNC_CMD_OK;
}

BYTE f_readrate(char *data, char *result) {

   UINT16 lsb, msb, index;
   int i, nconv;
   int fee;
   BYTE retval;
   UINT16 rate_telA, rate_telB;

   nconv = sscanf(data, "%d", &fee);

    if (nconv != 1) {

      retval = FUNC_EXEC_BAD_ARGS_TYPE;
      sprintf(result, "%d|", retval);
      return FUNC_CMD_OK;
   }

   if( (fee < 0) || (fee > 7) ) {

       retval = FUNC_EXEC_BAD_ARGS_VALUE;
       sprintf(result, "%d|", retval);
       return FUNC_CMD_OK;
   }

   IEC0bits.T2IE = 0;           // disable Timer2
   fpga_write(0x001, 0x100);    // lock

   index = 0x110 + (fee * 4);
   lsb = fpga_read(index);
   msb = fpga_read(index + 1);

   //rate_telA = (UINT16)lsb + (UINT16)(msb << 8);
   rate_telA = lsb + (msb << 8);

   index = 0x110 + (fee * 4 + 2);
   lsb = fpga_read(index);
   msb = fpga_read(index + 1);

   //rate_telB = (UINT16)lsb + (UINT16)(msb << 8);
   rate_telB = lsb + (msb << 8);

   fpga_write(0x000, 0x100);    // unlock
   IEC0bits.T2IE = 1;           // enable Timer2

   sprintf(result, "0|%d,%d", rate_telA, rate_telB);

   return FUNC_CMD_OK;
}

// EOF
