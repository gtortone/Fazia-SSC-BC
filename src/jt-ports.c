//Our open source (CC-0) version of the ports.c from XAPP058
// CC-0, public domain
//
// You'll also need lenval.c and micro.c from XAPP058
// IT doesn't have a stated license so we're hesitant to include it in SVN
// Get it here: http://www.xilinx.com/support/documentation/application_notes/xapp058.zip
#include <p33Fxxxx.h>

#include "setup.h"
#include "jt-ports.h"
#include "ff.h"

#define MAX_BUFFER 1024
static unsigned char buf[MAX_BUFFER]; //buffer to hold incoming bytes
static unsigned int bufBytes = 0, bufPointer = 0;

void xsvf_setup(void) {
   bufBytes = 0;
}

void setPort(short p, short val) {
   if (p == TMS) 
      JTAGTMS = (unsigned char) val;
   if (p == TDI) 
      JTAGTDI = (unsigned char) val;
   if (p == TCK)
      JTAGTCK = (unsigned char) val;
}

void readByte(unsigned char *data) {

   extern FIL File;

   if (bufBytes == 0) {
      f_read(&File, buf, MAX_BUFFER, &bufBytes);
      bufPointer = 0;
   }

   (*data) = buf[bufPointer];

   bufPointer++;
   bufBytes--;
}

unsigned char readTDOBit() {
   return JTAGTDO;
}

void waitTime(long microsec) {
   volatile long i;

   for (i = 0; i < microsec; ++i) {
      setPort(TCK, 0); /* set the TCK port to low  */
      setPort(TCK, 1); /* set the TCK port to high */
   }
}

// EOF
