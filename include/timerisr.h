#ifndef _TIMERINT_H_
#define _TIMERINT_H_

#include <Generic.h>

void SetAckTimer(UINT value);
UINT GetAckTimer(void);

void __attribute__((__interrupt__, no_auto_psv)) _T1Interrupt(void);
void __attribute__((__interrupt__, no_auto_psv)) _T2Interrupt(void);

#endif

// EOF
