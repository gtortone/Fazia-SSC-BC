#ifndef _FPGA_H
#define _FPGA_H

#include <Generic.h>

#include "ff.h"

#define FPGA_FW_VERSION             0x51

#define FPGA_RUNNING        PORTBbits.RB10
#define FPGA_REPROGRAM      PORTBbits.RB9

#define FPGA_FW_NUM         3
#define FPGA_STARTUP_FW     "/conf/fw_fpga_startup.xsvf"
#define FPGA_BACKUP_FW      "/conf/fw_fpga_backup.xsvf"
#define FPGA_RESCUE_FW      "/conf/fw_fpga_rescue.xsvf"

#define FPGA_NOFW_VAL        0x00
#define FPGA_DEFAULT_VAL     0x01
#define FPGA_STARTUP_VAL     0x02
#define FPGA_BACKUP_VAL      0x04
#define FPGA_RESCUE_VAL      0x08
#define FPGA_COMMAND_VAL     0x10

#define FPGA_REG_NUM         25
#define FPGA_INI_FILE       "fpga.ini"

typedef struct {

   const UINT16 addr;
   const char comment[64];
   const BOOL persistent;

} fpgareg_t;

BOOL fpga_isrunning(void);
BOOL fpgafw_isvalid(void);
BOOL get_fpga_fwver(void);
BYTE get_fpgasw(void);
void set_fpgasw(BYTE type);
FRESULT fpga_loadconf(char *filename);

#endif

// EOF
