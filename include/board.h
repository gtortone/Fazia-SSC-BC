#ifndef _BOARD_H
#define _BOARD_H

#include <libpic30.h>

#define FOSC            79226000UL  // clock-frequecy in Hz with suffix LL (64-bit-long)
#define FCY             (FOSC/2)    // MCU is running at FCY MIPS

#define __delay_ms(d) \
  { __delay32( (unsigned long) (((unsigned long long) d)*(FCY)/1000ULL)); }
#define __delay_us(d) \
  { __delay32( (unsigned long) (((unsigned long long) d)*(FCY)/1000000ULL)); }

#endif

// EOF

