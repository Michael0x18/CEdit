include 'x4/ti84pceg.inc'
include 'x4/spi.inc'

	assume adl=1
	section .text



section .data

extern _x4_Buffer
extern _x4_PrevScrBuffer
extern _x4_ScrLoc
extern __frameset
extern _x4_PutStr
extern _x4_Copy8x8
extern _x4_Copy8Bytes
