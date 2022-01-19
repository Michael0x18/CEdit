;       LIBX4 is a statically linked library containing
;       4bpp routines
;
;       License is LGPL
;       Michael0x18, beckadamtheinventor
;
include 'ti84pceg.inc'
include 'spi.asm'

; Sets up the screen in 4bpp, column major mode
; void x4_Begin(void)
public _x4_Begin
_x4_Begin:
	;ei
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
	ld	hl, _x4_DefaulPaletteData	; default palette entries
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

public _x4_FillScreen_nocheck
_x4_FillScreen_nocheck:
	pop	bc
	ex	(sp),hl
	push	bc
	ld	a, l
	jq	_x4_FillScreen.entry

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
.entry:
	ld	hl, (_x4_Buffer)
	ld	de, (_x4_Buffer)
	inc	de
	ld	bc, 38400 - 1
	ld	(hl), a
	ldir
	ret

; copy a buffer from src to dest, order is dest then src, so read src first
public _x4_BlitBuffer
_x4_BlitBuffer:
	pop	bc,de
	ex (sp),hl
	push	de,bc
	ld	bc,38400
	ldir
	ret

; Returns the current drawing location
public _x4_GetDrawLocation
_x4_GetDrawLocation:
	ld	hl,(_x4_Buffer)
	ret

; Sets the current drawing location. Takes in a buffer
; TODO make this wait for hw to finish moving buffer to
; GRAM only if the buffer passed in is the same as the
; one being displayed
public _x4_SetDrawLocation
_x4_SetDrawLocation:
	pop	de				; Pop the return address
	ex	(sp),hl				; Read the argument into hl
	push	de				; Restore the stack
	;Pre-check
	;ld	hl,(ti.mpLcdRis)
	;and	hl,ti.lcdIntVcomp

	;Make the check
	ld	de,(_x4_PrevScrBuffer)		; Load previous buffer into de
	push	hl				; Put hl back onto the stack,
	or	a,a				; Reset carry
	sbc	hl,de				; Test for equality
	jq	nz,.skip			; Jump if not equal
	;Vcomp
	;mpLcdRis & lcdIntVcomp
	;ld hl,ti.mpLcdRis
	;bit ti.bLcdIntVcomp,(hl)
	;jq	nz,.skip
	;Waiting for dma
	ld	hl,(_x4_PrevScrBuffer)		; Load buffer address into hl
	ld	bc,38400			; Stick size of buffer in bc
	add	hl,bc				; Add to hl
	push	hl				; Put hl on stack				;TODO fix this, it's stupid
	pop	bc				; Pop to bc
.loop:	; The main wait loop
	ld	hl,ti.mpLcdRis
	bit	ti.bLcdIntVcomp, (hl)
	jq	nz,.skip
	ld	hl,(ti.mpLcdCurr)		; Load the cursor into hl
	or	a,a				; Reset carry
	sbc	hl,bc				; Test
	jq	c,.loop				; Jump if <
.skip:
	pop	bc				; Pop bc back
	ld	(_x4_Buffer),bc			; Set the draw location
	ret

; DONE make this wait for stuff
public _x4_SetScreenLocation
_x4_SetScreenLocation:
        ; Arguments
        pop     de							; Pop the return address
        pop     bc							; Pop the new pointer
        push    bc							; Restore the stack
        push    de							; 
        ; Wait
        ld      hl,ti.mpLcdRis
.loop:
        bit     ti.bLcdIntLNBU,(hl)
        jq      z,.loop
        ; Set
        ld      de,(ti.mpLcdBase)
        ld      (_x4_PrevScrBuffer),de
        ld      (ti.mpLcdBase),bc
        ; End
        ld      hl,ti.mpLcdIcr
        ld      (hl), ti.lcdIntLNBU or ti.lcdIntVcomp
        ret
; x4_FastVertLine(x,y,len,c)
;_x4_FastVertLine:
;	;; TODO
;	ld	hl,-ti.stack_size
;	call	__frameset
;	ld	bc,(ix+6)
;	ld	de,(ix+9)
;	ret

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
	jr	z,.skip		;Shift if the offset is odd
	ex	de,hl
	repeat 4
		add	hl,hl
	end repeat
	ex	de,hl
.skip:				;Write the pixel
	;Current state:
	; HL contains the offset
	; BC is scratch register
	; DE contains the byte to write
	ld	bc, (_x4_Buffer)
	add	hl, bc		; BC is still scratch
	ld	a,(hl)
	and	d
	or	e
	ld	(hl),a
	ret


section .data
; The currently active drawing buffer.
public _x4_Buffer
	_x4_Buffer	:=	ti.mpLcdLpbase
;	_x4_Buffer	dl	ti.vRam

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

extern __frameset;
include 'font.asm'
