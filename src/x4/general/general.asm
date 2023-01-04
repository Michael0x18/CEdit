include '../ti84pceg.inc'

	assume adl=1
	section .text

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
	pop	de					; Pop the return address
	ex	(sp),hl				; Read the argument into hl
	push	de				; Restore the stack
	;Pre-check
	;ld	hl,(ti.mpLcdRis)
	;and	hl,ti.lcdIntVcomp

	;Check if we are setting to what was the previous screen
	ld	de,(_x4_PrevScrBuffer)		; Load previous buffer into de
	push	hl						; Put hl back onto the stack,
	or	a,a							; Reset carry
	sbc	hl,de						; Test for equality
	jq	nz,.skip					; Jump if not equal - don't need
									; to wait for draw if it wasn't drawn 
									; 😶
	;Vcomp
	;mpLcdRis & lcdIntVcomp
	;ld hl,ti.mpLcdRis
	;bit ti.bLcdIntVcomp,(hl)
	;jq	nz,.skip
	;Waiting for dma
	ld	hl,(_x4_PrevScrBuffer)		; Load buffer address into hl
	ld	bc,38400
	add	hl,bc						; hl is now end of buffer
	ex	de,hl							; swap hl to bc
.loop:	; The main wait loop
	ld	hl,ti.mpLcdRis
	bit	ti.bLcdIntVcomp, (hl)
	jq	nz,.skip
	ld	hl,(ti.mpLcdCurr)		; Load the cursor into hl
	or	a,a				; Reset carry
	sbc	hl,bc				; Test
	jq	c,.loop				; Jump if <
.skip:
	pop	bc				; Pop original argument back
	ld	(_x4_Buffer),bc			; Set the draw location
	ret

public _x4_GetScreenLocation
_x4_GetScreenLocation:
	ld	hl,(ti.mpLcdBase)
	ret

public _x4_SetScreenLocation
_x4_SetScreenLocation:
        ; Arguments
        pop     de							; Pop the return address
        pop     bc							; Pop the new pointer
		;ld	(_x4_ScrLoc),bc					; Stash the new screen location
        push    bc							; Restore the stack
        push    de							; 
        ; Wait
        ld      hl,ti.mpLcdRis
.loop:
        bit     ti.bLcdIntLNBU,(hl)
        jq      z,.loop
        ; Set
        ld      de,(ti.mpLcdBase)
        ld      (_x4_PrevScrBuffer),de		; Swap to previous buffer
        ld      (ti.mpLcdBase),bc
        ; End
        ld      hl,ti.mpLcdIcr
        ld      (hl), ti.lcdIntLNBU or ti.lcdIntVcomp
        ret

public _x4_BlitBuffer
_x4_BlitBuffer:
	pop	bc,de
	ex (sp),hl
	push	de,bc
	ld	bc,38400
	ldir
	ret

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

public _x4_FillScreen_PrePacked
_x4_FillScreen_PrePacked:
	pop	bc
	ex	(sp),hl
	push	bc
	ld	a, l
	jq	_x4_FillScreen.entry
	

extern _x4_Buffer
extern _x4_PrevScrBuffer