#include <p33Fxxxx.h>

#include "board.h"
#include "setup.h"
#include "jt-micro.h"
#include "jt-ports.h"

////#define JTAGDATASETTLE 20
////#define JTAGCLOCK 100
#define JTAGDATASETTLE 2
#define JTAGCLOCK 1

void jtagReset(void);
void jtagTMSHigh(void);
void jtagTMSLow(void);
void jtagClockTicks(unsigned char c);
void jtagClockHigh(void);
void jtagClockLow(void);

struct _JTAG{
	unsigned char HiZ:1;
} jtagSettings;

void jtagReset(void){
	jtagTMSHigh();
	jtagClockTicks(10);//one extra if clk starts high
	jtagTMSLow();//always return to low for writes
}

void jtagClockTicks(unsigned char c){
	unsigned char i;

	for(i=0;i<c;i++){
		jtagClockHigh();
		jtagClockLow();
	}
}

void jtagClockHigh(void){
	JTAGTCK_TRIS=(~jtagSettings.HiZ);//set output
	JTAGTCK=jtagSettings.HiZ;//data
	__delay_us(JTAGCLOCK);//delay
}

void jtagClockLow(void){
	JTAGTCK=0;//set clock low
	JTAGTCK_TRIS=0;//set clock output for HIGHZ
	__delay_us(JTAGCLOCK);//delay
}

void jtagTMSHigh(void){
	JTAGTMS_TRIS=(~jtagSettings.HiZ);//set output
	JTAGTMS=jtagSettings.HiZ;//data
	__delay_us(JTAGDATASETTLE);//delay
}

void jtagTMSLow(void){
	JTAGTMS=0;//cs
	JTAGTMS_TRIS=0;//cs output for HIGHZ
	__delay_us(JTAGDATASETTLE);//delay
}

// EOF
