;       LIBX4 is a statically linked library containing
;       4bpp routines
;
;       License is LGPL
;       Michael0x18, beckadamtheinventor
;
include 'ti84pceg.inc'
include 'spi.asm'



; x,y
; Returns offset hl, not including the buffer
; Does not computer even/odd offset
; Effectively computes x*120+y/2
public _x4_GetPixelAddress
_x4_GetPixelAddress:
	.x	:=	ix+6		; Pixel x position
	.y	:=	ix+9		; Pixel y position
	ld	hl,-12
	call	__frameset		; Frame is set up?		
	ld	hl, (.x)		; Get x into hl
	ld	bc, (.y)
	call	_x4_GetPixelAddress_Internal
	ld	sp,ix
	pop	ix
	ret;

; backend for _x4_GetPixelAddress, can be called from assembly
public _x4_GetPixelAddress_Internal
_x4_GetPixelAddress_Internal:
	bit	0,h
	ld	h,120
	jr	z,.skip
	ld	b,h
.skip:
	mlt	hl
	srl	c
	add	hl,bc
	ret;

; Write a pixel to the screen
; void _x4_PutPixel(int24_t x, int24_t y, int c)
public _x4_PutPixel
_x4_PutPixel:
	.x	:=	ix+6
	.y	:=	ix+9
	.c	:=	ix+12
	ld	hl, -15
	call	__frameset
	ld	hl, (.x)
	ld	bc, (.y)
	ld	de, (.c)
	call _x4_PutPixel_Internal
	ld	sp,ix
	pop	ix
	ret

; Internal function that puts pixel on screen
; hl	x
; bc	y
; de	c
public _x4_PutPixel_Internal
_x4_PutPixel_Internal:
	push	bc
	call	_x4_GetPixelAddress_Internal
	pop	bc
	bit	0, c
	ld	d,$F0
	jr	z,.skip		;Shift if the offset is odd
	ex	de,hl
	repeat 4
		add	hl,hl
	end repeat
	ex	de,hl
	ld	d,$0F
.skip:				;Write the pixel
	;Current state:
	; HL contains the offset
	; BC is scratch register
	; DE contains the byte to write
	ld	bc, (_x4_Buffer)
	add	hl, bc		; BC is still scratch
	ld	a,(hl)
	and	a,d
	or	a,e
	ld	(hl),a
	ret


section .data
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
