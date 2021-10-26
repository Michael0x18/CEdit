;       LIBX4 is a statically linked library containing
;       4bpp routines
;
;       License is LGPL
;       Michael0x18, beckadamtheinventor
;
include 'ti84pceg.inc'
include 'spi.asm'

; void x4_Begin(void)
public _x4_Begin
_x4_Begin:
	ld	a,ti.lcdBpp4
	ld	(ti.mpLcdCtrl), a
	spi	$36, $2c		;Do mysterious spi stuff to get it in column-major mode
	spi	$2a, 0,0, 0,$ef
	spi	$2b, 0,0, 1,$3f
	ret

public _x4_LoadDefaultPalette
_x4_LoadDefaultPalette:
	ld	hl, _x4_DefaulPaletteData	; default palette entries
	ld	de, ti.mpLcdPalette	; lcd palette entries
	ld	bc, 16
	ldir
	ret

public _x4_End
_x4_End:
	spi	$2a, 0,0, 1,$3f
	spi	$2b, 0,0, 0,$ef
	spi	$36, $08
	ld	a, ti.lcdBpp16
	ld 	(ti.mpLcdCtrl), a
	ret

; Clears the screen. Takes the color to use on the top of the stack
public _x4_FillScreen
_x4_FillScreen:
	pop	bc
	ex	(sp), hl
	push	bc
; pack 4bpp color into 8 bits
	ld	a, l	; a = color
	and	a, $F	; a &= 0b1111
	ld	l, a	; color &= 0b1111
	add	a, a	; a += a
	add	a, a	; a += a
	add	a, a	; a += a
	add	a, a	; a += a
	add	a, l	; a += color
	ld	hl, (_x4_Buffer)
	ld	de, (_x4_Buffer)
	inc	de
	ld	bc, 38400 - 1
	ld	(hl), a
	ldir
	ret

; Fast copy a buffer from src to dest, order is dest then src, so read src first
public _x4_BlitBuffer
_x4_BlitBuffer:
	pop	bc,de
	ex	(sp),hl
	push	de,bc
	ld	bc,38400
	ldir
	ret

; Returns the current drawing location
public _x4_GetDrawLocation
_x4_GetDrawLocation:
	ld	hl,_x4_Buffer
	ret

; Sets the current drawing location. Takes in a buffer
public _x4_SetDrawLocation
_x4_SetDrawLocation:
	pop	de
	ex	(sp),hl
	ld	(_x4_Buffer),hl
	ex	hl,de
	jp	(hl)

public _x4_SetScreenLocation
_x4_SetScreenLocation:
	pop	de
	ex	(sp),hl
	ld	(ti.mpLcdBase),hl
	ex	hl,de
	jp	(hl)

section .data
; Palette data
public _x4_DefaulPaletteData
_x4_DefaulPaletteData:
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



; The currently active drawing buffer.
public _x4_Buffer
	_x4_Buffer dl ti.vRam
