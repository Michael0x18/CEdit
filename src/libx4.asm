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
    ld a,ti.lcdBpp4
    ld (ti.mpLcdCtrl), a
    spi	$36, $2c		;Do mysterious spi stuff to get it in column-major mode
	spi	$2a, 0,0, 0,$ef
	spi	$2b, 0,0, 1,$3f
	ret

public _x4_LoadDefaultPalette
_x4_LoadDefaultPalette:
	ld	hl, $0000
	ld	(ti.mpLcdPalette + 0 * word), hl
	ld	hl, $001F
	ld	(ti.mpLcdPalette + 1 * word), hl
	ld	hl, $7C00
	ld	(ti.mpLcdPalette + 2 * word), hl
	ld	hl, $03E0
	ld	(ti.mpLcdPalette + 3 * word), hl
	ret

public _x4_End
_x4_End:
    spi $2a, 0,0, 1,$3f
	spi $2b, 0,0, 0,$ef
	spi $36, $08
	ld	a, ti.lcdBpp16
	ld 	(ti.mpLcdCtrl), a
	ret

; Clears the screen. Takes the color to use on the top of the stack
public _x4_FillScreen
_x4_FillScreen:
	ld hl,3
	add hl,sp
	ld	a,(hl)
	ld	hl, ti.vRam
	ld	de, ti.vRam + 1
	ld	bc, 38400 - 1
	ld	(hl), a
	ldir
	ret

