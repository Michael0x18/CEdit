#ifndef general_h
#define general_h

#include <stdio.h>
#include <stdlib.h>
#include <tice.h>
#include <keypadc.h>
#include <graphx.h>
#include <string.h>

/**
 * general.h contains definitions for general purpose sub
 */
#include "../macros.h"
#include "../libx4_constants.h"

/**
 * Initializes x4
 * Puts the screen in column major mode and switches
 * to 4bpp.
 *
 * Does not clear vram, initialize palette, or initialize
 * drawing buffers. These must be done manually
 *
 * Normal (default) setup will consist of the following
 * steps:
 *
 * x4_Begin();
 * x4_LoadDefaultPalette();
 * x4_SetDrawLocation(X4_BUFFER_1);
 * x4_FillScreen(0);
 * ...
 * x4_SetScreenLocation(X4_BUFFER_0);
 * x4_End();
 */
void x4_Begin(void);

/**
 * Restores OS defaults for screen
 * (Row major and 16bpp)
 * Does not clear vram and/or set the screen back.
 * You will need to do this manually.
 *
 * See doc for x4_Begin(void) for more details.
 */
void x4_End(void);

/**
 * Returns the address of the location libx4 will use
 * to draw.
 *
 * It is recommended to directly use X4_DRAW_LOCATION instead.
 * This avoids a call and lets it be inlined
 */
void *x4_GetDrawLocation(void);

/**
 * Sets the location libx4 will use to draw. This should
 * usually be one of the X4_BUFFER_* macros.
 *
 * If not, it should be at least 38400 bytes in size.
 */
void x4_SetDrawLocation(void *addr);

/**
 * Sets the screen location that the LCD controller will
 * use to display. In general, should be one of the X4_BUFFER_*
 * macros.
 *
 * If not, it should be at least 38400 bytes in size.
 */
void x4_SetScreenLocation(void *addr);

/**
 * Returns the location that the screen is currently being
 * driven from.
 *
 * It is recommended to directly use X4_SCREEN_LOCATION instead
 * This avoids a call and lets it be inlined
 */
void *x4_GetScreenLocation(void);

/**
 * Loads the default palette, which consists of TIOS colors
 * but in a different order:
 * 0	Black
 * 1	DrkGray
 * 2	Gray
 * 3	MedGray
 * 4	LtGray
 * 5	White
 * 6	Blue
 * 7	Green
 * 8	Red
 * 9	Navy
 * A	LtBlue
 * B	Yellow
 * C	Magenta
 * D	Orange
 * E	Brown
 * F	White (duplicated)
 */
void x4_LoadDefaultPalette(void);

/**
 * Copies 38400 bytes from src into dest
 */
void x4_BlitBuffer(void *dest, void *src);

/**
 * Color may only be between 0 and 15,
 * inclusive. It is recommended to use the
 * prepacked version of this subroutine
 * instead, as it's faster and smaller.
 */
void x4_FillScreen(uint8_t color);

/**
 * Color may only be an 8 bit integer with the
 * following format:
 * XX
 * Where X is a number in hexadecimal.
 * In short, the last four bits must be the same
 * as the first four. This is because it doesn't
 * pack the 4 bit color into 8 bits, instead
 * relying on it being done at compile time. The
 * X4_PACK_4_TO_8(x) macro is provided for convenience.
 * (please use optimization of some sort or the macro
 * won't work)
 */
void x4_FillScreen_PrePacked(uint8_t color);

void x4_SlideBuffer_FromRight(void *dest, void *src);
void x4_SlideBuffer_FromLeft(void *dest, void *src);
void x4_SlideBuffer_FromTop(void *dest, void *src);
void x4_SlideBuffer_FromBottom(void *dest, void *src);

// TODO these four
void x4_SlideBuffer_FromRight_sync(void *dest, void *scratch, void *src);
void x4_SlideBuffer_FromLeft_sync(void *dest, void *scratch, void *src);
void x4_SlideBuffer_FromTop_sync(void *dest, void *scratch, void *src);
void x4_SlideBuffer_FromBottom_sync(void *dest, void *scratch, void *src);

#endif /*general_h*/