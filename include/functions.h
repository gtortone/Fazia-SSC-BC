#ifndef _FUNC_H
#define _FUNC_H

#include <Generic.h>
#include "ff.h"

#define MAX_FUNC_NUM    29
#define MAX_HPFUNC_NUM   3

#define FUNC_CMD_OK                 0x00
#define FUNC_CMD_NOT_VALID          0x01
#define FUNC_CMD_NOT_DEFINED        0x02

#define FUNC_EXEC_OK                0x00
#define FUNC_EXEC_BAD_ARGS_TYPE     0x01
#define FUNC_EXEC_BAD_ARGS_VALUE    0x02
#define FUNC_EXEC_INPROGRESS        0xFF

void func_init(void);
BYTE func_invoke(unsigned char code, char *data, char *result);
BYTE hpfunc_invoke(unsigned char code, char *data, char *result);

BYTE f_reset(char *data, char *result);
BYTE f_clear(char *data, char *result);
BYTE f_echo(char *data, char *result);

BYTE f_setbcid(char *data, char *result);
BYTE f_setbcgrp(char *data, char *result);
BYTE f_getvoltage(char *data, char *result);
BYTE f_gettemp(char *data, char *result);
//static const char *put_rc(FRESULT rc);
BYTE f_usd_init(char *data, char *result);
BYTE f_usd_mount(char *data, char *result);
BYTE f_fat_ls(char *data, char *result);
BYTE f_fat_cd(char *data, char *result);
BYTE f_fat_pwd(char *data, char *result);
BYTE f_fat_mkdir(char *data, char *result);
BYTE f_fat_rm(char *data, char *result);
BYTE f_fat_mv(char *data, char *result);
BYTE f_fat_cp(char *data, char *result);
BYTE f_fat_fopen(char *data, char *result);
BYTE f_fat_fclose(char *data, char *result);
BYTE f_fat_fseek(char *data, char *result);
BYTE f_fat_fread(char *data, char *result);
BYTE f_fat_fwrite(char *data, char *result);
BYTE f_fpga_read(char *data, char *result);
BYTE f_fpga_write(char *data, char *result);
BYTE f_jtag_prog(char *data, char *result);
BYTE f_fpga_status(char *data, char *result);
BYTE f_fpga_loadconf(char *data, char *result);
BYTE f_fpga_saveconf(char *data, char *result);
BYTE f_adc_write(char *data, char *result);
BYTE f_sfp_read(char *data, char *result);
BYTE f_getuerr(char *data, char *result);
BYTE f_resetuart(char *data, char *result);

#endif

// EOF

