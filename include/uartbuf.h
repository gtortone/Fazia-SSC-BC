#ifndef _UARTBUF_H_
#define _UARTBUF_H_

#include "cbuffer.h"
#include "frame.h"

#define MASTER_RX       0
#define MASTER_TX       1
//#define MASTER_HPRX     2
//#define MASTER_HPTX     3
#define SLAVE_RX        2
#define SLAVE_TX        3

void uart_rawputch(UINT channel, unsigned char d);

void uart_master_rawputch(unsigned char d);        // for xprintf.c functions
void uart_slave_rawputch(unsigned char d);

void uartbuf_alloc(void);
void uartbuf_init(void);
void uartbuf_reset(UINT channel);

void uartbuf_flush(UINT channel);
UINT16 uartbuf_frameflush(UINT channel);

void uartbuf_getframe(UINT channel, unsigned char *f, UINT flen, UINT foffset);
void uartbuf_putframe(UINT channel, unsigned char *f);
void uartbuf_routeframe(UINT chsrc, UINT chdst, UINT flen, UINT foffset);

#endif

// EOF

