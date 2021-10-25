;       LIBX4 is a statically linked library containing
;       4bpp routines
;
;       License is LGPL
;       Michael0x18
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
	ld	hl, $0000							;Black
	ld	(ti.mpLcdPalette + 0 * word), hl
	ld	hl, $A94A							;Dark Gray
	ld	(ti.mpLcdPalette + 1 * word), hl	
	ld	hl, $4631							;Gray
	ld	(ti.mpLcdPalette + 2 * word), hl
	ld	hl, $6318							;MedGray
	ld	(ti.mpLcdPalette + 3 * word), hl
	ld	hl, $739C							;LtGray
	ld	(ti.mpLcdPalette + 4 * word), hl
	ld	hl, $FFFF							;White
	ld	(ti.mpLcdPalette + 5 * word), hl
	ld	hl, $1F								;Blue
	ld	(ti.mpLcdPalette + 6 * word), hl
	ld	hl, $8260							;Green
	ld	(ti.mpLcdPalette + 7 * word), hl
	ld	hl, $7C00							;Red
	ld	(ti.mpLcdPalette + 8 * word), hl
	ld	hl, $10								;Navy
	ld	(ti.mpLcdPalette + 9 * word), hl
	ld	hl, $25F							;LtBlue
	ld	(ti.mpLcdPalette + 10 * word), hl
	ld	hl, $FFE0							;Yellow
	ld	(ti.mpLcdPalette + 11 * word), hl
	ld	hl, $7C1F							;Magenta
	ld	(ti.mpLcdPalette + 12 * word), hl
	ld	hl, $FE05							;Orange
	ld	(ti.mpLcdPalette + 13 * word), hl
	ld	hl, $5880							;Brown
	ld	(ti.mpLcdPalette + 14 * word), hl
	ld	hl, $FFFF							;White2
	ld	(ti.mpLcdPalette + 15 * word), hl
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
	ld	hl,3
	add	hl,sp
	ld	a,(hl)
	ld	hl, (x4_Buffer)
	ld	de, (x4_Buffer)
	inc	de
	ld	bc, 38400 - 1
	ld	(hl), a
	rld
	ldir
	ret

; Fast copy a buffer from src to dest, order is dest then src, so read src first
public _x4_BlitBuffer
_x4_BlitBuffer:
	ld	hl,3
	add	hl,sp
	ld	de,(hl)
	inc	hl
	inc	hl
	inc	hl
	ld	hl,(hl)
	ld	bc,38400
	ldir
	ret

; Returns the current drawing location
public _x4_GetDrawLocation
_x4_GetDrawLocation:
	ld	hl,x4_Buffer
	ret

; Sets the current drawing location. Takes in a buffer
public _x4_SetDrawLocation
_x4_SetDrawLocation:
	ld	hl,3
	add	hl,sp
	ld	bc, (hl)
	ld	(x4_Buffer),bc
	ret

public _x4_SetScreenLocation
_x4_SetScreenLocation:
	ld	hl,3
	add	hl,sp
	ld	bc, (hl)
	ld	(ti.mpLcdBase),bc
	ret

section .data
; The currently active drawing buffer.
private x4_Buffer
	x4_Buffer dl ti.vRam
