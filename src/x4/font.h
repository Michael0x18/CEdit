#ifndef font_h
#define font_h

#include <stdio.h>
#include <stdlib.h>
#include <tice.h>
#include <keypadc.h>
#include <graphx.h>
#include <string.h>

#include "libx4.h"

/*
 * Font storage method:
 * Fonts are stored as an array, 128 entries in size, of font characters.
 * Each font character is a two dimensional array of uint8_t elements.
 * Each element holds holds font data (including color) for two pixels.
 * Note that this means the font height must be even.
 */

/*
 * Unpacks the default font into the font buffer
 */
void x4_load_default_font(uint8_t font_buffer[128][8][8], uint8_t fg, uint8_t bg);

// TODO
/*
 * Draws a character at x,y, with color c.
 * Only supports drawing the character starting at an even row
 */
void x4_PutChar(uint8_t font_buffer[128][8][8], int x, int y, char ch);

void x4_PutStr(uint8_t font_buffer[128][8][8], int x, int y, char *str);

#endif /*font_h*/
