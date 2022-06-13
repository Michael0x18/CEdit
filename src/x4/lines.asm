include 'ti84pceg.inc'
include 'spi.inc'

    assume adl=1
    section .text

;public _x4_VertLine
;_x4_VertLine:
;	.x	:=	ix+6
;	.y	:=	ix+9
;	.l	:=	ix+12
;	.c	:=	ix+15
;	ld	hl,	-18
;	call	__frameset
;	ld	hl,	(.x)
;	ld	bc,	(.y)
;	ld	de,	(.c)
;	call	_x4_PutPixel_Internal
;		; One pixel put at the base offset
;		; Side effect: hl is the right offset
;	push	hl
;	pop	de
;	inc	de
;	ld	bc,	(.l)
;	ldir
;	ld	sp,ix
;	pop	ix
;	ret
;
;public _x4_HorizLine
;_x4_HorizLine:
;	ret
;
extern _x4_Buffer
extern __frameset
extern _x4_PutPixel_Internal
