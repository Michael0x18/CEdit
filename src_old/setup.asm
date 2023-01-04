include 'ti84pceg.inc'
include 'spi.inc'

	assume adl=1
	section .text

; Sets up the screen in 4bpp, column major mode
; void x4_Begin(void)
public _x4_Begin
_x4_Begin:
	;ei
	call ti.boot.InitializeHardware
	ld	a,ti.lcdBpp4
	ld	(ti.mpLcdCtrl), a
	spi	$36, $2c		;Do mysterious spi stuff to get it in column-major mode
	spi	$2a, 0,0, 0,$ef
	spi	$2b, 0,0, 1,$3f
        ld      hl,ti.mpLcdCtrl+1
        set     12,(hl-1)
        set     13,(hl-1)
	ld	hl,ti.vRam
	ld	(_x4_Buffer),hl
	;ld	hl,(_x4_Buffer)
	ret


public _x4_LoadDefaultPalette
_x4_LoadDefaultPalette:
	ld	hl, _x4_DefaultPaletteData	; default palette entries
	ld	de, ti.mpLcdPalette	; lcd palette entries
	ld	bc, 16 * word
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

extern __frameset
extern _x4_Buffer
extern _x4_DefaultPaletteData