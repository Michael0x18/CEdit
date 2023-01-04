include 'ti84pceg.inc'
include 'spi.inc'

	assume adl=1
	section .text

	section .data

public _x4_Buffer
_x4_Buffer	:=	ti.mpLcdLpbase
;	_x4_Buffer	dl	ti.vRam

public _x4_PrevScrBuffer
_x4_PrevScrBuffer	dl	ti.vRam

; Misc memory location 0
public _x4_d0
_x4_d0			dl	0

; Misc memory location 1
public _x4_d1
_x4_d1			dl	0

; Misc memory location 2
public _x4_d2
_x4_d2			dl	0

public _x4_d3
_x4_d3			dl	0

public _x4_d4
 _x4_d4		dl	0

public _x4_ScrLoc
_x4_ScrLoc	dl	0