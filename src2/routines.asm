include 'ti84pceg.inc'

ti.WaitShort = 00003B4h
ti.WaitLong  = 00003B8h

pSpiRange    = 0D000h
mpSpiRange   = 0F80000h
spiValid     = 8
pSpiValid    = pSpiRange + spiValid
mpSpiValid   = mpSpiRange + spiValid
spiStatus    = 12
pSpiStatus   = pSpiRange + spiStatus
mpSpiStatus  = mpSpiRange + spiStatus
spiData      = 24
pSpiData     = pSpiRange + spiData
mpSpiData    = mpSpiRange + spiData

lcd          = ti.vRam + 8
lcd.width    = ti.lcdWidth
lcd.height   = ti.lcdHeight
lcd.size     = lcd.width * lcd.height

;						;Jacobly's magic spi macro
macro spi cmd, params&
	ld	a, cmd
	call	spiCmd
	match any, params
		iterate param, any
			ld	a, param
			call	spiParam
		end iterate
	end match
end macro

; Puts the screen in 4bpp mode
public _b4_Begin
_b4_Begin:
	ld	a, ti.lcdBpp4
	ld	(ti.mpLcdCtrl), a
	spi	$36, $2c		;Do mysterious spi stuff to get it in column-major mode
	spi	$2a, 0,0, 0,$ef
	spi	$2b, 0,0, 1,$3f
	ret

public _b4_End
_b4_End:
	spi $2a, 0,0, 1,$3f
	spi $2b, 0,0, 0,$ef
	spi $36, $08
	ld	a, ti.lcdBpp16
	ld 	(ti.mpLcdCtrl), a
	ret

; Clears the screen. Takes the color to use on the top of the stack
public _b4_FillScreen
_b4_FillScreen:
	ld hl,3
	add hl,sp
	ld	a,(hl)
	ld	hl, ti.vRam
	ld	de, ti.vRam + 1
	ld	bc, 38400 - 1
	ld	(hl), a
	ldir
	ret

;x,y,len,color
public _b4_VertLine
_b4_VertLine:
	ret
	pop	bc	; x coordinate
	pop	de	; y coordinate




	;;;;;Jacobly's stuff

spiParam:
	scf
	virtual
		jr	nc, $
		load .jr_nc : byte from $$
	end virtual
	db	.jr_nc
spiCmd:
	or	a, a
	ld	hl, mpSpiData or spiValid shl 8
	ld	b, 3
.loop:	rla
	rla
	rla
	ld	(hl), a
	djnz	.loop
	ld	l, h
	ld	(hl), 1
.wait:	ld	l, spiStatus + 1
.wait1:	ld	a, (hl)
	and	a, $f0
	jr	nz, .wait1
	dec	l
.wait2:	bit	2, (hl)
	jr	nz, .wait2
	ld	l, h
	ld	(hl), a
	ret