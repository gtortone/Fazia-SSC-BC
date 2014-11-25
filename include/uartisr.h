#ifndef _UARTINT_H_
#define _UARTINT_H_

#include <Generic.h>

#define _DI()		__asm__ volatile("disi #0x3FFF")
#define _EI()		__asm__ volatile("disi #0")

void __attribute__((__interrupt__, no_auto_psv)) _U1RXInterrupt(void);
void __attribute__((__interrupt__, no_auto_psv)) _U2RXInterrupt(void);

#endif

// EOF
