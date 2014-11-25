#ifndef _UARTERROR_H
#define _UARTERROR_H

typedef struct {
    UINT16         uart1_oerr;  // UART1 overrun error
    UINT16         uart1_ferr;  // UART1 frame error
    UINT16         uart2_oerr;  // UART1 overrun error
    UINT16         uart2_ferr;  // UART1 frame error

} UartErrLog;

#endif

//EOF
