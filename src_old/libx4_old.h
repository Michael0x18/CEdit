#ifndef libx4_h
#define libx4_h

#include "libx4_constants.h"
#include "font.h"

extern void *x4_Buffer;

void x4_Copy8Bytes(void *dest, void *src);

void calc84maniac_Copy8x8(void *dest, void *src);

/**
 * Copy an 8x16 area onto the screen
 */
void x4_Copy8x8(uint24_t x, uint24_t y, void *src);

uint24_t x4_GetPixelAddress(int24_t x, int24_t y);

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
