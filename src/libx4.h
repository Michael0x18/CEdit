#ifndef libx4_h
#define libx4_h

#include "libx4_constants.h"

extern void* x4_Buffer;

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
 * Note: Return is broken
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
 * Note: Return is broken
 */
void* x4_GetScreenLocation(void);

/*
 * Literally just ldir, but with bc set to 38400.
 */
void x4_BlitBuffer(void* dest, void* src);

void x4_PutPixel(int x, int y, int c){
    int offset = x*120 + y/2;
    //int offset = y*160 + x/2;
    uint8_t mask;
    if(y%2==1){
        c<<=4;
        mask = 0b00001111;
    }else{
        mask = 0b11110000;
    }
    *((char*)x4_Buffer+offset)&=mask;
    *((char*)x4_Buffer+offset)|=c;
}

void x4_HorizLine(int x, int y, int len, int c){
	int offset = x*120 + y/2;
	uint8_t mask;
	if(y%2==1){
		c<<=4;
		mask=0b00001111;
	}else{
		mask=0b11110000;
	}
	for(int i = 0; i < len; i++){
		*((char*)x4_Buffer+offset)&=mask;
		*((char*)x4_Buffer+offset)|=c;
		offset+=120;
	}
}

#endif
