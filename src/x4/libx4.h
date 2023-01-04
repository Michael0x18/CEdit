#ifndef libx4_h
#define libx4_h

#include "libx4_constants.h"
#include "font.h"

#define fixfactor 64

extern void *x4_Buffer;

void x4_Copy8Bytes(void *dest, void *src);

void calc84maniac_Copy8x8(void *dest, void *src);

/**
 * Copy an 8x16 area onto the screen
 */
void x4_Copy8x8(uint24_t x, uint24_t y, void *src);

uint24_t x4_GetPixelAddress(int24_t x, int24_t y);

/*
 * Sets up the 4bpp drawing
 * Note: You need to call the palette setting,
 * vram clearing, and draw location stuff
 * separately. This is meant to give the user
 * the greatest amount of control over what goes
 * on during setup.
 *
 * A normal (default) setup will look like this:
 * x4_Begin();
 * x4_LoadDefaultPalette();
 * x4_SetDrawLocation(X4_BUFFER_1);
 * x4_FillScreen(0);
 * ...
 * x4_End();
 */
void x4_Begin(void);

/*
 * Restores OS defaults
 *
 */
void x4_End(void);

/*
 * Color may only be between 0 and 15,
 * inclusive.
 */
void x4_FillScreen(int8_t color);

/*
 * Loads the default palette, which consists
 * of the same colors as the TIOS palette, but
 * in a different order
 */
void x4_LoadDefaultPalette(void);

/*
 * Returns the address ofd the drawing location.
 */
void *x4_GetDrawLocation(void);

/*
 * Sets the draw location to this address.
 */
void x4_SetDrawLocation(void *addr);

/*
 * Sets the location of the screen.
 */
void x4_SetScreenLocation(void *addr);

/*
 * Returns the location of the screen
 */
void *x4_GetScreenLocation(void);

/*
 * Copies 38400 bytes from src into dest
 */
void x4_BlitBuffer(void *dest, void *src);

/*
 * Draws a pixel to the screen, at the point x,y, with color c
 */
void x4_PutPixel(int24_t x, int24_t y, int24_t c);

void x4_Line_EFLA(int x, int y, int x2, int y2, int c);

void x4_VertLine(int x, int y, int len, int c);

void x4_HorizLine(int x, int y, int len, int c);

// TODO implement this
void x4_Circle(int x, int y, int r, int c);

void x4_FillCircle(int x, int y, int r, int c);

void x4_FillRectangle(int x, int y, int width, int height, int c);

void x4_Rectangle(int x, int y, int width, int height, int c);

/**
 * Draw an 8x8 sprite onto the screen
 * x - X coordinate to draw to
 * y - Y coordinate to draw to
 * src - 4x8byte array, used as source for sprite
 */
void x4_Sprt8(int24_t x, int24_t y, void *src);

#endif /*libx4.h*/
