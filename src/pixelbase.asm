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

extern __frameset
extern _x4_Buffer