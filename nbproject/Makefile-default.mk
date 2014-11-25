#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=mkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/BlockCard-SSC.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/BlockCard-SSC.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=src/main.c src/xprintf.c src/setup.c src/cbuffer.c src/uartbuf.c src/frame.c src/functions.c src/timerisr.c src/uartisr.c src/spi-sw.c src/i2c-sw.c src/spi-dev.c src/i2c-dev.c src/mmc.c src/ff.c src/ccsbcs.c src/base64.c src/jt-lenval.c src/jt-ports.c src/jt-core.c src/jt-micro.c src/fpga.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/src/main.o ${OBJECTDIR}/src/xprintf.o ${OBJECTDIR}/src/setup.o ${OBJECTDIR}/src/cbuffer.o ${OBJECTDIR}/src/uartbuf.o ${OBJECTDIR}/src/frame.o ${OBJECTDIR}/src/functions.o ${OBJECTDIR}/src/timerisr.o ${OBJECTDIR}/src/uartisr.o ${OBJECTDIR}/src/spi-sw.o ${OBJECTDIR}/src/i2c-sw.o ${OBJECTDIR}/src/spi-dev.o ${OBJECTDIR}/src/i2c-dev.o ${OBJECTDIR}/src/mmc.o ${OBJECTDIR}/src/ff.o ${OBJECTDIR}/src/ccsbcs.o ${OBJECTDIR}/src/base64.o ${OBJECTDIR}/src/jt-lenval.o ${OBJECTDIR}/src/jt-ports.o ${OBJECTDIR}/src/jt-core.o ${OBJECTDIR}/src/jt-micro.o ${OBJECTDIR}/src/fpga.o
POSSIBLE_DEPFILES=${OBJECTDIR}/src/main.o.d ${OBJECTDIR}/src/xprintf.o.d ${OBJECTDIR}/src/setup.o.d ${OBJECTDIR}/src/cbuffer.o.d ${OBJECTDIR}/src/uartbuf.o.d ${OBJECTDIR}/src/frame.o.d ${OBJECTDIR}/src/functions.o.d ${OBJECTDIR}/src/timerisr.o.d ${OBJECTDIR}/src/uartisr.o.d ${OBJECTDIR}/src/spi-sw.o.d ${OBJECTDIR}/src/i2c-sw.o.d ${OBJECTDIR}/src/spi-dev.o.d ${OBJECTDIR}/src/i2c-dev.o.d ${OBJECTDIR}/src/mmc.o.d ${OBJECTDIR}/src/ff.o.d ${OBJECTDIR}/src/ccsbcs.o.d ${OBJECTDIR}/src/base64.o.d ${OBJECTDIR}/src/jt-lenval.o.d ${OBJECTDIR}/src/jt-ports.o.d ${OBJECTDIR}/src/jt-core.o.d ${OBJECTDIR}/src/jt-micro.o.d ${OBJECTDIR}/src/fpga.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/src/main.o ${OBJECTDIR}/src/xprintf.o ${OBJECTDIR}/src/setup.o ${OBJECTDIR}/src/cbuffer.o ${OBJECTDIR}/src/uartbuf.o ${OBJECTDIR}/src/frame.o ${OBJECTDIR}/src/functions.o ${OBJECTDIR}/src/timerisr.o ${OBJECTDIR}/src/uartisr.o ${OBJECTDIR}/src/spi-sw.o ${OBJECTDIR}/src/i2c-sw.o ${OBJECTDIR}/src/spi-dev.o ${OBJECTDIR}/src/i2c-dev.o ${OBJECTDIR}/src/mmc.o ${OBJECTDIR}/src/ff.o ${OBJECTDIR}/src/ccsbcs.o ${OBJECTDIR}/src/base64.o ${OBJECTDIR}/src/jt-lenval.o ${OBJECTDIR}/src/jt-ports.o ${OBJECTDIR}/src/jt-core.o ${OBJECTDIR}/src/jt-micro.o ${OBJECTDIR}/src/fpga.o

# Source Files
SOURCEFILES=src/main.c src/xprintf.c src/setup.c src/cbuffer.c src/uartbuf.c src/frame.c src/functions.c src/timerisr.c src/uartisr.c src/spi-sw.c src/i2c-sw.c src/spi-dev.c src/i2c-dev.c src/mmc.c src/ff.c src/ccsbcs.c src/base64.c src/jt-lenval.c src/jt-ports.c src/jt-core.c src/jt-micro.c src/fpga.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/BlockCard-SSC.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33FJ128GP804
MP_LINKER_FILE_OPTION=,-Tp33FJ128GP804.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/src/main.o: src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/main.o.d 
	@${RM} ${OBJECTDIR}/src/main.o.ok ${OBJECTDIR}/src/main.o.err 
	@${RM} ${OBJECTDIR}/src/main.o 
	@${FIXDEPS} "${OBJECTDIR}/src/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"./include" -O3 -fschedule-insns -fschedule-insns2 -MMD -MF "${OBJECTDIR}/src/main.o.d" -o ${OBJECTDIR}/src/main.o src/main.c    -fast-math
	
${OBJECTDIR}/src/xprintf.o: src/xprintf.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/xprintf.o.d 
	@${RM} ${OBJECTDIR}/src/xprintf.o.ok ${OBJECTDIR}/src/xprintf.o.err 
	@${RM} ${OBJECTDIR}/src/xprintf.o 
	@${FIXDEPS} "${OBJECTDIR}/src/xprintf.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"./include" -O3 -fschedule-insns -fschedule-insns2 -MMD -MF "${OBJECTDIR}/src/xprintf.o.d" -o ${OBJECTDIR}/src/xprintf.o src/xprintf.c    -fast-math
	
${OBJECTDIR}/src/setup.o: src/setup.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/setup.o.d 
	@${RM} ${OBJECTDIR}/src/setup.o.ok ${OBJECTDIR}/src/setup.o.err 
	@${RM} ${OBJECTDIR}/src/setup.o 
	@${FIXDEPS} "${OBJECTDIR}/src/setup.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"./include" -O3 -fschedule-insns -fschedule-insns2 -MMD -MF "${OBJECTDIR}/src/setup.o.d" -o ${OBJECTDIR}/src/setup.o src/setup.c    -fast-math
	
${OBJECTDIR}/src/cbuffer.o: src/cbuffer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/cbuffer.o.d 
	@${RM} ${OBJECTDIR}/src/cbuffer.o.ok ${OBJECTDIR}/src/cbuffer.o.err 
	@${RM} ${OBJECTDIR}/src/cbuffer.o 
	@${FIXDEPS} "${OBJECTDIR}/src/cbuffer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"./include" -O3 -fschedule-insns -fschedule-insns2 -MMD -MF "${OBJECTDIR}/src/cbuffer.o.d" -o ${OBJECTDIR}/src/cbuffer.o src/cbuffer.c    -fast-math
	
${OBJECTDIR}/src/uartbuf.o: src/uartbuf.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/uartbuf.o.d 
	@${RM} ${OBJECTDIR}/src/uartbuf.o.ok ${OBJECTDIR}/src/uartbuf.o.err 
	@${RM} ${OBJECTDIR}/src/uartbuf.o 
	@${FIXDEPS} "${OBJECTDIR}/src/uartbuf.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"./include" -O3 -fschedule-insns -fschedule-insns2 -MMD -MF "${OBJECTDIR}/src/uartbuf.o.d" -o ${OBJECTDIR}/src/uartbuf.o src/uartbuf.c    -fast-math
	
${OBJECTDIR}/src/frame.o: src/frame.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/frame.o.d 
	@${RM} ${OBJECTDIR}/src/frame.o.ok ${OBJECTDIR}/src/frame.o.err 
	@${RM} ${OBJECTDIR}/src/frame.o 
	@${FIXDEPS} "${OBJECTDIR}/src/frame.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"./include" -O3 -fschedule-insns -fschedule-insns2 -MMD -MF "${OBJECTDIR}/src/frame.o.d" -o ${OBJECTDIR}/src/frame.o src/frame.c    -fast-math
	
${OBJECTDIR}/src/functions.o: src/functions.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/functions.o.d 
	@${RM} ${OBJECTDIR}/src/functions.o.ok ${OBJECTDIR}/src/functions.o.err 
	@${RM} ${OBJECTDIR}/src/functions.o 
	@${FIXDEPS} "${OBJECTDIR}/src/functions.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"./include" -O3 -fschedule-insns -fschedule-insns2 -MMD -MF "${OBJECTDIR}/src/functions.o.d" -o ${OBJECTDIR}/src/functions.o src/functions.c    -fast-math
	
${OBJECTDIR}/src/timerisr.o: src/timerisr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/timerisr.o.d 
	@${RM} ${OBJECTDIR}/src/timerisr.o.ok ${OBJECTDIR}/src/timerisr.o.err 
	@${RM} ${OBJECTDIR}/src/timerisr.o 
	@${FIXDEPS} "${OBJECTDIR}/src/timerisr.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"./include" -O3 -fschedule-insns -fschedule-insns2 -MMD -MF "${OBJECTDIR}/src/timerisr.o.d" -o ${OBJECTDIR}/src/timerisr.o src/timerisr.c    -fast-math
	
${OBJECTDIR}/src/uartisr.o: src/uartisr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/uartisr.o.d 
	@${RM} ${OBJECTDIR}/src/uartisr.o.ok ${OBJECTDIR}/src/uartisr.o.err 
	@${RM} ${OBJECTDIR}/src/uartisr.o 
	@${FIXDEPS} "${OBJECTDIR}/src/uartisr.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"./include" -O3 -fschedule-insns -fschedule-insns2 -MMD -MF "${OBJECTDIR}/src/uartisr.o.d" -o ${OBJECTDIR}/src/uartisr.o src/uartisr.c    -fast-math
	
${OBJECTDIR}/src/spi-sw.o: src/spi-sw.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/spi-sw.o.d 
	@${RM} ${OBJECTDIR}/src/spi-sw.o.ok ${OBJECTDIR}/src/spi-sw.o.err 
	@${RM} ${OBJECTDIR}/src/spi-sw.o 
	@${FIXDEPS} "${OBJECTDIR}/src/spi-sw.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"./include" -O3 -fschedule-insns -fschedule-insns2 -MMD -MF "${OBJECTDIR}/src/spi-sw.o.d" -o ${OBJECTDIR}/src/spi-sw.o src/spi-sw.c    -fast-math
	
${OBJECTDIR}/src/i2c-sw.o: src/i2c-sw.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/i2c-sw.o.d 
	@${RM} ${OBJECTDIR}/src/i2c-sw.o.ok ${OBJECTDIR}/src/i2c-sw.o.err 
	@${RM} ${OBJECTDIR}/src/i2c-sw.o 
	@${FIXDEPS} "${OBJECTDIR}/src/i2c-sw.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"./include" -O3 -fschedule-insns -fschedule-insns2 -MMD -MF "${OBJECTDIR}/src/i2c-sw.o.d" -o ${OBJECTDIR}/src/i2c-sw.o src/i2c-sw.c    -fast-math
	
${OBJECTDIR}/src/spi-dev.o: src/spi-dev.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/spi-dev.o.d 
	@${RM} ${OBJECTDIR}/src/spi-dev.o.ok ${OBJECTDIR}/src/spi-dev.o.err 
	@${RM} ${OBJECTDIR}/src/spi-dev.o 
	@${FIXDEPS} "${OBJECTDIR}/src/spi-dev.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"./include" -O3 -fschedule-insns -fschedule-insns2 -MMD -MF "${OBJECTDIR}/src/spi-dev.o.d" -o ${OBJECTDIR}/src/spi-dev.o src/spi-dev.c    -fast-math
	
${OBJECTDIR}/src/i2c-dev.o: src/i2c-dev.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/i2c-dev.o.d 
	@${RM} ${OBJECTDIR}/src/i2c-dev.o.ok ${OBJECTDIR}/src/i2c-dev.o.err 
	@${RM} ${OBJECTDIR}/src/i2c-dev.o 
	@${FIXDEPS} "${OBJECTDIR}/src/i2c-dev.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"./include" -O3 -fschedule-insns -fschedule-insns2 -MMD -MF "${OBJECTDIR}/src/i2c-dev.o.d" -o ${OBJECTDIR}/src/i2c-dev.o src/i2c-dev.c    -fast-math
	
${OBJECTDIR}/src/mmc.o: src/mmc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/mmc.o.d 
	@${RM} ${OBJECTDIR}/src/mmc.o.ok ${OBJECTDIR}/src/mmc.o.err 
	@${RM} ${OBJECTDIR}/src/mmc.o 
	@${FIXDEPS} "${OBJECTDIR}/src/mmc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"./include" -O3 -fschedule-insns -fschedule-insns2 -MMD -MF "${OBJECTDIR}/src/mmc.o.d" -o ${OBJECTDIR}/src/mmc.o src/mmc.c    -fast-math
	
${OBJECTDIR}/src/ff.o: src/ff.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/ff.o.d 
	@${RM} ${OBJECTDIR}/src/ff.o.ok ${OBJECTDIR}/src/ff.o.err 
	@${RM} ${OBJECTDIR}/src/ff.o 
	@${FIXDEPS} "${OBJECTDIR}/src/ff.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"./include" -O3 -fschedule-insns -fschedule-insns2 -MMD -MF "${OBJECTDIR}/src/ff.o.d" -o ${OBJECTDIR}/src/ff.o src/ff.c    -fast-math
	
${OBJECTDIR}/src/ccsbcs.o: src/ccsbcs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/ccsbcs.o.d 
	@${RM} ${OBJECTDIR}/src/ccsbcs.o.ok ${OBJECTDIR}/src/ccsbcs.o.err 
	@${RM} ${OBJECTDIR}/src/ccsbcs.o 
	@${FIXDEPS} "${OBJECTDIR}/src/ccsbcs.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"./include" -O3 -fschedule-insns -fschedule-insns2 -MMD -MF "${OBJECTDIR}/src/ccsbcs.o.d" -o ${OBJECTDIR}/src/ccsbcs.o src/ccsbcs.c    -fast-math
	
${OBJECTDIR}/src/base64.o: src/base64.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/base64.o.d 
	@${RM} ${OBJECTDIR}/src/base64.o.ok ${OBJECTDIR}/src/base64.o.err 
	@${RM} ${OBJECTDIR}/src/base64.o 
	@${FIXDEPS} "${OBJECTDIR}/src/base64.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"./include" -O3 -fschedule-insns -fschedule-insns2 -MMD -MF "${OBJECTDIR}/src/base64.o.d" -o ${OBJECTDIR}/src/base64.o src/base64.c    -fast-math
	
${OBJECTDIR}/src/jt-lenval.o: src/jt-lenval.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/jt-lenval.o.d 
	@${RM} ${OBJECTDIR}/src/jt-lenval.o.ok ${OBJECTDIR}/src/jt-lenval.o.err 
	@${RM} ${OBJECTDIR}/src/jt-lenval.o 
	@${FIXDEPS} "${OBJECTDIR}/src/jt-lenval.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"./include" -O3 -fschedule-insns -fschedule-insns2 -MMD -MF "${OBJECTDIR}/src/jt-lenval.o.d" -o ${OBJECTDIR}/src/jt-lenval.o src/jt-lenval.c    -fast-math
	
${OBJECTDIR}/src/jt-ports.o: src/jt-ports.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/jt-ports.o.d 
	@${RM} ${OBJECTDIR}/src/jt-ports.o.ok ${OBJECTDIR}/src/jt-ports.o.err 
	@${RM} ${OBJECTDIR}/src/jt-ports.o 
	@${FIXDEPS} "${OBJECTDIR}/src/jt-ports.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"./include" -O3 -fschedule-insns -fschedule-insns2 -MMD -MF "${OBJECTDIR}/src/jt-ports.o.d" -o ${OBJECTDIR}/src/jt-ports.o src/jt-ports.c    -fast-math
	
${OBJECTDIR}/src/jt-core.o: src/jt-core.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/jt-core.o.d 
	@${RM} ${OBJECTDIR}/src/jt-core.o.ok ${OBJECTDIR}/src/jt-core.o.err 
	@${RM} ${OBJECTDIR}/src/jt-core.o 
	@${FIXDEPS} "${OBJECTDIR}/src/jt-core.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"./include" -O3 -fschedule-insns -fschedule-insns2 -MMD -MF "${OBJECTDIR}/src/jt-core.o.d" -o ${OBJECTDIR}/src/jt-core.o src/jt-core.c    -fast-math
	
${OBJECTDIR}/src/jt-micro.o: src/jt-micro.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/jt-micro.o.d 
	@${RM} ${OBJECTDIR}/src/jt-micro.o.ok ${OBJECTDIR}/src/jt-micro.o.err 
	@${RM} ${OBJECTDIR}/src/jt-micro.o 
	@${FIXDEPS} "${OBJECTDIR}/src/jt-micro.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"./include" -O3 -fschedule-insns -fschedule-insns2 -MMD -MF "${OBJECTDIR}/src/jt-micro.o.d" -o ${OBJECTDIR}/src/jt-micro.o src/jt-micro.c    -fast-math
	
${OBJECTDIR}/src/fpga.o: src/fpga.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/fpga.o.d 
	@${RM} ${OBJECTDIR}/src/fpga.o.ok ${OBJECTDIR}/src/fpga.o.err 
	@${RM} ${OBJECTDIR}/src/fpga.o 
	@${FIXDEPS} "${OBJECTDIR}/src/fpga.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"./include" -O3 -fschedule-insns -fschedule-insns2 -MMD -MF "${OBJECTDIR}/src/fpga.o.d" -o ${OBJECTDIR}/src/fpga.o src/fpga.c    -fast-math
	
else
${OBJECTDIR}/src/main.o: src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/main.o.d 
	@${RM} ${OBJECTDIR}/src/main.o.ok ${OBJECTDIR}/src/main.o.err 
	@${RM} ${OBJECTDIR}/src/main.o 
	@${FIXDEPS} "${OBJECTDIR}/src/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"./include" -O3 -fschedule-insns -fschedule-insns2 -MMD -MF "${OBJECTDIR}/src/main.o.d" -o ${OBJECTDIR}/src/main.o src/main.c    -fast-math
	
${OBJECTDIR}/src/xprintf.o: src/xprintf.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/xprintf.o.d 
	@${RM} ${OBJECTDIR}/src/xprintf.o.ok ${OBJECTDIR}/src/xprintf.o.err 
	@${RM} ${OBJECTDIR}/src/xprintf.o 
	@${FIXDEPS} "${OBJECTDIR}/src/xprintf.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"./include" -O3 -fschedule-insns -fschedule-insns2 -MMD -MF "${OBJECTDIR}/src/xprintf.o.d" -o ${OBJECTDIR}/src/xprintf.o src/xprintf.c    -fast-math
	
${OBJECTDIR}/src/setup.o: src/setup.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/setup.o.d 
	@${RM} ${OBJECTDIR}/src/setup.o.ok ${OBJECTDIR}/src/setup.o.err 
	@${RM} ${OBJECTDIR}/src/setup.o 
	@${FIXDEPS} "${OBJECTDIR}/src/setup.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"./include" -O3 -fschedule-insns -fschedule-insns2 -MMD -MF "${OBJECTDIR}/src/setup.o.d" -o ${OBJECTDIR}/src/setup.o src/setup.c    -fast-math
	
${OBJECTDIR}/src/cbuffer.o: src/cbuffer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/cbuffer.o.d 
	@${RM} ${OBJECTDIR}/src/cbuffer.o.ok ${OBJECTDIR}/src/cbuffer.o.err 
	@${RM} ${OBJECTDIR}/src/cbuffer.o 
	@${FIXDEPS} "${OBJECTDIR}/src/cbuffer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"./include" -O3 -fschedule-insns -fschedule-insns2 -MMD -MF "${OBJECTDIR}/src/cbuffer.o.d" -o ${OBJECTDIR}/src/cbuffer.o src/cbuffer.c    -fast-math
	
${OBJECTDIR}/src/uartbuf.o: src/uartbuf.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/uartbuf.o.d 
	@${RM} ${OBJECTDIR}/src/uartbuf.o.ok ${OBJECTDIR}/src/uartbuf.o.err 
	@${RM} ${OBJECTDIR}/src/uartbuf.o 
	@${FIXDEPS} "${OBJECTDIR}/src/uartbuf.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"./include" -O3 -fschedule-insns -fschedule-insns2 -MMD -MF "${OBJECTDIR}/src/uartbuf.o.d" -o ${OBJECTDIR}/src/uartbuf.o src/uartbuf.c    -fast-math
	
${OBJECTDIR}/src/frame.o: src/frame.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/frame.o.d 
	@${RM} ${OBJECTDIR}/src/frame.o.ok ${OBJECTDIR}/src/frame.o.err 
	@${RM} ${OBJECTDIR}/src/frame.o 
	@${FIXDEPS} "${OBJECTDIR}/src/frame.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"./include" -O3 -fschedule-insns -fschedule-insns2 -MMD -MF "${OBJECTDIR}/src/frame.o.d" -o ${OBJECTDIR}/src/frame.o src/frame.c    -fast-math
	
${OBJECTDIR}/src/functions.o: src/functions.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/functions.o.d 
	@${RM} ${OBJECTDIR}/src/functions.o.ok ${OBJECTDIR}/src/functions.o.err 
	@${RM} ${OBJECTDIR}/src/functions.o 
	@${FIXDEPS} "${OBJECTDIR}/src/functions.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"./include" -O3 -fschedule-insns -fschedule-insns2 -MMD -MF "${OBJECTDIR}/src/functions.o.d" -o ${OBJECTDIR}/src/functions.o src/functions.c    -fast-math
	
${OBJECTDIR}/src/timerisr.o: src/timerisr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/timerisr.o.d 
	@${RM} ${OBJECTDIR}/src/timerisr.o.ok ${OBJECTDIR}/src/timerisr.o.err 
	@${RM} ${OBJECTDIR}/src/timerisr.o 
	@${FIXDEPS} "${OBJECTDIR}/src/timerisr.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"./include" -O3 -fschedule-insns -fschedule-insns2 -MMD -MF "${OBJECTDIR}/src/timerisr.o.d" -o ${OBJECTDIR}/src/timerisr.o src/timerisr.c    -fast-math
	
${OBJECTDIR}/src/uartisr.o: src/uartisr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/uartisr.o.d 
	@${RM} ${OBJECTDIR}/src/uartisr.o.ok ${OBJECTDIR}/src/uartisr.o.err 
	@${RM} ${OBJECTDIR}/src/uartisr.o 
	@${FIXDEPS} "${OBJECTDIR}/src/uartisr.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"./include" -O3 -fschedule-insns -fschedule-insns2 -MMD -MF "${OBJECTDIR}/src/uartisr.o.d" -o ${OBJECTDIR}/src/uartisr.o src/uartisr.c    -fast-math
	
${OBJECTDIR}/src/spi-sw.o: src/spi-sw.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/spi-sw.o.d 
	@${RM} ${OBJECTDIR}/src/spi-sw.o.ok ${OBJECTDIR}/src/spi-sw.o.err 
	@${RM} ${OBJECTDIR}/src/spi-sw.o 
	@${FIXDEPS} "${OBJECTDIR}/src/spi-sw.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"./include" -O3 -fschedule-insns -fschedule-insns2 -MMD -MF "${OBJECTDIR}/src/spi-sw.o.d" -o ${OBJECTDIR}/src/spi-sw.o src/spi-sw.c    -fast-math
	
${OBJECTDIR}/src/i2c-sw.o: src/i2c-sw.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/i2c-sw.o.d 
	@${RM} ${OBJECTDIR}/src/i2c-sw.o.ok ${OBJECTDIR}/src/i2c-sw.o.err 
	@${RM} ${OBJECTDIR}/src/i2c-sw.o 
	@${FIXDEPS} "${OBJECTDIR}/src/i2c-sw.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"./include" -O3 -fschedule-insns -fschedule-insns2 -MMD -MF "${OBJECTDIR}/src/i2c-sw.o.d" -o ${OBJECTDIR}/src/i2c-sw.o src/i2c-sw.c    -fast-math
	
${OBJECTDIR}/src/spi-dev.o: src/spi-dev.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/spi-dev.o.d 
	@${RM} ${OBJECTDIR}/src/spi-dev.o.ok ${OBJECTDIR}/src/spi-dev.o.err 
	@${RM} ${OBJECTDIR}/src/spi-dev.o 
	@${FIXDEPS} "${OBJECTDIR}/src/spi-dev.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"./include" -O3 -fschedule-insns -fschedule-insns2 -MMD -MF "${OBJECTDIR}/src/spi-dev.o.d" -o ${OBJECTDIR}/src/spi-dev.o src/spi-dev.c    -fast-math
	
${OBJECTDIR}/src/i2c-dev.o: src/i2c-dev.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/i2c-dev.o.d 
	@${RM} ${OBJECTDIR}/src/i2c-dev.o.ok ${OBJECTDIR}/src/i2c-dev.o.err 
	@${RM} ${OBJECTDIR}/src/i2c-dev.o 
	@${FIXDEPS} "${OBJECTDIR}/src/i2c-dev.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"./include" -O3 -fschedule-insns -fschedule-insns2 -MMD -MF "${OBJECTDIR}/src/i2c-dev.o.d" -o ${OBJECTDIR}/src/i2c-dev.o src/i2c-dev.c    -fast-math
	
${OBJECTDIR}/src/mmc.o: src/mmc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/mmc.o.d 
	@${RM} ${OBJECTDIR}/src/mmc.o.ok ${OBJECTDIR}/src/mmc.o.err 
	@${RM} ${OBJECTDIR}/src/mmc.o 
	@${FIXDEPS} "${OBJECTDIR}/src/mmc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"./include" -O3 -fschedule-insns -fschedule-insns2 -MMD -MF "${OBJECTDIR}/src/mmc.o.d" -o ${OBJECTDIR}/src/mmc.o src/mmc.c    -fast-math
	
${OBJECTDIR}/src/ff.o: src/ff.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/ff.o.d 
	@${RM} ${OBJECTDIR}/src/ff.o.ok ${OBJECTDIR}/src/ff.o.err 
	@${RM} ${OBJECTDIR}/src/ff.o 
	@${FIXDEPS} "${OBJECTDIR}/src/ff.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"./include" -O3 -fschedule-insns -fschedule-insns2 -MMD -MF "${OBJECTDIR}/src/ff.o.d" -o ${OBJECTDIR}/src/ff.o src/ff.c    -fast-math
	
${OBJECTDIR}/src/ccsbcs.o: src/ccsbcs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/ccsbcs.o.d 
	@${RM} ${OBJECTDIR}/src/ccsbcs.o.ok ${OBJECTDIR}/src/ccsbcs.o.err 
	@${RM} ${OBJECTDIR}/src/ccsbcs.o 
	@${FIXDEPS} "${OBJECTDIR}/src/ccsbcs.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"./include" -O3 -fschedule-insns -fschedule-insns2 -MMD -MF "${OBJECTDIR}/src/ccsbcs.o.d" -o ${OBJECTDIR}/src/ccsbcs.o src/ccsbcs.c    -fast-math
	
${OBJECTDIR}/src/base64.o: src/base64.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/base64.o.d 
	@${RM} ${OBJECTDIR}/src/base64.o.ok ${OBJECTDIR}/src/base64.o.err 
	@${RM} ${OBJECTDIR}/src/base64.o 
	@${FIXDEPS} "${OBJECTDIR}/src/base64.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"./include" -O3 -fschedule-insns -fschedule-insns2 -MMD -MF "${OBJECTDIR}/src/base64.o.d" -o ${OBJECTDIR}/src/base64.o src/base64.c    -fast-math
	
${OBJECTDIR}/src/jt-lenval.o: src/jt-lenval.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/jt-lenval.o.d 
	@${RM} ${OBJECTDIR}/src/jt-lenval.o.ok ${OBJECTDIR}/src/jt-lenval.o.err 
	@${RM} ${OBJECTDIR}/src/jt-lenval.o 
	@${FIXDEPS} "${OBJECTDIR}/src/jt-lenval.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"./include" -O3 -fschedule-insns -fschedule-insns2 -MMD -MF "${OBJECTDIR}/src/jt-lenval.o.d" -o ${OBJECTDIR}/src/jt-lenval.o src/jt-lenval.c    -fast-math
	
${OBJECTDIR}/src/jt-ports.o: src/jt-ports.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/jt-ports.o.d 
	@${RM} ${OBJECTDIR}/src/jt-ports.o.ok ${OBJECTDIR}/src/jt-ports.o.err 
	@${RM} ${OBJECTDIR}/src/jt-ports.o 
	@${FIXDEPS} "${OBJECTDIR}/src/jt-ports.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"./include" -O3 -fschedule-insns -fschedule-insns2 -MMD -MF "${OBJECTDIR}/src/jt-ports.o.d" -o ${OBJECTDIR}/src/jt-ports.o src/jt-ports.c    -fast-math
	
${OBJECTDIR}/src/jt-core.o: src/jt-core.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/jt-core.o.d 
	@${RM} ${OBJECTDIR}/src/jt-core.o.ok ${OBJECTDIR}/src/jt-core.o.err 
	@${RM} ${OBJECTDIR}/src/jt-core.o 
	@${FIXDEPS} "${OBJECTDIR}/src/jt-core.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"./include" -O3 -fschedule-insns -fschedule-insns2 -MMD -MF "${OBJECTDIR}/src/jt-core.o.d" -o ${OBJECTDIR}/src/jt-core.o src/jt-core.c    -fast-math
	
${OBJECTDIR}/src/jt-micro.o: src/jt-micro.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/jt-micro.o.d 
	@${RM} ${OBJECTDIR}/src/jt-micro.o.ok ${OBJECTDIR}/src/jt-micro.o.err 
	@${RM} ${OBJECTDIR}/src/jt-micro.o 
	@${FIXDEPS} "${OBJECTDIR}/src/jt-micro.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"./include" -O3 -fschedule-insns -fschedule-insns2 -MMD -MF "${OBJECTDIR}/src/jt-micro.o.d" -o ${OBJECTDIR}/src/jt-micro.o src/jt-micro.c    -fast-math
	
${OBJECTDIR}/src/fpga.o: src/fpga.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/fpga.o.d 
	@${RM} ${OBJECTDIR}/src/fpga.o.ok ${OBJECTDIR}/src/fpga.o.err 
	@${RM} ${OBJECTDIR}/src/fpga.o 
	@${FIXDEPS} "${OBJECTDIR}/src/fpga.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"./include" -O3 -fschedule-insns -fschedule-insns2 -MMD -MF "${OBJECTDIR}/src/fpga.o.d" -o ${OBJECTDIR}/src/fpga.o src/fpga.c    -fast-math
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/BlockCard-SSC.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -omf=elf -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -o dist/${CND_CONF}/${IMAGE_TYPE}/BlockCard-SSC.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}        -fast-math -Wl,--defsym=__MPLAB_BUILD=1,--heap=2048,--stack=2048$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PICKIT2=1
else
dist/${CND_CONF}/${IMAGE_TYPE}/BlockCard-SSC.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -omf=elf -mcpu=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/BlockCard-SSC.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}        -fast-math -Wl,--defsym=__MPLAB_BUILD=1,--heap=2048,--stack=2048$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION)
	${MP_CC_DIR}/pic30-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/BlockCard-SSC.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -omf=elf
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell "${PATH_TO_IDE_BIN}"mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
