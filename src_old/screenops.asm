include 'ti84pceg.inc'
include 'spi.inc'

	assume adl=1
	section .text

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

;TODO returns the current screen location
public _x4_GetScreenLocation
_x4_GetScreenLocation:
	ld	hl,(_x4_ScrLoc)
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
		ld	(_x4_ScrLoc),bc					; Stash the new screen location
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

; dest, src,
public _x4_Copy8Bytes
_x4_Copy8Bytes:
	pop		bc
	pop		de
	ex 		(sp), hl
	push	de
	push	bc
	ld		bc,8
	ldir
	ret

; Primitive sprite routine
; As the name says, written by calc84maniac
public _calc84maniac_Copy8x8
_calc84maniac_Copy8x8:
    pop bc
    pop de
    ex (sp),hl
    push de
    push bc
    ld bc,8
    ld a,c
.loop:
    ldir
    ex de,hl
    ld c,120-8
    add hl,bc
    ex de,hl
    ld c,8
    dec a
    jr nz,.loop
    ret

extern _x4_Buffer
extern _x4_PrevScrBuffer
extern _x4_ScrLoc

