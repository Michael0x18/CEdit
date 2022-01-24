;       LIBX4 is a statically linked library containing
;       4bpp routines
;
;       License is LGPL
;       Michael0x18, beckadamtheinventor
;

section .data
include 'ti84pceg.inc'
include 'spi.asm'
; The currently active drawing buffer.
public _x4_Buffer
_x4_Buffer	:=	ti.mpLcdLpbase
;	_x4_Buffer	dl	ti.vRam

; Palette data
public _x4_DefaultPaletteData
_x4_DefaultPaletteData:
	dw	$0000		;Black
	dw	$A94A		;Dark Gray
	dw	$4631		;Gray
	dw	$6318		;MedGray
	dw	$739C		;LtGray
	dw	$FFFF		;White
	dw	$001F		;Blue
	dw	$8260		;Green
	dw	$7C00		;Red
	dw	$0010		;Navy
	dw	$25F		;LtBlue
	dw	$FFE0		;Yellow
	dw	$7C1F		;Magenta
	dw	$FE05		;Orange
	dw	$5880		;Brown
	dw	$FFFF		;White2

public _x4_FontSpacing
_x4_FontSpacing	dl	default_font_spacing

public _x4_FontData
_x4_FontData	dl	default_font_data

public _x4_PrevScrBuffer
_x4_PrevScrBuffer	dl	ti.vRam

; General purpose data thingy. For when I run out of registers
public _x4_d0
_x4_d0			dl	0

; General purpose data thingy. For when I run out of registers
public _x4_d1
_x4_d1			dl	0

; General purpose data thingy. For when I run out of registers
public _x4_d2
_x4_d2			dl	0

public _x4_d3
_x4_d3			dl	0

public _x4_d4
 _x4_d4		dl	0

extern __frameset
include 'font.asm'
