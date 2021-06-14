#include "fonts.h"

/* This contains the raw data for the font. */
static const uint8_t dr_mono_data[] = {
    #include "drmono-10-normal.inc"
};
/* However, C89 does not allow us to typecast a byte array into a
fontlib_font_t pointer directly, so we have to use a second statement to do it,
though helpfully we can at least do it in the global scope. */
const fontlib_font_t *dr_mono = (fontlib_font_t *)dr_mono_data;
