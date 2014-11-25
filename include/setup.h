#ifndef _SETUP_H
#define _SETUP_H

#include <Generic.h>

#define UNICAST_MAX_IDB     0xEFF

#define MULTICAST_BASE_IDB  0xF00
#define MULTICAST_MAX_IDB   0xFFD
#define BROADCAST_IDB       0xFFE

#define DEFAULT_IDB         0x000

#define ID_USD_FILENAME     "/conf/_BCID"

#define JTAGTDI             PORTBbits.RB5
#define JTAGTCK             PORTBbits.RB8
#define JTAGTDO             PORTBbits.RB6
#define JTAGTMS             PORTBbits.RB7

#define JTAGTDI_TRIS        TRISBbits.TRISB5
#define JTAGTCK_TRIS        TRISBbits.TRISB8
#define JTAGTD0_TRIS        TRISBbits.TRISB6
#define JTAGTMS_TRIS        TRISBbits.TRISB7

void ucsetup(void);
void memsetup(void);

void set_bcid(UINT id);
void refresh_bcid(void);
UINT get_bcid(void);

void init_bcgrp(void);
void add_bcgrp(UINT grp);
void del_bcgrp(UINT grp);
BOOL in_bcgrp(UINT grp);

#endif

// EOF

