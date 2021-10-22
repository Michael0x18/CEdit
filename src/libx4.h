#ifndef libx4_h
#define libx4

/*
 * Sets up the 4bpp drawing  
 * 
 */
void x4_Begin(void);

/*
 * Restores OS defaults  
 * 
 */
void x4_Begin(void);

/*
 * Color may only be between 0 and 15,
 * inclusive.
 */
void x4_FillScreen(int8_t color);

void x4_LoadDefaultPalette(void);

#endif