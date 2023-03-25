
;CodeVisionAVR C Compiler V2.03.9 Standard
;(C) Copyright 1998-2008 Pavel Haiduc, HP InfoTech s.r.l.
;http://www.hpinfotech.com

;Chip type              : ATmega644
;Program type           : Application
;Clock frequency        : 11.059200 MHz
;Memory model           : Small
;Optimize for           : Size
;(s)printf features     : float, width, precision
;(s)scanf features      : int, width
;External RAM size      : 0
;Data Stack size        : 1024 byte(s)
;Heap size              : 0 byte(s)
;Promote char to int    : Yes
;char is unsigned       : Yes
;global const stored in FLASH  : No
;8 bit enums            : Yes
;Enhanced core instructions    : On
;Smart register allocation : On
;Automatic register allocation : On

	#pragma AVRPART ADMIN PART_NAME ATmega644
	#pragma AVRPART MEMORY PROG_FLASH 65536
	#pragma AVRPART MEMORY EEPROM 2048
	#pragma AVRPART MEMORY INT_SRAM SIZE 4096
	#pragma AVRPART MEMORY INT_SRAM START_ADDR 0x100

	.LISTMAC
	.EQU EERE=0x0
	.EQU EEWE=0x1
	.EQU EEMWE=0x2
	.EQU UDRE=0x5
	.EQU RXC=0x7
	.EQU EECR=0x1F
	.EQU EEDR=0x20
	.EQU EEARL=0x21
	.EQU EEARH=0x22
	.EQU SPSR0=0x2D
	.EQU SPDR0=0x2E
	.EQU SMCR=0x33
	.EQU MCUSR=0x34
	.EQU MCUCR=0x35
	.EQU WDTCSR=0x60
	.EQU UCSR0A=0xC0
	.EQU UDR0=0xC6
	.EQU SPL=0x3D
	.EQU SPH=0x3E
	.EQU SREG=0x3F
	.EQU GPIOR0=0x1E

	.DEF R0X0=R0
	.DEF R0X1=R1
	.DEF R0X2=R2
	.DEF R0X3=R3
	.DEF R0X4=R4
	.DEF R0X5=R5
	.DEF R0X6=R6
	.DEF R0X7=R7
	.DEF R0X8=R8
	.DEF R0X9=R9
	.DEF R0XA=R10
	.DEF R0XB=R11
	.DEF R0XC=R12
	.DEF R0XD=R13
	.DEF R0XE=R14
	.DEF R0XF=R15
	.DEF R0X10=R16
	.DEF R0X11=R17
	.DEF R0X12=R18
	.DEF R0X13=R19
	.DEF R0X14=R20
	.DEF R0X15=R21
	.DEF R0X16=R22
	.DEF R0X17=R23
	.DEF R0X18=R24
	.DEF R0X19=R25
	.DEF R0X1A=R26
	.DEF R0X1B=R27
	.DEF R0X1C=R28
	.DEF R0X1D=R29
	.DEF R0X1E=R30
	.DEF R0X1F=R31

	.MACRO __CPD1N
	CPI  R30,LOW(@0)
	LDI  R26,HIGH(@0)
	CPC  R31,R26
	LDI  R26,BYTE3(@0)
	CPC  R22,R26
	LDI  R26,BYTE4(@0)
	CPC  R23,R26
	.ENDM

	.MACRO __CPD2N
	CPI  R26,LOW(@0)
	LDI  R30,HIGH(@0)
	CPC  R27,R30
	LDI  R30,BYTE3(@0)
	CPC  R24,R30
	LDI  R30,BYTE4(@0)
	CPC  R25,R30
	.ENDM

	.MACRO __CPWRR
	CP   R@0,R@2
	CPC  R@1,R@3
	.ENDM

	.MACRO __CPWRN
	CPI  R@0,LOW(@2)
	LDI  R30,HIGH(@2)
	CPC  R@1,R30
	.ENDM

	.MACRO __ADDB1MN
	SUBI R30,LOW(-@0-(@1))
	.ENDM

	.MACRO __ADDB2MN
	SUBI R26,LOW(-@0-(@1))
	.ENDM

	.MACRO __ADDW1MN
	SUBI R30,LOW(-@0-(@1))
	SBCI R31,HIGH(-@0-(@1))
	.ENDM

	.MACRO __ADDW2MN
	SUBI R26,LOW(-@0-(@1))
	SBCI R27,HIGH(-@0-(@1))
	.ENDM

	.MACRO __ADDW1FN
	SUBI R30,LOW(-2*@0-(@1))
	SBCI R31,HIGH(-2*@0-(@1))
	.ENDM

	.MACRO __ADDD1FN
	SUBI R30,LOW(-2*@0-(@1))
	SBCI R31,HIGH(-2*@0-(@1))
	SBCI R22,BYTE3(-2*@0-(@1))
	.ENDM

	.MACRO __ADDD1N
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	SBCI R22,BYTE3(-@0)
	SBCI R23,BYTE4(-@0)
	.ENDM

	.MACRO __ADDD2N
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	SBCI R24,BYTE3(-@0)
	SBCI R25,BYTE4(-@0)
	.ENDM

	.MACRO __SUBD1N
	SUBI R30,LOW(@0)
	SBCI R31,HIGH(@0)
	SBCI R22,BYTE3(@0)
	SBCI R23,BYTE4(@0)
	.ENDM

	.MACRO __SUBD2N
	SUBI R26,LOW(@0)
	SBCI R27,HIGH(@0)
	SBCI R24,BYTE3(@0)
	SBCI R25,BYTE4(@0)
	.ENDM

	.MACRO __ANDBMNN
	LDS  R30,@0+@1
	ANDI R30,LOW(@2)
	STS  @0+@1,R30
	.ENDM

	.MACRO __ANDWMNN
	LDS  R30,@0+@1
	ANDI R30,LOW(@2)
	STS  @0+@1,R30
	LDS  R30,@0+@1+1
	ANDI R30,HIGH(@2)
	STS  @0+@1+1,R30
	.ENDM

	.MACRO __ANDD1N
	ANDI R30,LOW(@0)
	ANDI R31,HIGH(@0)
	ANDI R22,BYTE3(@0)
	ANDI R23,BYTE4(@0)
	.ENDM

	.MACRO __ANDD2N
	ANDI R26,LOW(@0)
	ANDI R27,HIGH(@0)
	ANDI R24,BYTE3(@0)
	ANDI R25,BYTE4(@0)
	.ENDM

	.MACRO __ORBMNN
	LDS  R30,@0+@1
	ORI  R30,LOW(@2)
	STS  @0+@1,R30
	.ENDM

	.MACRO __ORWMNN
	LDS  R30,@0+@1
	ORI  R30,LOW(@2)
	STS  @0+@1,R30
	LDS  R30,@0+@1+1
	ORI  R30,HIGH(@2)
	STS  @0+@1+1,R30
	.ENDM

	.MACRO __ORD1N
	ORI  R30,LOW(@0)
	ORI  R31,HIGH(@0)
	ORI  R22,BYTE3(@0)
	ORI  R23,BYTE4(@0)
	.ENDM

	.MACRO __ORD2N
	ORI  R26,LOW(@0)
	ORI  R27,HIGH(@0)
	ORI  R24,BYTE3(@0)
	ORI  R25,BYTE4(@0)
	.ENDM

	.MACRO __DELAY_USB
	LDI  R24,LOW(@0)
__DELAY_USB_LOOP:
	DEC  R24
	BRNE __DELAY_USB_LOOP
	.ENDM

	.MACRO __DELAY_USW
	LDI  R24,LOW(@0)
	LDI  R25,HIGH(@0)
__DELAY_USW_LOOP:
	SBIW R24,1
	BRNE __DELAY_USW_LOOP
	.ENDM

	.MACRO __GETD1S
	LDD  R30,Y+@0
	LDD  R31,Y+@0+1
	LDD  R22,Y+@0+2
	LDD  R23,Y+@0+3
	.ENDM

	.MACRO __PUTD1S
	STD  Y+@0,R30
	STD  Y+@0+1,R31
	STD  Y+@0+2,R22
	STD  Y+@0+3,R23
	.ENDM

	.MACRO __PUTD2S
	STD  Y+@0,R26
	STD  Y+@0+1,R27
	STD  Y+@0+2,R24
	STD  Y+@0+3,R25
	.ENDM

	.MACRO __POINTB1MN
	LDI  R30,LOW(@0+@1)
	.ENDM

	.MACRO __POINTW1MN
	LDI  R30,LOW(@0+@1)
	LDI  R31,HIGH(@0+@1)
	.ENDM

	.MACRO __POINTD1M
	LDI  R30,LOW(@0)
	LDI  R31,HIGH(@0)
	LDI  R22,BYTE3(@0)
	LDI  R23,BYTE4(@0)
	.ENDM

	.MACRO __POINTW1FN
	LDI  R30,LOW(2*@0+@1)
	LDI  R31,HIGH(2*@0+@1)
	.ENDM

	.MACRO __POINTD1FN
	LDI  R30,LOW(2*@0+@1)
	LDI  R31,HIGH(2*@0+@1)
	LDI  R22,BYTE3(2*@0+@1)
	LDI  R23,BYTE4(2*@0+@1)
	.ENDM

	.MACRO __POINTB2MN
	LDI  R26,LOW(@0+@1)
	.ENDM

	.MACRO __POINTW2MN
	LDI  R26,LOW(@0+@1)
	LDI  R27,HIGH(@0+@1)
	.ENDM

	.MACRO __POINTBRM
	LDI  R@0,LOW(@1)
	.ENDM

	.MACRO __POINTWRM
	LDI  R@0,LOW(@2)
	LDI  R@1,HIGH(@2)
	.ENDM

	.MACRO __POINTBRMN
	LDI  R@0,LOW(@1+@2)
	.ENDM

	.MACRO __POINTWRMN
	LDI  R@0,LOW(@2+@3)
	LDI  R@1,HIGH(@2+@3)
	.ENDM

	.MACRO __POINTWRFN
	LDI  R@0,LOW(@2*2+@3)
	LDI  R@1,HIGH(@2*2+@3)
	.ENDM

	.MACRO __GETD1N
	LDI  R30,LOW(@0)
	LDI  R31,HIGH(@0)
	LDI  R22,BYTE3(@0)
	LDI  R23,BYTE4(@0)
	.ENDM

	.MACRO __GETD2N
	LDI  R26,LOW(@0)
	LDI  R27,HIGH(@0)
	LDI  R24,BYTE3(@0)
	LDI  R25,BYTE4(@0)
	.ENDM

	.MACRO __GETD2S
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	LDD  R24,Y+@0+2
	LDD  R25,Y+@0+3
	.ENDM

	.MACRO __GETB1MN
	LDS  R30,@0+@1
	.ENDM

	.MACRO __GETB1HMN
	LDS  R31,@0+@1
	.ENDM

	.MACRO __GETW1MN
	LDS  R30,@0+@1
	LDS  R31,@0+@1+1
	.ENDM

	.MACRO __GETD1MN
	LDS  R30,@0+@1
	LDS  R31,@0+@1+1
	LDS  R22,@0+@1+2
	LDS  R23,@0+@1+3
	.ENDM

	.MACRO __GETBRMN
	LDS  R@0,@1+@2
	.ENDM

	.MACRO __GETWRMN
	LDS  R@0,@2+@3
	LDS  R@1,@2+@3+1
	.ENDM

	.MACRO __GETWRZ
	LDD  R@0,Z+@2
	LDD  R@1,Z+@2+1
	.ENDM

	.MACRO __GETD2Z
	LDD  R26,Z+@0
	LDD  R27,Z+@0+1
	LDD  R24,Z+@0+2
	LDD  R25,Z+@0+3
	.ENDM

	.MACRO __GETB2MN
	LDS  R26,@0+@1
	.ENDM

	.MACRO __GETW2MN
	LDS  R26,@0+@1
	LDS  R27,@0+@1+1
	.ENDM

	.MACRO __GETD2MN
	LDS  R26,@0+@1
	LDS  R27,@0+@1+1
	LDS  R24,@0+@1+2
	LDS  R25,@0+@1+3
	.ENDM

	.MACRO __PUTB1MN
	STS  @0+@1,R30
	.ENDM

	.MACRO __PUTW1MN
	STS  @0+@1,R30
	STS  @0+@1+1,R31
	.ENDM

	.MACRO __PUTD1MN
	STS  @0+@1,R30
	STS  @0+@1+1,R31
	STS  @0+@1+2,R22
	STS  @0+@1+3,R23
	.ENDM

	.MACRO __PUTB1EN
	LDI  R26,LOW(@0+@1)
	LDI  R27,HIGH(@0+@1)
	CALL __EEPROMWRB
	.ENDM

	.MACRO __PUTW1EN
	LDI  R26,LOW(@0+@1)
	LDI  R27,HIGH(@0+@1)
	CALL __EEPROMWRW
	.ENDM

	.MACRO __PUTD1EN
	LDI  R26,LOW(@0+@1)
	LDI  R27,HIGH(@0+@1)
	CALL __EEPROMWRD
	.ENDM

	.MACRO __PUTBR0MN
	STS  @0+@1,R0
	.ENDM

	.MACRO __PUTDZ2
	STD  Z+@0,R26
	STD  Z+@0+1,R27
	STD  Z+@0+2,R24
	STD  Z+@0+3,R25
	.ENDM

	.MACRO __PUTBMRN
	STS  @0+@1,R@2
	.ENDM

	.MACRO __PUTWMRN
	STS  @0+@1,R@2
	STS  @0+@1+1,R@3
	.ENDM

	.MACRO __PUTBZR
	STD  Z+@1,R@0
	.ENDM

	.MACRO __PUTWZR
	STD  Z+@2,R@0
	STD  Z+@2+1,R@1
	.ENDM

	.MACRO __GETW1R
	MOV  R30,R@0
	MOV  R31,R@1
	.ENDM

	.MACRO __GETW2R
	MOV  R26,R@0
	MOV  R27,R@1
	.ENDM

	.MACRO __GETWRN
	LDI  R@0,LOW(@2)
	LDI  R@1,HIGH(@2)
	.ENDM

	.MACRO __PUTW1R
	MOV  R@0,R30
	MOV  R@1,R31
	.ENDM

	.MACRO __PUTW2R
	MOV  R@0,R26
	MOV  R@1,R27
	.ENDM

	.MACRO __ADDWRN
	SUBI R@0,LOW(-@2)
	SBCI R@1,HIGH(-@2)
	.ENDM

	.MACRO __ADDWRR
	ADD  R@0,R@2
	ADC  R@1,R@3
	.ENDM

	.MACRO __SUBWRN
	SUBI R@0,LOW(@2)
	SBCI R@1,HIGH(@2)
	.ENDM

	.MACRO __SUBWRR
	SUB  R@0,R@2
	SBC  R@1,R@3
	.ENDM

	.MACRO __ANDWRN
	ANDI R@0,LOW(@2)
	ANDI R@1,HIGH(@2)
	.ENDM

	.MACRO __ANDWRR
	AND  R@0,R@2
	AND  R@1,R@3
	.ENDM

	.MACRO __ORWRN
	ORI  R@0,LOW(@2)
	ORI  R@1,HIGH(@2)
	.ENDM

	.MACRO __ORWRR
	OR   R@0,R@2
	OR   R@1,R@3
	.ENDM

	.MACRO __EORWRR
	EOR  R@0,R@2
	EOR  R@1,R@3
	.ENDM

	.MACRO __GETWRS
	LDD  R@0,Y+@2
	LDD  R@1,Y+@2+1
	.ENDM

	.MACRO __PUTWSR
	STD  Y+@2,R@0
	STD  Y+@2+1,R@1
	.ENDM

	.MACRO __MOVEWRR
	MOV  R@0,R@2
	MOV  R@1,R@3
	.ENDM

	.MACRO __INWR
	IN   R@0,@2
	IN   R@1,@2+1
	.ENDM

	.MACRO __OUTWR
	OUT  @2+1,R@1
	OUT  @2,R@0
	.ENDM

	.MACRO __CALL1MN
	LDS  R30,@0+@1
	LDS  R31,@0+@1+1
	ICALL
	.ENDM

	.MACRO __CALL1FN
	LDI  R30,LOW(2*@0+@1)
	LDI  R31,HIGH(2*@0+@1)
	CALL __GETW1PF
	ICALL
	.ENDM

	.MACRO __CALL2EN
	LDI  R26,LOW(@0+@1)
	LDI  R27,HIGH(@0+@1)
	CALL __EEPROMRDW
	ICALL
	.ENDM

	.MACRO __GETW1STACK
	IN   R26,SPL
	IN   R27,SPH
	ADIW R26,@0+1
	LD   R30,X+
	LD   R31,X
	.ENDM

	.MACRO __NBST
	BST  R@0,@1
	IN   R30,SREG
	LDI  R31,0x40
	EOR  R30,R31
	OUT  SREG,R30
	.ENDM


	.MACRO __PUTB1SN
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X,R30
	.ENDM

	.MACRO __PUTW1SN
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1SN
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	CALL __PUTDP1
	.ENDM

	.MACRO __PUTB1SNS
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	ADIW R26,@1
	ST   X,R30
	.ENDM

	.MACRO __PUTW1SNS
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	ADIW R26,@1
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1SNS
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	ADIW R26,@1
	CALL __PUTDP1
	.ENDM

	.MACRO __PUTB1PMN
	LDS  R26,@0
	LDS  R27,@0+1
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X,R30
	.ENDM

	.MACRO __PUTW1PMN
	LDS  R26,@0
	LDS  R27,@0+1
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1PMN
	LDS  R26,@0
	LDS  R27,@0+1
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	CALL __PUTDP1
	.ENDM

	.MACRO __PUTB1PMNS
	LDS  R26,@0
	LDS  R27,@0+1
	ADIW R26,@1
	ST   X,R30
	.ENDM

	.MACRO __PUTW1PMNS
	LDS  R26,@0
	LDS  R27,@0+1
	ADIW R26,@1
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1PMNS
	LDS  R26,@0
	LDS  R27,@0+1
	ADIW R26,@1
	CALL __PUTDP1
	.ENDM

	.MACRO __PUTB1RN
	MOVW R26,R@0
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X,R30
	.ENDM

	.MACRO __PUTW1RN
	MOVW R26,R@0
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1RN
	MOVW R26,R@0
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	CALL __PUTDP1
	.ENDM

	.MACRO __PUTB1RNS
	MOVW R26,R@0
	ADIW R26,@1
	ST   X,R30
	.ENDM

	.MACRO __PUTW1RNS
	MOVW R26,R@0
	ADIW R26,@1
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1RNS
	MOVW R26,R@0
	ADIW R26,@1
	CALL __PUTDP1
	.ENDM

	.MACRO __PUTB1RON
	MOV  R26,R@0
	MOV  R27,R@1
	SUBI R26,LOW(-@2)
	SBCI R27,HIGH(-@2)
	ST   X,R30
	.ENDM

	.MACRO __PUTW1RON
	MOV  R26,R@0
	MOV  R27,R@1
	SUBI R26,LOW(-@2)
	SBCI R27,HIGH(-@2)
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1RON
	MOV  R26,R@0
	MOV  R27,R@1
	SUBI R26,LOW(-@2)
	SBCI R27,HIGH(-@2)
	CALL __PUTDP1
	.ENDM

	.MACRO __PUTB1RONS
	MOV  R26,R@0
	MOV  R27,R@1
	ADIW R26,@2
	ST   X,R30
	.ENDM

	.MACRO __PUTW1RONS
	MOV  R26,R@0
	MOV  R27,R@1
	ADIW R26,@2
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1RONS
	MOV  R26,R@0
	MOV  R27,R@1
	ADIW R26,@2
	CALL __PUTDP1
	.ENDM


	.MACRO __GETB1SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	LD   R30,Z
	.ENDM

	.MACRO __GETB1HSX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	LD   R31,Z
	.ENDM

	.MACRO __GETW1SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	LD   R0,Z+
	LD   R31,Z
	MOV  R30,R0
	.ENDM

	.MACRO __GETD1SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	LD   R0,Z+
	LD   R1,Z+
	LD   R22,Z+
	LD   R23,Z
	MOVW R30,R0
	.ENDM

	.MACRO __GETB2SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	LD   R26,X
	.ENDM

	.MACRO __GETW2SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	LD   R0,X+
	LD   R27,X
	MOV  R26,R0
	.ENDM

	.MACRO __GETD2SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	LD   R0,X+
	LD   R1,X+
	LD   R24,X+
	LD   R25,X
	MOVW R26,R0
	.ENDM

	.MACRO __GETBRSX
	MOVW R30,R28
	SUBI R30,LOW(-@1)
	SBCI R31,HIGH(-@1)
	LD   R@0,Z
	.ENDM

	.MACRO __GETWRSX
	MOVW R30,R28
	SUBI R30,LOW(-@2)
	SBCI R31,HIGH(-@2)
	LD   R@0,Z+
	LD   R@1,Z
	.ENDM

	.MACRO __LSLW8SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	LD   R31,Z
	CLR  R30
	.ENDM

	.MACRO __PUTB1SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	ST   X,R30
	.ENDM

	.MACRO __PUTW1SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	ST   X+,R30
	ST   X+,R31
	ST   X+,R22
	ST   X,R23
	.ENDM

	.MACRO __CLRW1SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	ST   X+,R30
	ST   X,R30
	.ENDM

	.MACRO __CLRD1SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	ST   X+,R30
	ST   X+,R30
	ST   X+,R30
	ST   X,R30
	.ENDM

	.MACRO __PUTB2SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	ST   Z,R26
	.ENDM

	.MACRO __PUTW2SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	ST   Z+,R26
	ST   Z,R27
	.ENDM

	.MACRO __PUTD2SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	ST   Z+,R26
	ST   Z+,R27
	ST   Z+,R24
	ST   Z,R25
	.ENDM

	.MACRO __PUTBSRX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	ST   Z,R@1
	.ENDM

	.MACRO __PUTWSRX
	MOVW R30,R28
	SUBI R30,LOW(-@2)
	SBCI R31,HIGH(-@2)
	ST   Z+,R@0
	ST   Z,R@1
	.ENDM

	.MACRO __PUTB1SNX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	LD   R0,X+
	LD   R27,X
	MOV  R26,R0
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X,R30
	.ENDM

	.MACRO __PUTW1SNX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	LD   R0,X+
	LD   R27,X
	MOV  R26,R0
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1SNX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	LD   R0,X+
	LD   R27,X
	MOV  R26,R0
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X+,R30
	ST   X+,R31
	ST   X+,R22
	ST   X,R23
	.ENDM

	.MACRO __MULBRR
	MULS R@0,R@1
	MOVW R30,R0
	.ENDM

	.MACRO __MULBRRU
	MUL  R@0,R@1
	MOVW R30,R0
	.ENDM

	.MACRO __MULBRR0
	MULS R@0,R@1
	.ENDM

	.MACRO __MULBRRU0
	MUL  R@0,R@1
	.ENDM

	.MACRO __MULBNWRU
	LDI  R26,@2
	MUL  R26,R@0
	MOVW R30,R0
	MUL  R26,R@1
	ADD  R31,R0
	.ENDM

;NAME DEFINITIONS FOR GLOBAL VARIABLES ALLOCATED TO REGISTERS
	.DEF _rx_wr_index0=R4
	.DEF _rx_rd_index0=R3
	.DEF _rx_counter0=R6
	.DEF _flag=R7
	.DEF _tanda_r=R9
	.DEF _tanda_g=R11
	.DEF _kuadran=R13
	.DEF _RIndex=R5

	.CSEG
	.ORG 0x00

;INTERRUPT VECTORS
	JMP  __RESET
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  _timer0_ovf_isr
	JMP  0x00
	JMP  _usart_rx_isr
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00

;GPIOR0 INITIALIZATION
	.EQU  __GPIOR0_INIT=0x00

_0x3:
	.DB  0x1
_0x4:
	.DB  0x2E
_0xF9:
	.DB  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0
_0x2000000:
	.DB  0x2D,0x4E,0x41,0x4E,0x0
_0x2040003:
	.DB  0x80,0xC0
_0x20A005F:
	.DB  0x1
_0x20A0000:
	.DB  0x2D,0x4E,0x41,0x4E,0x0

__GLOBAL_INI_TBL:
	.DW  0x01
	.DW  _Kp
	.DW  _0x3*2

	.DW  0x01
	.DW  _Kd
	.DW  _0x4*2

	.DW  0x08
	.DW  0x07
	.DW  _0xF9*2

	.DW  0x02
	.DW  __base_y_G102
	.DW  _0x2040003*2

	.DW  0x01
	.DW  __seed_G105
	.DW  _0x20A005F*2

_0xFFFFFFFF:
	.DW  0

__RESET:
	CLI
	CLR  R30
	OUT  EECR,R30

;INTERRUPT VECTORS ARE PLACED
;AT THE START OF FLASH
	LDI  R31,1
	OUT  MCUCR,R31
	OUT  MCUCR,R30

;DISABLE WATCHDOG
	LDI  R31,0x18
	WDR
	IN   R26,MCUSR
	CBR  R26,8
	OUT  MCUSR,R26
	STS  WDTCSR,R31
	STS  WDTCSR,R30

;CLEAR R2-R14
	LDI  R24,(14-2)+1
	LDI  R26,2
	CLR  R27
__CLEAR_REG:
	ST   X+,R30
	DEC  R24
	BRNE __CLEAR_REG

;CLEAR SRAM
	LDI  R24,LOW(0x1000)
	LDI  R25,HIGH(0x1000)
	LDI  R26,LOW(0x100)
	LDI  R27,HIGH(0x100)
__CLEAR_SRAM:
	ST   X+,R30
	SBIW R24,1
	BRNE __CLEAR_SRAM

;GLOBAL VARIABLES INITIALIZATION
	LDI  R30,LOW(__GLOBAL_INI_TBL*2)
	LDI  R31,HIGH(__GLOBAL_INI_TBL*2)
__GLOBAL_INI_NEXT:
	LPM  R24,Z+
	LPM  R25,Z+
	SBIW R24,0
	BREQ __GLOBAL_INI_END
	LPM  R26,Z+
	LPM  R27,Z+
	LPM  R0,Z+
	LPM  R1,Z+
	MOVW R22,R30
	MOVW R30,R0
__GLOBAL_INI_LOOP:
	LPM  R0,Z+
	ST   X+,R0
	SBIW R24,1
	BRNE __GLOBAL_INI_LOOP
	MOVW R30,R22
	RJMP __GLOBAL_INI_NEXT
__GLOBAL_INI_END:

;GPIOR0 INITIALIZATION
	LDI  R30,__GPIOR0_INIT
	OUT  GPIOR0,R30

;STACK POINTER INITIALIZATION
	LDI  R30,LOW(0x10FF)
	OUT  SPL,R30
	LDI  R30,HIGH(0x10FF)
	OUT  SPH,R30

;DATA STACK POINTER INITIALIZATION
	LDI  R28,LOW(0x500)
	LDI  R29,HIGH(0x500)

	JMP  _main

	.ESEG
	.ORG 0

	.DSEG
	.ORG 0x500

	.CSEG
;/*****************************************************
;This program was produced by the
;CodeWizardAVR V2.03.9 Standard
;Automatic Program Generator
;© Copyright 1998-2008 Pavel Haiduc, HP InfoTech s.r.l.
;http://www.hpinfotech.com
;
;Project :
;Version :
;Date    : 4/17/2013
;Author  : CarokArmy
;Company : CarokCompany.Inc
;Comments:
;
;
;Chip type               : ATmega644
;Program type            : Application
;AVR Core Clock frequency: 11.059200 MHz
;Memory model            : Small
;External RAM size       : 0
;Data Stack size         : 1024
;*****************************************************/
;
;#include <mega644.h>
	#ifndef __SLEEP_DEFINED__
	#define __SLEEP_DEFINED__
	.EQU __se_bit=0x01
	.EQU __sm_mask=0x0E
	.EQU __sm_powerdown=0x04
	.EQU __sm_powersave=0x06
	.EQU __sm_standby=0x0C
	.EQU __sm_ext_standby=0x0E
	.EQU __sm_adc_noise_red=0x02
	.SET power_ctrl_reg=smcr
	#endif
;#include <stdio.h>
;#include <delay.h>
;
;#include <math.h>
;
;#define en1 PORTD.5
;#define cw1 PORTD.6
;#define ccw1 PORTD.7
;
;
;#define en2 PORTD.2
;#define cw2 PORTD.3
;#define ccw2 PORTD.4
;
;#define en4 PORTB.5
;#define ccw4 PORTB.6
;#define cw4 PORTB.7
;
;
;#define en3 PORTB.4
;#define cw3 PORTB.3
;#define ccw3 PORTB.2
;
;#define en5 PORTB.1
;#define sol PORTB.0
;
;#define sw PINC.0
;#define push PINC.1
;
;// Alphanumeric LCD Module functions
;#asm
   .equ __lcd_port=0x02 ;PORTA
; 0000 0039 #endasm
;#include <lcd.h>
;
;#define RXB8 1
;#define TXB8 0
;#define UPE 2
;#define OVR 3
;#define FE 4
;#define UDRE 5
;#define RXC 7
;
;#define FRAMING_ERROR (1<<FE)
;#define PARITY_ERROR (1<<UPE)
;#define DATA_OVERRUN (1<<OVR)
;#define DATA_REGISTER_EMPTY (1<<UDRE)
;#define RX_COMPLETE (1<<RXC)
;
;// USART Receiver buffer
;#define RX_BUFFER_SIZE0 8
;char rx_buffer0[RX_BUFFER_SIZE0];
;
;#if RX_BUFFER_SIZE0<256
;unsigned char rx_wr_index0,rx_rd_index0,rx_counter0;
;#else
;unsigned int rx_wr_index0,rx_rd_index0,rx_counter0;
;#endif
;
;// This flag is set on USART Receiver buffer overflow
;bit rx_buffer_overflow0;
;
;
;static int sr,sg, sk;
;int flag=0;
;static int s_rt, s_gt, s_rg, s_gr, s_rk, s_gk, s_ok;
;static int m_rt, m_gt, m_rg, m_gr, m_rk, m_gk, m_ok;
;
;int tanda_r, tanda_g;
;
;int kuadran=0;
;
;float Fa,Fb,Fc,Fd;
;int Vel;
;
;float er=0,der,P,D;
;static signed int laster;
;signed int m;
;int Kp=1;

	.DSEG
;int Kd=46;
;
;unsigned char buffer[128];
;
;char sData[8];
;char RIndex;
;
;unsigned int KonversiDataSerial()
; 0000 0070 {

	.CSEG
_KonversiDataSerial:
; 0000 0071     unsigned int Hasil=0;
; 0000 0072     Hasil = (sData[1]-48) *100;
	ST   -Y,R17
	ST   -Y,R16
;	Hasil -> R16,R17
	__GETWRN 16,17,0
	__GETB1MN _sData,1
	CALL SUBOPT_0x0
	LDI  R26,LOW(100)
	LDI  R27,HIGH(100)
	CALL __MULW12
	MOVW R16,R30
; 0000 0073     Hasil += (sData[2]-48) *10;
	__GETB1MN _sData,2
	CALL SUBOPT_0x0
	CALL SUBOPT_0x1
; 0000 0074     Hasil += sData[3]-48;
	__GETB1MN _sData,3
	RJMP _0x20C0003
; 0000 0075 
; 0000 0076     return Hasil;
; 0000 0077 }
;
;unsigned int KonversiDataSerial2()
; 0000 007A {
_KonversiDataSerial2:
; 0000 007B     unsigned int Hasil=0;
; 0000 007C     Hasil = (sData[5]-48) *100;
	ST   -Y,R17
	ST   -Y,R16
;	Hasil -> R16,R17
	__GETWRN 16,17,0
	__GETB1MN _sData,5
	CALL SUBOPT_0x0
	LDI  R26,LOW(100)
	LDI  R27,HIGH(100)
	CALL __MULW12
	MOVW R16,R30
; 0000 007D     Hasil += (sData[6]-48) *10;
	__GETB1MN _sData,6
	CALL SUBOPT_0x0
	CALL SUBOPT_0x1
; 0000 007E     Hasil += sData[7]-48;
	__GETB1MN _sData,7
_0x20C0003:
	LDI  R31,0
	SBIW R30,48
	__ADDWRR 16,17,30,31
; 0000 007F 
; 0000 0080     return Hasil;
	MOVW R30,R16
	LD   R16,Y+
	LD   R17,Y+
	RET
; 0000 0081 }
;
;// USART Receiver interrupt service routine
;interrupt [USART_RXC] void usart_rx_isr(void)
; 0000 0085 {
_usart_rx_isr:
	ST   -Y,R0
	ST   -Y,R1
	ST   -Y,R15
	ST   -Y,R22
	ST   -Y,R23
	ST   -Y,R24
	ST   -Y,R25
	ST   -Y,R26
	ST   -Y,R27
	ST   -Y,R30
	ST   -Y,R31
	IN   R30,SREG
	ST   -Y,R30
; 0000 0086 char status,data;
; 0000 0087 status=UCSR0A;
	ST   -Y,R17
	ST   -Y,R16
;	status -> R17
;	data -> R16
	LDS  R17,192
; 0000 0088 data=UDR0;
	LDS  R16,198
; 0000 0089 if ((status & (FRAMING_ERROR | PARITY_ERROR | DATA_OVERRUN))==0)
	MOV  R30,R17
	ANDI R30,LOW(0x1C)
	BREQ PC+3
	JMP _0x5
; 0000 008A    {
; 0000 008B    if (data == 'R' ||data == 'G' ||data == 'r' ||data == 'g' ||data == '!' ||data == 'K' ||data == 'k' || data == '@' || data == 'o' || data == 'z' )
	CPI  R16,82
	BREQ _0x7
	CPI  R16,71
	BREQ _0x7
	CPI  R16,114
	BREQ _0x7
	CPI  R16,103
	BREQ _0x7
	CPI  R16,33
	BREQ _0x7
	CPI  R16,75
	BREQ _0x7
	CPI  R16,107
	BREQ _0x7
	CPI  R16,64
	BREQ _0x7
	CPI  R16,111
	BREQ _0x7
	CPI  R16,122
	BRNE _0x6
_0x7:
; 0000 008C     {
; 0000 008D         sData[0]=data;
	STS  _sData,R16
; 0000 008E         RIndex = 1;
	LDI  R30,LOW(1)
	MOV  R5,R30
; 0000 008F     }
; 0000 0090 
; 0000 0091     else if (data == 13)
	RJMP _0x9
_0x6:
	CPI  R16,13
	BREQ PC+3
	JMP _0xA
; 0000 0092     {   //cek isi dari header
; 0000 0093         switch (sData[0])
	LDS  R30,_sData
	LDI  R31,0
; 0000 0094         {
; 0000 0095            case 'R':  s_rt = KonversiDataSerial();
	CPI  R30,LOW(0x52)
	LDI  R26,HIGH(0x52)
	CPC  R31,R26
	BRNE _0xE
	RCALL _KonversiDataSerial
	STS  _s_rt_G000,R30
	STS  _s_rt_G000+1,R31
; 0000 0096                       m_rt = KonversiDataSerial2();  flag=0; break;
	RCALL _KonversiDataSerial2
	STS  _m_rt_G000,R30
	STS  _m_rt_G000+1,R31
	CLR  R7
	CLR  R8
	RJMP _0xD
; 0000 0097            case 'G':  s_gt = KonversiDataSerial();
_0xE:
	CPI  R30,LOW(0x47)
	LDI  R26,HIGH(0x47)
	CPC  R31,R26
	BRNE _0xF
	RCALL _KonversiDataSerial
	STS  _s_gt_G000,R30
	STS  _s_gt_G000+1,R31
; 0000 0098                       m_gt = KonversiDataSerial2();  flag=0; break;
	RCALL _KonversiDataSerial2
	STS  _m_gt_G000,R30
	STS  _m_gt_G000+1,R31
	CLR  R7
	CLR  R8
	RJMP _0xD
; 0000 0099            case 'r':  s_rg = KonversiDataSerial();
_0xF:
	CPI  R30,LOW(0x72)
	LDI  R26,HIGH(0x72)
	CPC  R31,R26
	BRNE _0x10
	RCALL _KonversiDataSerial
	STS  _s_rg_G000,R30
	STS  _s_rg_G000+1,R31
; 0000 009A                       m_rg = KonversiDataSerial2();  flag=0; break;
	RCALL _KonversiDataSerial2
	STS  _m_rg_G000,R30
	STS  _m_rg_G000+1,R31
	CLR  R7
	CLR  R8
	RJMP _0xD
; 0000 009B            case 'g':  s_gr = KonversiDataSerial();
_0x10:
	CPI  R30,LOW(0x67)
	LDI  R26,HIGH(0x67)
	CPC  R31,R26
	BRNE _0x11
	RCALL _KonversiDataSerial
	STS  _s_gr_G000,R30
	STS  _s_gr_G000+1,R31
; 0000 009C                       m_gr = KonversiDataSerial2();  flag=0; break;
	RCALL _KonversiDataSerial2
	STS  _m_gr_G000,R30
	STS  _m_gr_G000+1,R31
	CLR  R7
	CLR  R8
	RJMP _0xD
; 0000 009D            case '!':  sr = KonversiDataSerial();
_0x11:
	CPI  R30,LOW(0x21)
	LDI  R26,HIGH(0x21)
	CPC  R31,R26
	BRNE _0x12
	RCALL _KonversiDataSerial
	STS  _sr_G000,R30
	STS  _sr_G000+1,R31
; 0000 009E                       sg = KonversiDataSerial2();   flag=0; break;
	RCALL _KonversiDataSerial2
	STS  _sg_G000,R30
	STS  _sg_G000+1,R31
	CLR  R7
	CLR  R8
	RJMP _0xD
; 0000 009F            case 'K':  s_rk = KonversiDataSerial();
_0x12:
	CPI  R30,LOW(0x4B)
	LDI  R26,HIGH(0x4B)
	CPC  R31,R26
	BRNE _0x13
	RCALL _KonversiDataSerial
	STS  _s_rk_G000,R30
	STS  _s_rk_G000+1,R31
; 0000 00A0                       m_rk = KonversiDataSerial2();   flag=0; break;
	RCALL _KonversiDataSerial2
	STS  _m_rk_G000,R30
	STS  _m_rk_G000+1,R31
	CLR  R7
	CLR  R8
	RJMP _0xD
; 0000 00A1            case 'k':  s_gk = KonversiDataSerial();
_0x13:
	CPI  R30,LOW(0x6B)
	LDI  R26,HIGH(0x6B)
	CPC  R31,R26
	BRNE _0x14
	RCALL _KonversiDataSerial
	STS  _s_gk_G000,R30
	STS  _s_gk_G000+1,R31
; 0000 00A2                       m_gk = KonversiDataSerial2();   flag=0; break;
	RCALL _KonversiDataSerial2
	STS  _m_gk_G000,R30
	STS  _m_gk_G000+1,R31
	CLR  R7
	CLR  R8
	RJMP _0xD
; 0000 00A3            case '@':  s_ok = KonversiDataSerial();
_0x14:
	CPI  R30,LOW(0x40)
	LDI  R26,HIGH(0x40)
	CPC  R31,R26
	BRNE _0x15
	RCALL _KonversiDataSerial
	STS  _s_ok_G000,R30
	STS  _s_ok_G000+1,R31
; 0000 00A4                       m_ok = KonversiDataSerial2();   flag=0; break;
	RCALL _KonversiDataSerial2
	STS  _m_ok_G000,R30
	STS  _m_ok_G000+1,R31
	CLR  R7
	CLR  R8
	RJMP _0xD
; 0000 00A5            case 'z':  tanda_r = KonversiDataSerial();
_0x15:
	CPI  R30,LOW(0x7A)
	LDI  R26,HIGH(0x7A)
	CPC  R31,R26
	BRNE _0x16
	RCALL _KonversiDataSerial
	__PUTW1R 9,10
; 0000 00A6                       tanda_g = KonversiDataSerial2();   flag=0; break;
	RCALL _KonversiDataSerial2
	__PUTW1R 11,12
	CLR  R7
	CLR  R8
	RJMP _0xD
; 0000 00A7            case 'o': flag=1;  break;
_0x16:
	CPI  R30,LOW(0x6F)
	LDI  R26,HIGH(0x6F)
	CPC  R31,R26
	BRNE _0xD
	LDI  R30,LOW(1)
	LDI  R31,HIGH(1)
	__PUTW1R 7,8
; 0000 00A8         }
_0xD:
; 0000 00A9     }
; 0000 00AA     else
	RJMP _0x18
_0xA:
; 0000 00AB     {
; 0000 00AC         sData[RIndex]=data;
	MOV  R30,R5
	LDI  R31,0
	SUBI R30,LOW(-_sData)
	SBCI R31,HIGH(-_sData)
	ST   Z,R16
; 0000 00AD         if(RIndex>8) RIndex=0;
	LDI  R30,LOW(8)
	CP   R30,R5
	BRSH _0x19
	CLR  R5
; 0000 00AE         else RIndex++;
	RJMP _0x1A
_0x19:
	INC  R5
; 0000 00AF     }
_0x1A:
_0x18:
_0x9:
; 0000 00B0 //   rx_buffer0[rx_wr_index0]=data;
; 0000 00B1 //   if (++rx_wr_index0 == RX_BUFFER_SIZE0) rx_wr_index0=0;
; 0000 00B2 //   if (++rx_counter0 == RX_BUFFER_SIZE0)
; 0000 00B3 //      {
; 0000 00B4 //      rx_counter0=0;
; 0000 00B5 //      rx_buffer_overflow0=1;
; 0000 00B6 //      };
; 0000 00B7    };
_0x5:
; 0000 00B8 }
	LD   R16,Y+
	LD   R17,Y+
	LD   R30,Y+
	OUT  SREG,R30
	LD   R31,Y+
	LD   R30,Y+
	LD   R27,Y+
	LD   R26,Y+
	LD   R25,Y+
	LD   R24,Y+
	LD   R23,Y+
	LD   R22,Y+
	LD   R15,Y+
	LD   R1,Y+
	LD   R0,Y+
	RETI
;
;#ifndef _DEBUG_TERMINAL_IO_
;// Get a character from the USART Receiver buffer
;#define _ALTERNATE_GETCHAR_
;#pragma used+
;char getchar(void)
; 0000 00BF {
; 0000 00C0 char data;
; 0000 00C1 while (rx_counter0==0);
;	data -> R17
; 0000 00C2 data=rx_buffer0[rx_rd_index0];
; 0000 00C3 if (++rx_rd_index0 == RX_BUFFER_SIZE0) rx_rd_index0=0;
; 0000 00C4 #asm("cli")
; 0000 00C5 --rx_counter0;
; 0000 00C6 #asm("sei")
; 0000 00C7 return data;
; 0000 00C8 }
;#pragma used-
;#endif
;
;// Standard Input/Output functions
;unsigned int a,pwm1,pwm2,pwm3,pwm4,pwm5;
;unsigned char psol;
;
;// Timer 0 overflow interrupt service routine
;interrupt [TIM0_OVF] void timer0_ovf_isr(void)
; 0000 00D2 {
_timer0_ovf_isr:
	ST   -Y,R26
	ST   -Y,R27
	ST   -Y,R30
	ST   -Y,R31
	IN   R30,SREG
	ST   -Y,R30
; 0000 00D3 // Place your code here
; 0000 00D4    a++;
	LDI  R26,LOW(_a)
	LDI  R27,HIGH(_a)
	LD   R30,X+
	LD   R31,X+
	ADIW R30,1
	ST   -X,R31
	ST   -X,R30
; 0000 00D5 
; 0000 00D6     if(a==255) a=0;
	CALL SUBOPT_0x2
	CPI  R26,LOW(0xFF)
	LDI  R30,HIGH(0xFF)
	CPC  R27,R30
	BRNE _0x1F
	LDI  R30,LOW(0)
	STS  _a,R30
	STS  _a+1,R30
; 0000 00D7     if(a<=pwm1)en1=0;   else en1=1;
_0x1F:
	LDS  R30,_pwm1
	LDS  R31,_pwm1+1
	CALL SUBOPT_0x3
	BRLO _0x20
	CBI  0xB,5
	RJMP _0x23
_0x20:
	SBI  0xB,5
; 0000 00D8     if(a<=pwm2)en2=0;   else en2=1;
_0x23:
	LDS  R30,_pwm2
	LDS  R31,_pwm2+1
	CALL SUBOPT_0x3
	BRLO _0x26
	CBI  0xB,2
	RJMP _0x29
_0x26:
	SBI  0xB,2
; 0000 00D9     if(a<=pwm3)en3=0;   else en3=1;
_0x29:
	LDS  R30,_pwm3
	LDS  R31,_pwm3+1
	CALL SUBOPT_0x3
	BRLO _0x2C
	CBI  0x5,4
	RJMP _0x2F
_0x2C:
	SBI  0x5,4
; 0000 00DA     if(a<=pwm4)en4=0;   else en4=1;
_0x2F:
	LDS  R30,_pwm4
	LDS  R31,_pwm4+1
	CALL SUBOPT_0x3
	BRLO _0x32
	CBI  0x5,5
	RJMP _0x35
_0x32:
	SBI  0x5,5
; 0000 00DB     if(a<=pwm5)en5=0;   else en5=1;
_0x35:
	LDS  R30,_pwm5
	LDS  R31,_pwm5+1
	CALL SUBOPT_0x3
	BRLO _0x38
	CBI  0x5,1
	RJMP _0x3B
_0x38:
	SBI  0x5,1
; 0000 00DC     if(a<=psol)sol=0;   else sol=1;
_0x3B:
	LDS  R30,_psol
	CALL SUBOPT_0x2
	LDI  R31,0
	CP   R30,R26
	CPC  R31,R27
	BRLO _0x3E
	CBI  0x5,0
	RJMP _0x41
_0x3E:
	SBI  0x5,0
; 0000 00DD }
_0x41:
	LD   R30,Y+
	OUT  SREG,R30
	LD   R31,Y+
	LD   R30,Y+
	LD   R27,Y+
	LD   R26,Y+
	RETI
;
;// Declare your global variables here
;unsigned char buf[16];
;
;void stop()
; 0000 00E3 {
_stop:
; 0000 00E4     cw1=0; ccw1=0; cw2=0; ccw2=0;   cw3=0; ccw3=0; cw4=0; ccw4=0;
	CBI  0xB,6
	CBI  0xB,7
	CBI  0xB,3
	CBI  0xB,4
	CBI  0x5,3
	CBI  0x5,2
	CBI  0x5,7
	CBI  0x5,6
; 0000 00E5 }
	RET
;
;void maju(unsigned char v)
; 0000 00E8 {
; 0000 00E9 
; 0000 00EA    pwm1=v*cos(60); cw1=0; ccw1=1;  pwm2=v*cos(60); cw2=1; ccw2=0;
;	v -> Y+0
; 0000 00EB    pwm4=v*cos(45); cw4=0; ccw4=1;  pwm3=v*cos(45); cw3=1; ccw3=0;
; 0000 00EC }
;
;void mundur(unsigned char v)
; 0000 00EF {
_mundur:
; 0000 00F0 
; 0000 00F1    pwm1=v*cos(60); cw1=1; ccw1=0;  pwm2=v*cos(60); cw2=0; ccw2=1;
;	v -> Y+0
	CALL SUBOPT_0x4
	PUSH R31
	PUSH R30
	CALL SUBOPT_0x5
	POP  R26
	POP  R27
	CALL SUBOPT_0x6
	LDI  R26,LOW(_pwm1)
	LDI  R27,HIGH(_pwm1)
	CALL SUBOPT_0x7
	SBI  0xB,6
	CBI  0xB,7
	CALL SUBOPT_0x4
	PUSH R31
	PUSH R30
	CALL SUBOPT_0x5
	POP  R26
	POP  R27
	CALL SUBOPT_0x6
	LDI  R26,LOW(_pwm2)
	LDI  R27,HIGH(_pwm2)
	CALL SUBOPT_0x7
	CBI  0xB,3
	SBI  0xB,4
; 0000 00F2    pwm4=v*cos(45); cw4=1; ccw4=0;  pwm3=v*cos(45); cw3=0; ccw3=1;
	CALL SUBOPT_0x4
	PUSH R31
	PUSH R30
	CALL SUBOPT_0x8
	POP  R26
	POP  R27
	CALL SUBOPT_0x6
	LDI  R26,LOW(_pwm4)
	LDI  R27,HIGH(_pwm4)
	CALL SUBOPT_0x7
	SBI  0x5,7
	CBI  0x5,6
	CALL SUBOPT_0x4
	PUSH R31
	PUSH R30
	CALL SUBOPT_0x8
	POP  R26
	POP  R27
	CALL SUBOPT_0x6
	LDI  R26,LOW(_pwm3)
	LDI  R27,HIGH(_pwm3)
	CALL SUBOPT_0x7
	CBI  0x5,3
	SBI  0x5,2
; 0000 00F3 }
	JMP  _0x20C0001
;
;void kanan(unsigned char v)
; 0000 00F6 {
; 0000 00F7    pwm1=v*cos(30); cw1=1; ccw1=0;  pwm2=v*cos(120); cw2=1; ccw2=0;
;	v -> Y+0
; 0000 00F8    pwm4=v*cos(120); cw4=0; ccw4=1;  pwm3=v*cos(30); cw3=0; ccw3=1;
; 0000 00F9 }
;
;void kiri(unsigned char v)
; 0000 00FC {
; 0000 00FD    pwm1=v*cos(30); cw1=0; ccw1=1;  pwm2=v*cos(120); cw2=0; ccw2=1;
;	v -> Y+0
; 0000 00FE    pwm4=v*cos(120); cw4=1; ccw4=0;  pwm3=v*cos(30); cw3=1; ccw3=0;
; 0000 00FF }
;
;void tendang()
; 0000 0102 {
; 0000 0103    psol=255; delay_ms(20); psol=0;
; 0000 0104 }
;
;
;//------------Kinematik------------
;
;void CW_CCW_motor(float a, float b, float c, float d)
; 0000 010A {
_CW_CCW_motor:
; 0000 010B     if(a<0){ cw1=1; ccw1=0; pwm1=-a; }    else { cw1=0; ccw1=1; pwm1=a; }
;	a -> Y+12
;	b -> Y+8
;	c -> Y+4
;	d -> Y+0
	LDD  R26,Y+15
	TST  R26
	BRPL _0x94
	SBI  0xB,6
	CBI  0xB,7
	CALL SUBOPT_0x9
	CALL __ANEGF1
	RJMP _0xEF
_0x94:
	CBI  0xB,6
	SBI  0xB,7
	CALL SUBOPT_0x9
_0xEF:
	LDI  R26,LOW(_pwm1)
	LDI  R27,HIGH(_pwm1)
	CALL SUBOPT_0x7
; 0000 010C     if(b<0){ cw2=1; ccw2=0; pwm2=-b; }    else { cw2=0; ccw2=1; pwm2=b; }
	LDD  R26,Y+11
	TST  R26
	BRPL _0x9E
	SBI  0xB,3
	CBI  0xB,4
	CALL SUBOPT_0xA
	CALL __ANEGF1
	RJMP _0xF0
_0x9E:
	CBI  0xB,3
	SBI  0xB,4
	CALL SUBOPT_0xA
_0xF0:
	LDI  R26,LOW(_pwm2)
	LDI  R27,HIGH(_pwm2)
	CALL SUBOPT_0x7
; 0000 010D     if(c<0){ cw3=1; ccw3=0; pwm3=-c; }    else { cw3=0; ccw3=1; pwm3=c; }
	LDD  R26,Y+7
	TST  R26
	BRPL _0xA8
	SBI  0x5,3
	CBI  0x5,2
	CALL SUBOPT_0xB
	CALL __ANEGF1
	RJMP _0xF1
_0xA8:
	CBI  0x5,3
	SBI  0x5,2
	CALL SUBOPT_0xB
_0xF1:
	LDI  R26,LOW(_pwm3)
	LDI  R27,HIGH(_pwm3)
	CALL SUBOPT_0x7
; 0000 010E     if(d<0){ cw4=1; ccw4=0; pwm4=-d; }    else { cw4=0; ccw4=1; pwm4=d; }
	LDD  R26,Y+3
	TST  R26
	BRPL _0xB2
	SBI  0x5,7
	CBI  0x5,6
	CALL SUBOPT_0xC
	CALL __ANEGF1
	RJMP _0xF2
_0xB2:
	CBI  0x5,7
	SBI  0x5,6
	CALL SUBOPT_0xC
_0xF2:
	LDI  R26,LOW(_pwm4)
	LDI  R27,HIGH(_pwm4)
	CALL SUBOPT_0x7
; 0000 010F }
	ADIW R28,16
	RET
;
;
;void Gerak_linier(float alpha, float asudut)
; 0000 0113 {   float a, b, c, d, tsudut;
_Gerak_linier:
; 0000 0114 
; 0000 0115     tsudut=alpha-asudut;
	SBIW R28,20
;	alpha -> Y+24
;	asudut -> Y+20
;	a -> Y+16
;	b -> Y+12
;	c -> Y+8
;	d -> Y+4
;	tsudut -> Y+0
	__GETD2S 20
	__GETD1S 24
	CALL __SUBF12
	__PUTD1S 0
; 0000 0116      a=cos(((35-tsudut)/180)*3.14);            //deg2rad
	CALL SUBOPT_0xD
	__GETD1N 0x420C0000
	CALL SUBOPT_0xE
	__PUTD1S 16
; 0000 0117      b=cos(((145-tsudut)/180)*3.14);
	CALL SUBOPT_0xD
	__GETD1N 0x43110000
	CALL SUBOPT_0xE
	__PUTD1S 12
; 0000 0118      c=cos(((225-tsudut)/180)*3.14);
	CALL SUBOPT_0xD
	__GETD1N 0x43610000
	CALL SUBOPT_0xE
	__PUTD1S 8
; 0000 0119      d=cos(((315-tsudut)/180)*3.14);
	CALL SUBOPT_0xD
	__GETD1N 0x439D8000
	CALL SUBOPT_0xE
	__PUTD1S 4
; 0000 011A 
; 0000 011B     Fa=Vel*a;
	__GETD1S 16
	CALL SUBOPT_0xF
	STS  _Fa,R30
	STS  _Fa+1,R31
	STS  _Fa+2,R22
	STS  _Fa+3,R23
; 0000 011C     Fb=Vel*b;
	CALL SUBOPT_0x9
	CALL SUBOPT_0xF
	STS  _Fb,R30
	STS  _Fb+1,R31
	STS  _Fb+2,R22
	STS  _Fb+3,R23
; 0000 011D     Fc=Vel*c;
	CALL SUBOPT_0xA
	CALL SUBOPT_0xF
	STS  _Fc,R30
	STS  _Fc+1,R31
	STS  _Fc+2,R22
	STS  _Fc+3,R23
; 0000 011E     Fd=Vel*d;
	CALL SUBOPT_0xB
	CALL SUBOPT_0xF
	STS  _Fd,R30
	STS  _Fd+1,R31
	STS  _Fd+2,R22
	STS  _Fd+3,R23
; 0000 011F }
	ADIW R28,28
	RET
;
;void Move(float alpha2, int jarak, float act_kompas)          //Linier + Angular
; 0000 0122 {
_Move:
; 0000 0123     float Fang, f1,f2,f3,f4;
; 0000 0124     float dkompas, alpha3;
; 0000 0125     int radius=8;
; 0000 0126 
; 0000 0127    // act_kompas=heading;
; 0000 0128 
; 0000 0129     Gerak_linier(alpha2,act_kompas);
	SBIW R28,28
	ST   -Y,R17
	ST   -Y,R16
;	alpha2 -> Y+36
;	jarak -> Y+34
;	act_kompas -> Y+30
;	Fang -> Y+26
;	f1 -> Y+22
;	f2 -> Y+18
;	f3 -> Y+14
;	f4 -> Y+10
;	dkompas -> Y+6
;	alpha3 -> Y+2
;	radius -> R16,R17
	__GETWRN 16,17,8
	CALL SUBOPT_0x10
	CALL __PUTPARD1
	__GETD1S 34
	CALL __PUTPARD1
	RCALL _Gerak_linier
; 0000 012A 
; 0000 012B     Fang=(Vel/radius);   //Gerak Angular
	MOVW R30,R16
	LDS  R26,_Vel
	LDS  R27,_Vel+1
	CALL __DIVW21
	CALL SUBOPT_0x11
	__PUTD1S 26
; 0000 012C 
; 0000 012D     if(alpha2>=0 && alpha2<=180)
	LDD  R26,Y+39
	TST  R26
	BRMI _0xBD
	CALL SUBOPT_0x12
	BREQ PC+4
	BRCS PC+3
	JMP  _0xBD
	RJMP _0xBE
_0xBD:
	RJMP _0xBC
_0xBE:
; 0000 012E     {
; 0000 012F         if(act_kompas >= (180+alpha2) || act_kompas <= alpha2)
	CALL SUBOPT_0x10
	__GETD2N 0x43340000
	CALL __ADDF12
	CALL SUBOPT_0x13
	BRSH _0xC0
	CALL SUBOPT_0x14
	BREQ PC+2
	BRCC PC+3
	JMP  _0xC0
	RJMP _0xBF
_0xC0:
; 0000 0130         {
; 0000 0131             if(act_kompas<=alpha2)
	CALL SUBOPT_0x14
	BREQ PC+4
	BRCS PC+3
	JMP  _0xC2
; 0000 0132             {
; 0000 0133                 dkompas = act_kompas;
	CALL SUBOPT_0x15
	RJMP _0xF3
; 0000 0134             }
; 0000 0135             else
_0xC2:
; 0000 0136             {
; 0000 0137                dkompas = -(360-act_kompas);
	__GETD2S 30
	__GETD1N 0x43B40000
	CALL __SUBF12
	CALL __ANEGF1
_0xF3:
	__PUTD1S 6
; 0000 0138             }
; 0000 0139              Fang = Fang;
	CALL SUBOPT_0x16
	RJMP _0xF4
; 0000 013A         }
; 0000 013B         else
_0xBF:
; 0000 013C         {
; 0000 013D             dkompas=act_kompas;
	CALL SUBOPT_0x17
; 0000 013E             Fang= -Fang;
	CALL __ANEGF1
_0xF4:
	__PUTD1S 26
; 0000 013F         }
; 0000 0140     }
; 0000 0141 
; 0000 0142     else  if(alpha2>180 && alpha2<=360)
	RJMP _0xC5
_0xBC:
	CALL SUBOPT_0x12
	BREQ PC+2
	BRCC PC+3
	JMP  _0xC7
	CALL SUBOPT_0x18
	__GETD1N 0x43B40000
	CALL __CMPF12
	BREQ PC+4
	BRCS PC+3
	JMP  _0xC7
	RJMP _0xC8
_0xC7:
	RJMP _0xC6
_0xC8:
; 0000 0143     {
; 0000 0144         if(alpha2 >= act_kompas && act_kompas >= (alpha2-180))
	CALL SUBOPT_0x15
	CALL SUBOPT_0x18
	CALL __CMPF12
	BRLO _0xCA
	CALL SUBOPT_0x19
	BRSH _0xCB
_0xCA:
	RJMP _0xC9
_0xCB:
; 0000 0145         {
; 0000 0146             dkompas = act_kompas;      Fang=Fang;
	CALL SUBOPT_0x17
	RJMP _0xF5
; 0000 0147         }
; 0000 0148         else if(act_kompas>=alpha2)
_0xC9:
	CALL SUBOPT_0x14
	BRLO _0xCD
; 0000 0149         {
; 0000 014A             dkompas = act_kompas;      Fang=-Fang;
	CALL SUBOPT_0x15
	RJMP _0xF6
; 0000 014B         }
; 0000 014C         else if(act_kompas<(alpha2-180))
_0xCD:
	CALL SUBOPT_0x19
	BRSH _0xCF
; 0000 014D         {
; 0000 014E             dkompas = (360+act_kompas);    Fang=-Fang;
	CALL SUBOPT_0x15
	__GETD2N 0x43B40000
	CALL __ADDF12
_0xF6:
	__PUTD1S 6
	CALL SUBOPT_0x16
	CALL __ANEGF1
_0xF5:
	__PUTD1S 26
; 0000 014F         }
; 0000 0150     }
_0xCF:
; 0000 0151 
; 0000 0152 
; 0000 0153       er=alpha2-dkompas;
_0xC6:
_0xC5:
	__GETD2S 6
	CALL SUBOPT_0x10
	CALL __SUBF12
	STS  _er,R30
	STS  _er+1,R31
	STS  _er+2,R22
	STS  _er+3,R23
; 0000 0154         P=Kp*er;
	CALL SUBOPT_0x1A
	LDS  R26,_Kp
	LDS  R27,_Kp+1
	CALL SUBOPT_0x6
	STS  _P,R30
	STS  _P+1,R31
	STS  _P+2,R22
	STS  _P+3,R23
; 0000 0155      der=er-laster;
	LDS  R30,_laster_G000
	LDS  R31,_laster_G000+1
	CALL SUBOPT_0x1B
	CALL SUBOPT_0x11
	CALL SUBOPT_0x1C
	STS  _der,R30
	STS  _der+1,R31
	STS  _der+2,R22
	STS  _der+3,R23
; 0000 0156          D=Kd*der;
	LDS  R26,_Kd
	LDS  R27,_Kd+1
	CALL SUBOPT_0x6
	STS  _D,R30
	STS  _D+1,R31
	STS  _D+2,R22
	STS  _D+3,R23
; 0000 0157      laster=er;
	CALL SUBOPT_0x1A
	LDI  R26,LOW(_laster_G000)
	LDI  R27,HIGH(_laster_G000)
	CALL __CFD1
	ST   X+,R30
	ST   X,R31
; 0000 0158          m=P+D;
	LDS  R30,_D
	LDS  R31,_D+1
	LDS  R22,_D+2
	LDS  R23,_D+3
	LDS  R26,_P
	LDS  R27,_P+1
	LDS  R24,_P+2
	LDS  R25,_P+3
	CALL __ADDF12
	LDI  R26,LOW(_m)
	LDI  R27,HIGH(_m)
	CALL __CFD1
	ST   X+,R30
	ST   X,R31
; 0000 0159 
; 0000 015A         if(er>=-8 && er<=8) Fang=0;
	CALL SUBOPT_0x1B
	__GETD1N 0xC1000000
	CALL __CMPF12
	BRLO _0xD1
	CALL SUBOPT_0x1B
	__GETD1N 0x41000000
	CALL __CMPF12
	BREQ PC+4
	BRCS PC+3
	JMP  _0xD1
	RJMP _0xD2
_0xD1:
	RJMP _0xD0
_0xD2:
	LDI  R30,LOW(0)
	STD  Y+26,R30
	STD  Y+26+1,R30
	STD  Y+26+2,R30
	STD  Y+26+3,R30
; 0000 015B         else Fang=Fang;
	RJMP _0xD3
_0xD0:
	CALL SUBOPT_0x16
	__PUTD1S 26
; 0000 015C 
; 0000 015D       //  if(er>=-3 && er<=3)  maju(200);
; 0000 015E       //  else
; 0000 015F      //   {
; 0000 0160           f1=Fa+Fang;//+m;
_0xD3:
	CALL SUBOPT_0x16
	LDS  R26,_Fa
	LDS  R27,_Fa+1
	LDS  R24,_Fa+2
	LDS  R25,_Fa+3
	CALL __ADDF12
	__PUTD1S 22
; 0000 0161           f2=Fb+Fang;//+m;
	CALL SUBOPT_0x16
	LDS  R26,_Fb
	LDS  R27,_Fb+1
	LDS  R24,_Fb+2
	LDS  R25,_Fb+3
	CALL __ADDF12
	__PUTD1S 18
; 0000 0162           f3=Fc+Fang;//+m;
	CALL SUBOPT_0x16
	LDS  R26,_Fc
	LDS  R27,_Fc+1
	LDS  R24,_Fc+2
	LDS  R25,_Fc+3
	CALL __ADDF12
	__PUTD1S 14
; 0000 0163           f4=Fd+Fang;//+m;
	CALL SUBOPT_0x16
	LDS  R26,_Fd
	LDS  R27,_Fd+1
	LDS  R24,_Fd+2
	LDS  R25,_Fd+3
	CALL __ADDF12
	__PUTD1S 10
; 0000 0164      //   }
; 0000 0165 
; 0000 0166 
; 0000 0167      CW_CCW_motor(f1,f2,f3,f4);
	CALL SUBOPT_0x1D
	CALL SUBOPT_0x1D
	CALL SUBOPT_0x1D
	CALL SUBOPT_0x1D
	RCALL _CW_CCW_motor
; 0000 0168 
; 0000 0169 //     lcd_gotoxy(0,0);
; 0000 016A //     sprintf(buffer," %.0f  %.0f  %.0f",alpha2,Fa,Fb);
; 0000 016B //     lcd_puts(buffer);
; 0000 016C //     lcd_gotoxy(0,1);
; 0000 016D //      sprintf(buffer," %.0f  %.0f  %.0f ",act_kompas,Fc,Fd);
; 0000 016E //     lcd_puts(buffer);
; 0000 016F //     delay_ms(100);
; 0000 0170 
; 0000 0171 }
	LDD  R17,Y+1
	LDD  R16,Y+0
	ADIW R28,40
	RET
;
;void ketarget(float sudt, int jarak, float shead)
; 0000 0174 {
_ketarget:
; 0000 0175     if(flag==1) stop();
;	sudt -> Y+6
;	jarak -> Y+4
;	shead -> Y+0
	LDI  R30,LOW(1)
	LDI  R31,HIGH(1)
	CP   R30,R7
	CPC  R31,R8
	BRNE _0xD4
	RCALL _stop
; 0000 0176     else   Move(sudt, jarak, shead);
	RJMP _0xD5
_0xD4:
	CALL SUBOPT_0x1E
	LDD  R30,Y+8
	LDD  R31,Y+8+1
	ST   -Y,R31
	ST   -Y,R30
	CALL SUBOPT_0x1E
	RCALL _Move
; 0000 0177 }
_0xD5:
	ADIW R28,10
	RET
;
;void kegawang(float alpha, int k_jrak, float act_kompas)
; 0000 017A {
; 0000 017B     if(flag==1) stop();
;	alpha -> Y+6
;	k_jrak -> Y+4
;	act_kompas -> Y+0
; 0000 017C     else
; 0000 017D     {
; 0000 017E         if(m_ok<=k_jrak)
; 0000 017F         { if(s_ok<=165 && s_ok>=90) {   Gerak_linier(alpha,act_kompas);     }     //kiri(100); delay_ms(40);
; 0000 0180           else if(s_ok>=195 && s_ok <=270) {  Gerak_linier(alpha,act_kompas);     }   //kanan(100); delay_ms(40);
; 0000 0181         }
; 0000 0182     }
; 0000 0183 }
;
;void main(void)
; 0000 0186 {
_main:
; 0000 0187 // Declare your local variables here
; 0000 0188 
; 0000 0189 // Input/Output Ports initialization
; 0000 018A // Port A initialization
; 0000 018B // Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In
; 0000 018C // State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T
; 0000 018D PORTA=0x00;
	LDI  R30,LOW(0)
	OUT  0x2,R30
; 0000 018E DDRA=0x00;
	OUT  0x1,R30
; 0000 018F 
; 0000 0190 // Port B initialization
; 0000 0191 // Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In
; 0000 0192 // State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T
; 0000 0193 PORTB=0x03;
	LDI  R30,LOW(3)
	OUT  0x5,R30
; 0000 0194 DDRB=0xFF;
	LDI  R30,LOW(255)
	OUT  0x4,R30
; 0000 0195 
; 0000 0196 // Port C initialization
; 0000 0197 // Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In
; 0000 0198 // State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T
; 0000 0199 PORTC=0x0F;
	LDI  R30,LOW(15)
	OUT  0x8,R30
; 0000 019A DDRC=0x00;
	LDI  R30,LOW(0)
	OUT  0x7,R30
; 0000 019B 
; 0000 019C // Port D initialization
; 0000 019D // Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In
; 0000 019E // State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T
; 0000 019F PORTD=0x00;
	OUT  0xB,R30
; 0000 01A0 DDRD=0xFC;
	LDI  R30,LOW(252)
	OUT  0xA,R30
; 0000 01A1 
; 0000 01A2 // Timer/Counter 0 initialization
; 0000 01A3 // Clock source: System Clock
; 0000 01A4 // Clock value: 11059.200 kHz
; 0000 01A5 // Mode: Normal top=FFh
; 0000 01A6 // OC0A output: Disconnected
; 0000 01A7 // OC0B output: Disconnected
; 0000 01A8 TCCR0A=0x00;
	LDI  R30,LOW(0)
	OUT  0x24,R30
; 0000 01A9 TCCR0B=0x01;
	LDI  R30,LOW(1)
	OUT  0x25,R30
; 0000 01AA TCNT0=0x00;
	LDI  R30,LOW(0)
	OUT  0x26,R30
; 0000 01AB OCR0A=0x00;
	OUT  0x27,R30
; 0000 01AC OCR0B=0x00;
	OUT  0x28,R30
; 0000 01AD 
; 0000 01AE // Timer/Counter 1 initialization
; 0000 01AF // Clock source: System Clock
; 0000 01B0 // Clock value: Timer 1 Stopped
; 0000 01B1 // Mode: Normal top=FFFFh
; 0000 01B2 // OC1A output: Discon.
; 0000 01B3 // OC1B output: Discon.
; 0000 01B4 // Noise Canceler: Off
; 0000 01B5 // Input Capture on Falling Edge
; 0000 01B6 // Timer 1 Overflow Interrupt: Off
; 0000 01B7 // Input Capture Interrupt: Off
; 0000 01B8 // Compare A Match Interrupt: Off
; 0000 01B9 // Compare B Match Interrupt: Off
; 0000 01BA TCCR1A=0x00;
	STS  128,R30
; 0000 01BB TCCR1B=0x00;
	STS  129,R30
; 0000 01BC TCNT1H=0x00;
	STS  133,R30
; 0000 01BD TCNT1L=0x00;
	STS  132,R30
; 0000 01BE ICR1H=0x00;
	STS  135,R30
; 0000 01BF ICR1L=0x00;
	STS  134,R30
; 0000 01C0 OCR1AH=0x00;
	STS  137,R30
; 0000 01C1 OCR1AL=0x00;
	STS  136,R30
; 0000 01C2 OCR1BH=0x00;
	STS  139,R30
; 0000 01C3 OCR1BL=0x00;
	STS  138,R30
; 0000 01C4 
; 0000 01C5 // Timer/Counter 2 initialization
; 0000 01C6 // Clock source: System Clock
; 0000 01C7 // Clock value: Timer 2 Stopped
; 0000 01C8 // Mode: Normal top=FFh
; 0000 01C9 // OC2A output: Disconnected
; 0000 01CA // OC2B output: Disconnected
; 0000 01CB ASSR=0x00;
	STS  182,R30
; 0000 01CC TCCR2A=0x00;
	STS  176,R30
; 0000 01CD TCCR2B=0x00;
	STS  177,R30
; 0000 01CE TCNT2=0x00;
	STS  178,R30
; 0000 01CF OCR2A=0x00;
	STS  179,R30
; 0000 01D0 OCR2B=0x00;
	STS  180,R30
; 0000 01D1 
; 0000 01D2 // External Interrupt(s) initialization
; 0000 01D3 // INT0: Off
; 0000 01D4 // INT1: Off
; 0000 01D5 // INT2: Off
; 0000 01D6 // Interrupt on any change on pins PCINT0-7: Off
; 0000 01D7 // Interrupt on any change on pins PCINT8-15: Off
; 0000 01D8 // Interrupt on any change on pins PCINT16-23: Off
; 0000 01D9 // Interrupt on any change on pins PCINT24-31: Off
; 0000 01DA EICRA=0x00;
	STS  105,R30
; 0000 01DB EIMSK=0x00;
	OUT  0x1D,R30
; 0000 01DC PCICR=0x00;
	STS  104,R30
; 0000 01DD 
; 0000 01DE // Timer/Counter 0 Interrupt(s) initialization
; 0000 01DF TIMSK0=0x01;
	LDI  R30,LOW(1)
	STS  110,R30
; 0000 01E0 // Timer/Counter 1 Interrupt(s) initialization
; 0000 01E1 TIMSK1=0x00;
	LDI  R30,LOW(0)
	STS  111,R30
; 0000 01E2 // Timer/Counter 2 Interrupt(s) initialization
; 0000 01E3 TIMSK2=0x00;
	STS  112,R30
; 0000 01E4 
; 0000 01E5 // USART initialization
; 0000 01E6 // Communication Parameters: 8 Data, 1 Stop, No Parity
; 0000 01E7 // USART Receiver: On
; 0000 01E8 // USART Transmitter: On
; 0000 01E9 // USART0 Mode: Asynchronous
; 0000 01EA // USART Baud Rate: 19200
; 0000 01EB UCSR0A=0x00;
	STS  192,R30
; 0000 01EC UCSR0B=0x98;
	LDI  R30,LOW(152)
	STS  193,R30
; 0000 01ED UCSR0C=0x06;
	LDI  R30,LOW(6)
	STS  194,R30
; 0000 01EE UBRR0H=0x00;
	LDI  R30,LOW(0)
	STS  197,R30
; 0000 01EF UBRR0L=0x47; //0x23;
	LDI  R30,LOW(71)
	STS  196,R30
; 0000 01F0 
; 0000 01F1 // Analog Comparator initialization
; 0000 01F2 // Analog Comparator: Off
; 0000 01F3 // Analog Comparator Input Capture by Timer/Counter 1: Off
; 0000 01F4 ACSR=0x80;
	LDI  R30,LOW(128)
	OUT  0x30,R30
; 0000 01F5 ADCSRB=0x00;
	LDI  R30,LOW(0)
	STS  123,R30
; 0000 01F6 
; 0000 01F7 // LCD module initialization
; 0000 01F8 lcd_init(16);
	LDI  R30,LOW(16)
	ST   -Y,R30
	CALL _lcd_init
; 0000 01F9 
; 0000 01FA 
; 0000 01FB // Global enable interrupts
; 0000 01FC #asm("sei")
	sei
; 0000 01FD 
; 0000 01FE Vel = 210;
	LDI  R30,LOW(210)
	LDI  R31,HIGH(210)
	STS  _Vel,R30
	STS  _Vel+1,R31
; 0000 01FF //Vel = 240;
; 0000 0200 
; 0000 0201 while (1)
_0xE0:
; 0000 0202       {
; 0000 0203      // Place your code here
; 0000 0204 
; 0000 0205      while(flag==1) stop();
_0xE3:
	LDI  R30,LOW(1)
	LDI  R31,HIGH(1)
	CP   R30,R7
	CPC  R31,R8
	BRNE _0xE5
	RCALL _stop
	RJMP _0xE3
_0xE5:
; 0000 0217 if(tanda_g == 1) mundur(100);
	LDI  R30,LOW(1)
	LDI  R31,HIGH(1)
	CP   R30,R11
	CPC  R31,R12
	BRNE _0xE6
	LDI  R30,LOW(100)
	ST   -Y,R30
	RCALL _mundur
; 0000 0218        else if(m_gt <= m_rt)
	RJMP _0xE7
_0xE6:
	LDS  R30,_m_rt_G000
	LDS  R31,_m_rt_G000+1
	LDS  R26,_m_gt_G000
	LDS  R27,_m_gt_G000+1
	CP   R30,R26
	CPC  R31,R27
	BRLT _0xE8
; 0000 0219        {
; 0000 021A            if(m_gt >= 30) ketarget(s_gt, m_gt,sg);
	SBIW R26,30
	BRLT _0xE9
	LDS  R30,_s_gt_G000
	LDS  R31,_s_gt_G000+1
	CALL SUBOPT_0x1F
	LDS  R30,_m_gt_G000
	LDS  R31,_m_gt_G000+1
	RJMP _0xF8
; 0000 021B            else ketarget(s_gk, m_gk, sg);
_0xE9:
	LDS  R30,_s_gk_G000
	LDS  R31,_s_gk_G000+1
	CALL SUBOPT_0x1F
	LDS  R30,_m_gk_G000
	LDS  R31,_m_gk_G000+1
_0xF8:
	ST   -Y,R31
	ST   -Y,R30
	CALL SUBOPT_0x20
	RCALL _ketarget
; 0000 021C        }
; 0000 021D        else
	RJMP _0xEB
_0xE8:
; 0000 021E        {
; 0000 021F             if(m_gr<120) stop();
	LDS  R26,_m_gr_G000
	LDS  R27,_m_gr_G000+1
	CPI  R26,LOW(0x78)
	LDI  R30,HIGH(0x78)
	CPC  R27,R30
	BRGE _0xEC
	RCALL _stop
; 0000 0220             else ketarget(s_gr, m_gr, sg);
	RJMP _0xED
_0xEC:
	LDS  R30,_s_gr_G000
	LDS  R31,_s_gr_G000+1
	CALL SUBOPT_0x1F
	LDS  R30,_m_gr_G000
	LDS  R31,_m_gr_G000+1
	ST   -Y,R31
	ST   -Y,R30
	CALL SUBOPT_0x20
	RCALL _ketarget
; 0000 0221        }
_0xED:
_0xEB:
_0xE7:
; 0000 0222 
; 0000 0223 
; 0000 0224       };
	RJMP _0xE0
; 0000 0225 }
_0xEE:
	RJMP _0xEE
	#ifndef __SLEEP_DEFINED__
	#define __SLEEP_DEFINED__
	.EQU __se_bit=0x01
	.EQU __sm_mask=0x0E
	.EQU __sm_powerdown=0x04
	.EQU __sm_powersave=0x06
	.EQU __sm_standby=0x0C
	.EQU __sm_ext_standby=0x0E
	.EQU __sm_adc_noise_red=0x02
	.SET power_ctrl_reg=smcr
	#endif

	.CSEG

	.CSEG
_ftrunc:
   ldd  r23,y+3
   ldd  r22,y+2
   ldd  r31,y+1
   ld   r30,y
   bst  r23,7
   lsl  r23
   sbrc r22,7
   sbr  r23,1
   mov  r25,r23
   subi r25,0x7e
   breq __ftrunc0
   brcs __ftrunc0
   cpi  r25,24
   brsh __ftrunc1
   clr  r26
   clr  r27
   clr  r24
__ftrunc2:
   sec
   ror  r24
   ror  r27
   ror  r26
   dec  r25
   brne __ftrunc2
   and  r30,r26
   and  r31,r27
   and  r22,r24
   rjmp __ftrunc1
__ftrunc0:
   clt
   clr  r23
   clr  r30
   clr  r31
   clr  r22
__ftrunc1:
   cbr  r22,0x80
   lsr  r23
   brcc __ftrunc3
   sbr  r22,0x80
__ftrunc3:
   bld  r23,7
   ld   r26,y+
   ld   r27,y+
   ld   r24,y+
   ld   r25,y+
   cp   r30,r26
   cpc  r31,r27
   cpc  r22,r24
   cpc  r23,r25
   bst  r25,7
   ret
_floor:
	CALL SUBOPT_0xC
	CALL __PUTPARD1
	CALL _ftrunc
	__PUTD1S 0
    brne __floor1
__floor0:
	CALL SUBOPT_0xC
	RJMP _0x20C0002
__floor1:
    brtc __floor0
	CALL SUBOPT_0xD
	__GETD1N 0x3F800000
	CALL SUBOPT_0x1C
	RJMP _0x20C0002
_sin:
	SBIW R28,4
	ST   -Y,R17
	LDI  R17,0
	CALL SUBOPT_0x21
	__GETD1N 0x3E22F983
	CALL __MULF12
	CALL SUBOPT_0x22
	CALL SUBOPT_0x23
	CALL __PUTPARD1
	RCALL _floor
	CALL SUBOPT_0x21
	CALL SUBOPT_0x1C
	CALL SUBOPT_0x22
	CALL SUBOPT_0x24
	CALL __CMPF12
	BREQ PC+2
	BRCC PC+3
	JMP  _0x2020017
	CALL SUBOPT_0x24
	CALL SUBOPT_0x1C
	CALL SUBOPT_0x22
	LDI  R17,LOW(1)
_0x2020017:
	CALL SUBOPT_0x21
	__GETD1N 0x3E800000
	CALL __CMPF12
	BREQ PC+2
	BRCC PC+3
	JMP  _0x2020018
	CALL SUBOPT_0x24
	CALL __SUBF12
	CALL SUBOPT_0x22
_0x2020018:
	CPI  R17,0
	BREQ _0x2020019
	CALL SUBOPT_0x23
	CALL __ANEGF1
	CALL SUBOPT_0x22
_0x2020019:
	CALL SUBOPT_0x23
	CALL SUBOPT_0x21
	CALL __MULF12
	__PUTD1S 1
	__GETD2N 0x4226C4B1
	CALL __MULF12
	MOVW R26,R30
	MOVW R24,R22
	__GETD1N 0x422DE51D
	CALL SUBOPT_0x1C
	CALL SUBOPT_0x25
	__GETD2N 0x4104534C
	CALL __ADDF12
	CALL SUBOPT_0x21
	CALL __MULF12
	PUSH R23
	PUSH R22
	PUSH R31
	PUSH R30
	__GETD1S 1
	__GETD2N 0x3FDEED11
	CALL __ADDF12
	CALL SUBOPT_0x25
	__GETD2N 0x3FA87B5E
	CALL __ADDF12
	POP  R26
	POP  R27
	POP  R24
	POP  R25
	CALL __DIVF21
	LDD  R17,Y+0
	ADIW R28,9
	RET
_cos:
	CALL SUBOPT_0xD
	__GETD1N 0x3FC90FDB
	CALL __SUBF12
	CALL __PUTPARD1
	RCALL _sin
_0x20C0002:
	ADIW R28,4
	RET
    .equ __lcd_direction=__lcd_port-1
    .equ __lcd_pin=__lcd_port-2
    .equ __lcd_rs=0
    .equ __lcd_rd=1
    .equ __lcd_enable=2
    .equ __lcd_busy_flag=7

	.DSEG

	.CSEG
__lcd_delay_G102:
    ldi   r31,15
__lcd_delay0:
    dec   r31
    brne  __lcd_delay0
	RET
__lcd_ready:
    in    r26,__lcd_direction
    andi  r26,0xf                 ;set as input
    out   __lcd_direction,r26
    sbi   __lcd_port,__lcd_rd     ;RD=1
    cbi   __lcd_port,__lcd_rs     ;RS=0
__lcd_busy:
	RCALL __lcd_delay_G102
    sbi   __lcd_port,__lcd_enable ;EN=1
	RCALL __lcd_delay_G102
    in    r26,__lcd_pin
    cbi   __lcd_port,__lcd_enable ;EN=0
	RCALL __lcd_delay_G102
    sbi   __lcd_port,__lcd_enable ;EN=1
	RCALL __lcd_delay_G102
    cbi   __lcd_port,__lcd_enable ;EN=0
    sbrc  r26,__lcd_busy_flag
    rjmp  __lcd_busy
	RET
__lcd_write_nibble_G102:
    andi  r26,0xf0
    or    r26,r27
    out   __lcd_port,r26          ;write
    sbi   __lcd_port,__lcd_enable ;EN=1
	CALL __lcd_delay_G102
    cbi   __lcd_port,__lcd_enable ;EN=0
	CALL __lcd_delay_G102
	RET
__lcd_write_data:
    cbi  __lcd_port,__lcd_rd 	  ;RD=0
    in    r26,__lcd_direction
    ori   r26,0xf0 | (1<<__lcd_rs) | (1<<__lcd_rd) | (1<<__lcd_enable) ;set as output
    out   __lcd_direction,r26
    in    r27,__lcd_port
    andi  r27,0xf
    ld    r26,y
	RCALL __lcd_write_nibble_G102
    ld    r26,y
    swap  r26
	RCALL __lcd_write_nibble_G102
    sbi   __lcd_port,__lcd_rd     ;RD=1
	JMP  _0x20C0001
__lcd_read_nibble_G102:
    sbi   __lcd_port,__lcd_enable ;EN=1
	CALL __lcd_delay_G102
    in    r30,__lcd_pin           ;read
    cbi   __lcd_port,__lcd_enable ;EN=0
	CALL __lcd_delay_G102
    andi  r30,0xf0
	RET
_lcd_read_byte0_G102:
	CALL __lcd_delay_G102
	RCALL __lcd_read_nibble_G102
    mov   r26,r30
	RCALL __lcd_read_nibble_G102
    cbi   __lcd_port,__lcd_rd     ;RD=0
    swap  r30
    or    r30,r26
	RET
_lcd_clear:
	CALL __lcd_ready
	LDI  R30,LOW(2)
	ST   -Y,R30
	CALL __lcd_write_data
	CALL __lcd_ready
	LDI  R30,LOW(12)
	ST   -Y,R30
	CALL __lcd_write_data
	CALL __lcd_ready
	LDI  R30,LOW(1)
	ST   -Y,R30
	CALL __lcd_write_data
	LDI  R30,LOW(0)
	STS  __lcd_y,R30
	STS  __lcd_x,R30
	RET
__long_delay_G102:
    clr   r26
    clr   r27
__long_delay0:
    sbiw  r26,1         ;2 cycles
    brne  __long_delay0 ;2 cycles
	RET
__lcd_init_write_G102:
    cbi  __lcd_port,__lcd_rd 	  ;RD=0
    in    r26,__lcd_direction
    ori   r26,0xf7                ;set as output
    out   __lcd_direction,r26
    in    r27,__lcd_port
    andi  r27,0xf
    ld    r26,y
	CALL __lcd_write_nibble_G102
    sbi   __lcd_port,__lcd_rd     ;RD=1
	RJMP _0x20C0001
_lcd_init:
    cbi   __lcd_port,__lcd_enable ;EN=0
    cbi   __lcd_port,__lcd_rs     ;RS=0
	LD   R30,Y
	STS  __lcd_maxx,R30
	CALL SUBOPT_0x4
	SUBI R30,LOW(-128)
	SBCI R31,HIGH(-128)
	__PUTB1MN __base_y_G102,2
	CALL SUBOPT_0x4
	SUBI R30,LOW(-192)
	SBCI R31,HIGH(-192)
	__PUTB1MN __base_y_G102,3
	CALL SUBOPT_0x26
	CALL SUBOPT_0x26
	CALL SUBOPT_0x26
	RCALL __long_delay_G102
	LDI  R30,LOW(32)
	ST   -Y,R30
	RCALL __lcd_init_write_G102
	RCALL __long_delay_G102
	LDI  R30,LOW(40)
	CALL SUBOPT_0x27
	LDI  R30,LOW(4)
	CALL SUBOPT_0x27
	LDI  R30,LOW(133)
	CALL SUBOPT_0x27
    in    r26,__lcd_direction
    andi  r26,0xf                 ;set as input
    out   __lcd_direction,r26
    sbi   __lcd_port,__lcd_rd     ;RD=1
	CALL _lcd_read_byte0_G102
	CPI  R30,LOW(0x5)
	BREQ _0x204000B
	LDI  R30,LOW(0)
	RJMP _0x20C0001
_0x204000B:
	CALL __lcd_ready
	LDI  R30,LOW(6)
	ST   -Y,R30
	CALL __lcd_write_data
	CALL _lcd_clear
	LDI  R30,LOW(1)
_0x20C0001:
	ADIW R28,1
	RET

	.CSEG

	.CSEG

	.CSEG

	.DSEG

	.CSEG

	.DSEG
_rx_buffer0:
	.BYTE 0x8
_sr_G000:
	.BYTE 0x2
_sg_G000:
	.BYTE 0x2
_s_rt_G000:
	.BYTE 0x2
_s_gt_G000:
	.BYTE 0x2
_s_rg_G000:
	.BYTE 0x2
_s_gr_G000:
	.BYTE 0x2
_s_rk_G000:
	.BYTE 0x2
_s_gk_G000:
	.BYTE 0x2
_s_ok_G000:
	.BYTE 0x2
_m_rt_G000:
	.BYTE 0x2
_m_gt_G000:
	.BYTE 0x2
_m_rg_G000:
	.BYTE 0x2
_m_gr_G000:
	.BYTE 0x2
_m_rk_G000:
	.BYTE 0x2
_m_gk_G000:
	.BYTE 0x2
_m_ok_G000:
	.BYTE 0x2
_Fa:
	.BYTE 0x4
_Fb:
	.BYTE 0x4
_Fc:
	.BYTE 0x4
_Fd:
	.BYTE 0x4
_Vel:
	.BYTE 0x2
_er:
	.BYTE 0x4
_der:
	.BYTE 0x4
_P:
	.BYTE 0x4
_D:
	.BYTE 0x4
_laster_G000:
	.BYTE 0x2
_m:
	.BYTE 0x2
_Kp:
	.BYTE 0x2
_Kd:
	.BYTE 0x2
_sData:
	.BYTE 0x8
_a:
	.BYTE 0x2
_pwm1:
	.BYTE 0x2
_pwm2:
	.BYTE 0x2
_pwm3:
	.BYTE 0x2
_pwm4:
	.BYTE 0x2
_pwm5:
	.BYTE 0x2
_psol:
	.BYTE 0x1
__base_y_G102:
	.BYTE 0x4
__lcd_x:
	.BYTE 0x1
__lcd_y:
	.BYTE 0x1
__lcd_maxx:
	.BYTE 0x1
_p_S1040024:
	.BYTE 0x2
__seed_G105:
	.BYTE 0x4

	.CSEG
;OPTIMIZER ADDED SUBROUTINE, CALLED 4 TIMES, CODE SIZE REDUCTION:3 WORDS
SUBOPT_0x0:
	LDI  R31,0
	SBIW R30,48
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES, CODE SIZE REDUCTION:1 WORDS
SUBOPT_0x1:
	LDI  R26,LOW(10)
	LDI  R27,HIGH(10)
	CALL __MULW12
	__ADDWRR 16,17,30,31
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 7 TIMES, CODE SIZE REDUCTION:9 WORDS
SUBOPT_0x2:
	LDS  R26,_a
	LDS  R27,_a+1
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 5 TIMES, CODE SIZE REDUCTION:5 WORDS
SUBOPT_0x3:
	RCALL SUBOPT_0x2
	CP   R30,R26
	CPC  R31,R27
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 6 TIMES, CODE SIZE REDUCTION:7 WORDS
SUBOPT_0x4:
	LD   R30,Y
	LDI  R31,0
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES, CODE SIZE REDUCTION:3 WORDS
SUBOPT_0x5:
	__GETD1N 0x42700000
	CALL __PUTPARD1
	JMP  _cos

;OPTIMIZER ADDED SUBROUTINE, CALLED 10 TIMES, CODE SIZE REDUCTION:33 WORDS
SUBOPT_0x6:
	CALL __CWD2
	CALL __CDF2
	CALL __MULF12
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 8 TIMES, CODE SIZE REDUCTION:11 WORDS
SUBOPT_0x7:
	CALL __CFD1U
	ST   X+,R30
	ST   X,R31
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES, CODE SIZE REDUCTION:3 WORDS
SUBOPT_0x8:
	__GETD1N 0x42340000
	CALL __PUTPARD1
	JMP  _cos

;OPTIMIZER ADDED SUBROUTINE, CALLED 3 TIMES, CODE SIZE REDUCTION:1 WORDS
SUBOPT_0x9:
	__GETD1S 12
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 3 TIMES, CODE SIZE REDUCTION:1 WORDS
SUBOPT_0xA:
	__GETD1S 8
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 3 TIMES, CODE SIZE REDUCTION:1 WORDS
SUBOPT_0xB:
	__GETD1S 4
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 4 TIMES, CODE SIZE REDUCTION:3 WORDS
SUBOPT_0xC:
	__GETD1S 0
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 6 TIMES, CODE SIZE REDUCTION:7 WORDS
SUBOPT_0xD:
	__GETD2S 0
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 4 TIMES, CODE SIZE REDUCTION:51 WORDS
SUBOPT_0xE:
	CALL __SUBF12
	MOVW R26,R30
	MOVW R24,R22
	__GETD1N 0x43340000
	CALL __DIVF21
	__GETD2N 0x4048F5C3
	CALL __MULF12
	CALL __PUTPARD1
	JMP  _cos

;OPTIMIZER ADDED SUBROUTINE, CALLED 4 TIMES, CODE SIZE REDUCTION:9 WORDS
SUBOPT_0xF:
	LDS  R26,_Vel
	LDS  R27,_Vel+1
	RJMP SUBOPT_0x6

;OPTIMIZER ADDED SUBROUTINE, CALLED 6 TIMES, CODE SIZE REDUCTION:7 WORDS
SUBOPT_0x10:
	__GETD1S 36
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 7 TIMES, CODE SIZE REDUCTION:9 WORDS
SUBOPT_0x11:
	CALL __CWD1
	CALL __CDF1
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES, CODE SIZE REDUCTION:5 WORDS
SUBOPT_0x12:
	__GETD2S 36
	__GETD1N 0x43340000
	CALL __CMPF12
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 6 TIMES, CODE SIZE REDUCTION:17 WORDS
SUBOPT_0x13:
	__GETD2S 30
	CALL __CMPF12
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 3 TIMES, CODE SIZE REDUCTION:1 WORDS
SUBOPT_0x14:
	RCALL SUBOPT_0x10
	RJMP SUBOPT_0x13

;OPTIMIZER ADDED SUBROUTINE, CALLED 6 TIMES, CODE SIZE REDUCTION:7 WORDS
SUBOPT_0x15:
	__GETD1S 30
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 9 TIMES, CODE SIZE REDUCTION:13 WORDS
SUBOPT_0x16:
	__GETD1S 26
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES, CODE SIZE REDUCTION:3 WORDS
SUBOPT_0x17:
	RCALL SUBOPT_0x15
	__PUTD1S 6
	RJMP SUBOPT_0x16

;OPTIMIZER ADDED SUBROUTINE, CALLED 4 TIMES, CODE SIZE REDUCTION:3 WORDS
SUBOPT_0x18:
	__GETD2S 36
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES, CODE SIZE REDUCTION:7 WORDS
SUBOPT_0x19:
	RCALL SUBOPT_0x18
	__GETD1N 0x43340000
	CALL __SWAPD12
	CALL __SUBF12
	RJMP SUBOPT_0x13

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES, CODE SIZE REDUCTION:3 WORDS
SUBOPT_0x1A:
	LDS  R30,_er
	LDS  R31,_er+1
	LDS  R22,_er+2
	LDS  R23,_er+3
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 3 TIMES, CODE SIZE REDUCTION:9 WORDS
SUBOPT_0x1B:
	LDS  R26,_er
	LDS  R27,_er+1
	LDS  R24,_er+2
	LDS  R25,_er+3
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 5 TIMES, CODE SIZE REDUCTION:5 WORDS
SUBOPT_0x1C:
	CALL __SWAPD12
	CALL __SUBF12
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 4 TIMES, CODE SIZE REDUCTION:9 WORDS
SUBOPT_0x1D:
	__GETD1S 22
	CALL __PUTPARD1
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES, CODE SIZE REDUCTION:1 WORDS
SUBOPT_0x1E:
	__GETD1S 6
	CALL __PUTPARD1
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 5 TIMES, CODE SIZE REDUCTION:5 WORDS
SUBOPT_0x1F:
	RCALL SUBOPT_0x11
	CALL __PUTPARD1
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES, CODE SIZE REDUCTION:1 WORDS
SUBOPT_0x20:
	LDS  R30,_sg_G000
	LDS  R31,_sg_G000+1
	RJMP SUBOPT_0x1F

;OPTIMIZER ADDED SUBROUTINE, CALLED 8 TIMES, CODE SIZE REDUCTION:11 WORDS
SUBOPT_0x21:
	__GETD2S 5
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 5 TIMES, CODE SIZE REDUCTION:5 WORDS
SUBOPT_0x22:
	__PUTD1S 5
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 3 TIMES, CODE SIZE REDUCTION:1 WORDS
SUBOPT_0x23:
	__GETD1S 5
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 3 TIMES, CODE SIZE REDUCTION:5 WORDS
SUBOPT_0x24:
	RCALL SUBOPT_0x21
	__GETD1N 0x3F000000
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES, CODE SIZE REDUCTION:1 WORDS
SUBOPT_0x25:
	__GETD2S 1
	CALL __MULF12
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 3 TIMES, CODE SIZE REDUCTION:5 WORDS
SUBOPT_0x26:
	CALL __long_delay_G102
	LDI  R30,LOW(48)
	ST   -Y,R30
	JMP  __lcd_init_write_G102

;OPTIMIZER ADDED SUBROUTINE, CALLED 3 TIMES, CODE SIZE REDUCTION:3 WORDS
SUBOPT_0x27:
	ST   -Y,R30
	CALL __lcd_write_data
	JMP  __long_delay_G102


	.CSEG
__ANEGW1:
	NEG  R31
	NEG  R30
	SBCI R31,0
	RET

__ANEGD1:
	COM  R31
	COM  R22
	COM  R23
	NEG  R30
	SBCI R31,-1
	SBCI R22,-1
	SBCI R23,-1
	RET

__CWD1:
	MOV  R22,R31
	ADD  R22,R22
	SBC  R22,R22
	MOV  R23,R22
	RET

__CWD2:
	MOV  R24,R27
	ADD  R24,R24
	SBC  R24,R24
	MOV  R25,R24
	RET

__MULW12U:
	MUL  R31,R26
	MOV  R31,R0
	MUL  R30,R27
	ADD  R31,R0
	MUL  R30,R26
	MOV  R30,R0
	ADD  R31,R1
	RET

__MULW12:
	RCALL __CHKSIGNW
	RCALL __MULW12U
	BRTC __MULW121
	RCALL __ANEGW1
__MULW121:
	RET

__DIVW21U:
	CLR  R0
	CLR  R1
	LDI  R25,16
__DIVW21U1:
	LSL  R26
	ROL  R27
	ROL  R0
	ROL  R1
	SUB  R0,R30
	SBC  R1,R31
	BRCC __DIVW21U2
	ADD  R0,R30
	ADC  R1,R31
	RJMP __DIVW21U3
__DIVW21U2:
	SBR  R26,1
__DIVW21U3:
	DEC  R25
	BRNE __DIVW21U1
	MOVW R30,R26
	MOVW R26,R0
	RET

__DIVW21:
	RCALL __CHKSIGNW
	RCALL __DIVW21U
	BRTC __DIVW211
	RCALL __ANEGW1
__DIVW211:
	RET

__CHKSIGNW:
	CLT
	SBRS R31,7
	RJMP __CHKSW1
	RCALL __ANEGW1
	SET
__CHKSW1:
	SBRS R27,7
	RJMP __CHKSW2
	COM  R26
	COM  R27
	ADIW R26,1
	BLD  R0,0
	INC  R0
	BST  R0,0
__CHKSW2:
	RET

__PUTPARD1:
	ST   -Y,R23
	ST   -Y,R22
	ST   -Y,R31
	ST   -Y,R30
	RET

__CDF2U:
	SET
	RJMP __CDF2U0
__CDF2:
	CLT
__CDF2U0:
	RCALL __SWAPD12
	RCALL __CDF1U0

__SWAPD12:
	MOV  R1,R24
	MOV  R24,R22
	MOV  R22,R1
	MOV  R1,R25
	MOV  R25,R23
	MOV  R23,R1

__SWAPW12:
	MOV  R1,R27
	MOV  R27,R31
	MOV  R31,R1

__SWAPB12:
	MOV  R1,R26
	MOV  R26,R30
	MOV  R30,R1
	RET

__ANEGF1:
	SBIW R30,0
	SBCI R22,0
	SBCI R23,0
	BREQ __ANEGF10
	SUBI R23,0x80
__ANEGF10:
	RET

__ROUND_REPACK:
	TST  R21
	BRPL __REPACK
	CPI  R21,0x80
	BRNE __ROUND_REPACK0
	SBRS R30,0
	RJMP __REPACK
__ROUND_REPACK0:
	ADIW R30,1
	ADC  R22,R25
	ADC  R23,R25
	BRVS __REPACK1

__REPACK:
	LDI  R21,0x80
	EOR  R21,R23
	BRNE __REPACK0
	PUSH R21
	RJMP __ZERORES
__REPACK0:
	CPI  R21,0xFF
	BREQ __REPACK1
	LSL  R22
	LSL  R0
	ROR  R21
	ROR  R22
	MOV  R23,R21
	RET
__REPACK1:
	PUSH R21
	TST  R0
	BRMI __REPACK2
	RJMP __MAXRES
__REPACK2:
	RJMP __MINRES

__UNPACK:
	LDI  R21,0x80
	MOV  R1,R25
	AND  R1,R21
	LSL  R24
	ROL  R25
	EOR  R25,R21
	LSL  R21
	ROR  R24

__UNPACK1:
	LDI  R21,0x80
	MOV  R0,R23
	AND  R0,R21
	LSL  R22
	ROL  R23
	EOR  R23,R21
	LSL  R21
	ROR  R22
	RET

__CFD1U:
	SET
	RJMP __CFD1U0
__CFD1:
	CLT
__CFD1U0:
	PUSH R21
	RCALL __UNPACK1
	CPI  R23,0x80
	BRLO __CFD10
	CPI  R23,0xFF
	BRCC __CFD10
	RJMP __ZERORES
__CFD10:
	LDI  R21,22
	SUB  R21,R23
	BRPL __CFD11
	NEG  R21
	CPI  R21,8
	BRTC __CFD19
	CPI  R21,9
__CFD19:
	BRLO __CFD17
	SER  R30
	SER  R31
	SER  R22
	LDI  R23,0x7F
	BLD  R23,7
	RJMP __CFD15
__CFD17:
	CLR  R23
	TST  R21
	BREQ __CFD15
__CFD18:
	LSL  R30
	ROL  R31
	ROL  R22
	ROL  R23
	DEC  R21
	BRNE __CFD18
	RJMP __CFD15
__CFD11:
	CLR  R23
__CFD12:
	CPI  R21,8
	BRLO __CFD13
	MOV  R30,R31
	MOV  R31,R22
	MOV  R22,R23
	SUBI R21,8
	RJMP __CFD12
__CFD13:
	TST  R21
	BREQ __CFD15
__CFD14:
	LSR  R23
	ROR  R22
	ROR  R31
	ROR  R30
	DEC  R21
	BRNE __CFD14
__CFD15:
	TST  R0
	BRPL __CFD16
	RCALL __ANEGD1
__CFD16:
	POP  R21
	RET

__CDF1U:
	SET
	RJMP __CDF1U0
__CDF1:
	CLT
__CDF1U0:
	SBIW R30,0
	SBCI R22,0
	SBCI R23,0
	BREQ __CDF10
	CLR  R0
	BRTS __CDF11
	TST  R23
	BRPL __CDF11
	COM  R0
	RCALL __ANEGD1
__CDF11:
	MOV  R1,R23
	LDI  R23,30
	TST  R1
__CDF12:
	BRMI __CDF13
	DEC  R23
	LSL  R30
	ROL  R31
	ROL  R22
	ROL  R1
	RJMP __CDF12
__CDF13:
	MOV  R30,R31
	MOV  R31,R22
	MOV  R22,R1
	PUSH R21
	RCALL __REPACK
	POP  R21
__CDF10:
	RET

__SWAPACC:
	PUSH R20
	MOVW R20,R30
	MOVW R30,R26
	MOVW R26,R20
	MOVW R20,R22
	MOVW R22,R24
	MOVW R24,R20
	MOV  R20,R0
	MOV  R0,R1
	MOV  R1,R20
	POP  R20
	RET

__UADD12:
	ADD  R30,R26
	ADC  R31,R27
	ADC  R22,R24
	RET

__NEGMAN1:
	COM  R30
	COM  R31
	COM  R22
	SUBI R30,-1
	SBCI R31,-1
	SBCI R22,-1
	RET

__SUBF12:
	PUSH R21
	RCALL __UNPACK
	CPI  R25,0x80
	BREQ __ADDF129
	LDI  R21,0x80
	EOR  R1,R21

	RJMP __ADDF120

__ADDF12:
	PUSH R21
	RCALL __UNPACK
	CPI  R25,0x80
	BREQ __ADDF129

__ADDF120:
	CPI  R23,0x80
	BREQ __ADDF128
__ADDF121:
	MOV  R21,R23
	SUB  R21,R25
	BRVS __ADDF129
	BRPL __ADDF122
	RCALL __SWAPACC
	RJMP __ADDF121
__ADDF122:
	CPI  R21,24
	BRLO __ADDF123
	CLR  R26
	CLR  R27
	CLR  R24
__ADDF123:
	CPI  R21,8
	BRLO __ADDF124
	MOV  R26,R27
	MOV  R27,R24
	CLR  R24
	SUBI R21,8
	RJMP __ADDF123
__ADDF124:
	TST  R21
	BREQ __ADDF126
__ADDF125:
	LSR  R24
	ROR  R27
	ROR  R26
	DEC  R21
	BRNE __ADDF125
__ADDF126:
	MOV  R21,R0
	EOR  R21,R1
	BRMI __ADDF127
	RCALL __UADD12
	BRCC __ADDF129
	ROR  R22
	ROR  R31
	ROR  R30
	INC  R23
	BRVC __ADDF129
	RJMP __MAXRES
__ADDF128:
	RCALL __SWAPACC
__ADDF129:
	RCALL __REPACK
	POP  R21
	RET
__ADDF127:
	SUB  R30,R26
	SBC  R31,R27
	SBC  R22,R24
	BREQ __ZERORES
	BRCC __ADDF1210
	COM  R0
	RCALL __NEGMAN1
__ADDF1210:
	TST  R22
	BRMI __ADDF129
	LSL  R30
	ROL  R31
	ROL  R22
	DEC  R23
	BRVC __ADDF1210

__ZERORES:
	CLR  R30
	CLR  R31
	CLR  R22
	CLR  R23
	POP  R21
	RET

__MINRES:
	SER  R30
	SER  R31
	LDI  R22,0x7F
	SER  R23
	POP  R21
	RET

__MAXRES:
	SER  R30
	SER  R31
	LDI  R22,0x7F
	LDI  R23,0x7F
	POP  R21
	RET

__MULF12:
	PUSH R21
	RCALL __UNPACK
	CPI  R23,0x80
	BREQ __ZERORES
	CPI  R25,0x80
	BREQ __ZERORES
	EOR  R0,R1
	SEC
	ADC  R23,R25
	BRVC __MULF124
	BRLT __ZERORES
__MULF125:
	TST  R0
	BRMI __MINRES
	RJMP __MAXRES
__MULF124:
	PUSH R0
	PUSH R17
	PUSH R18
	PUSH R19
	PUSH R20
	CLR  R17
	CLR  R18
	CLR  R25
	MUL  R22,R24
	MOVW R20,R0
	MUL  R24,R31
	MOV  R19,R0
	ADD  R20,R1
	ADC  R21,R25
	MUL  R22,R27
	ADD  R19,R0
	ADC  R20,R1
	ADC  R21,R25
	MUL  R24,R30
	RCALL __MULF126
	MUL  R27,R31
	RCALL __MULF126
	MUL  R22,R26
	RCALL __MULF126
	MUL  R27,R30
	RCALL __MULF127
	MUL  R26,R31
	RCALL __MULF127
	MUL  R26,R30
	ADD  R17,R1
	ADC  R18,R25
	ADC  R19,R25
	ADC  R20,R25
	ADC  R21,R25
	MOV  R30,R19
	MOV  R31,R20
	MOV  R22,R21
	MOV  R21,R18
	POP  R20
	POP  R19
	POP  R18
	POP  R17
	POP  R0
	TST  R22
	BRMI __MULF122
	LSL  R21
	ROL  R30
	ROL  R31
	ROL  R22
	RJMP __MULF123
__MULF122:
	INC  R23
	BRVS __MULF125
__MULF123:
	RCALL __ROUND_REPACK
	POP  R21
	RET

__MULF127:
	ADD  R17,R0
	ADC  R18,R1
	ADC  R19,R25
	RJMP __MULF128
__MULF126:
	ADD  R18,R0
	ADC  R19,R1
__MULF128:
	ADC  R20,R25
	ADC  R21,R25
	RET

__DIVF21:
	PUSH R21
	RCALL __UNPACK
	CPI  R23,0x80
	BRNE __DIVF210
	TST  R1
__DIVF211:
	BRPL __DIVF219
	RJMP __MINRES
__DIVF219:
	RJMP __MAXRES
__DIVF210:
	CPI  R25,0x80
	BRNE __DIVF218
__DIVF217:
	RJMP __ZERORES
__DIVF218:
	EOR  R0,R1
	SEC
	SBC  R25,R23
	BRVC __DIVF216
	BRLT __DIVF217
	TST  R0
	RJMP __DIVF211
__DIVF216:
	MOV  R23,R25
	PUSH R17
	PUSH R18
	PUSH R19
	PUSH R20
	CLR  R1
	CLR  R17
	CLR  R18
	CLR  R19
	CLR  R20
	CLR  R21
	LDI  R25,32
__DIVF212:
	CP   R26,R30
	CPC  R27,R31
	CPC  R24,R22
	CPC  R20,R17
	BRLO __DIVF213
	SUB  R26,R30
	SBC  R27,R31
	SBC  R24,R22
	SBC  R20,R17
	SEC
	RJMP __DIVF214
__DIVF213:
	CLC
__DIVF214:
	ROL  R21
	ROL  R18
	ROL  R19
	ROL  R1
	ROL  R26
	ROL  R27
	ROL  R24
	ROL  R20
	DEC  R25
	BRNE __DIVF212
	MOVW R30,R18
	MOV  R22,R1
	POP  R20
	POP  R19
	POP  R18
	POP  R17
	TST  R22
	BRMI __DIVF215
	LSL  R21
	ROL  R30
	ROL  R31
	ROL  R22
	DEC  R23
	BRVS __DIVF217
__DIVF215:
	RCALL __ROUND_REPACK
	POP  R21
	RET

__CMPF12:
	TST  R25
	BRMI __CMPF120
	TST  R23
	BRMI __CMPF121
	CP   R25,R23
	BRLO __CMPF122
	BRNE __CMPF121
	CP   R26,R30
	CPC  R27,R31
	CPC  R24,R22
	BRLO __CMPF122
	BREQ __CMPF123
__CMPF121:
	CLZ
	CLC
	RET
__CMPF122:
	CLZ
	SEC
	RET
__CMPF123:
	SEZ
	CLC
	RET
__CMPF120:
	TST  R23
	BRPL __CMPF122
	CP   R25,R23
	BRLO __CMPF121
	BRNE __CMPF122
	CP   R30,R26
	CPC  R31,R27
	CPC  R22,R24
	BRLO __CMPF122
	BREQ __CMPF123
	RJMP __CMPF121

;END OF CODE MARKER
__END_OF_CODE:
