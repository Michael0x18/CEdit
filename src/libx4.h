#ifndef libx4_h
#define libx4_h

#include "libx4_constants.h"

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
 * Returns the address of the drawing location.
 */
void* x4_GetDrawLocation(void);

/*
 * Sets the draw location to this address.
 */
void x4_SetDrawLocation(void* addr);

/*
 * Sets the location of the screen.
 */
void x4_SetScreenLocation(void* addr);

/*
 * Returns the location of the screen
 */
void* x4_GetScreenLocation(void);

/*
 * Literally just ldir, but with bc set to 38400.
 */
void x4_BlitBuffer(void* dest, void* src);

#endif
