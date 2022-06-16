#ifndef font_h
#define font_h

#include <stdio.h>
#include <stdlib.h>
#include <tice.h>
#include <keypadc.h>
#include <graphx.h>
#include <string.h>

#include "cedit.h"

struct x4_font{
    uint8_t char_width;
    uint8_t char_height;
    uint8_t *font_data;
};

/*
 * Font storage method:
 * Fonts are stored as an array, 256 entries in size, of font characters.
 * Each font character is a two dimensional array of uint8_t elements.
 * Each element holds holds font data (including color) for two pixels.
 * Note that this means the font height must be even.
*/

struct x4_font get_default_font(void);

#endif /*font_h*/
