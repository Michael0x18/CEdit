#ifndef font_h
#define font_h

struct x4_font{
    uint8_t char_width;
    uint8_t char_height;
    
};

/*
 * Font storage method:
 * Fonts are stored as an array, 256 entries in size, of font characters.
 * Each font character is a two dimensional array of uint8_t elements.
 * Each element holds holds font data (including color) for two pixels.
 * Note that this means the font height must be even.
*/

#endif /*font_h*/
