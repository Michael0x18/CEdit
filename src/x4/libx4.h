#ifndef libx4_h
#define libx4_h

#include "libx4_constants.h"
#include "font.h"

#define fixfactor 64

extern void *x4_Buffer;

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
void x4_BlitBuffer(void* dest, void* src);

/*
 * Draws a pixel to the screen, at the point x,y, with color c
 */
void x4_PutPixel(int24_t x, int24_t y, int24_t c);

//TODO implement this
extern void x4_VertLine(int,int,int,int);
extern void x4_HorizLine(int,int,int,int);
void x4_FillRectangle(int x, int y, int width, int height, int c){
	for(int i = 0; i < width; i++){
		x4_VertLine(x+i,y,height,c);
	}
}

void x4_Rectangle(int x, int y, int width, int height, int c){
	x4_VertLine(x,y,height,c);
	x4_VertLine(x+width-1,y,height,c);
	x4_HorizLine(x,y,width,c);
	x4_HorizLine(x,y+height-1,width,c);
}


/*
 * EFLA routine
 */
void x4_Line(int x, int y, int x2, int y2, int c)
{
	bool yl = 0;
	int sl = y2 - y;
	int ll = x2 - x;
	if (abs(sl) > abs(ll))
	{
		int tmp = sl;
		sl = ll;
		ll = tmp;
		yl = 1;
	}
	int24_t end = ll;
	int24_t inc = 0;
	if (ll < 0)
	{
		inc = -1;
		ll = -ll;
	}
	else
		inc = 1;
	//fix
	int dec;
	if (ll == 0)
		dec = sl * fixfactor;
	else
		dec = fixfactor * sl / ll;
	int j = 0; //fix
	if (yl)
	{
		for (int i = 0; i != end; i += inc)
		{
			x4_PutPixel(x + (j / fixfactor), y + i, c);
			j += dec;
		}
	}
	else
	{
		for (int i = 0; i != end; i += inc)
		{
			x4_PutPixel(x + i, y + (j / fixfactor), c);
			j += dec;
		}
	}
	x4_PutPixel(x2, y2, c);
}

/*
 * Vertical line - very fast routine *cough cough*
 * TODO
 */
void x4_VertLine(int x, int y, int len, int c){
	for(int i = 0; i < len; i++){
		x4_PutPixel(x,y+i,c);
	}
}

/*
 * Horizontal line - not as fast
 * TODO
 */
void x4_HorizLine(int x, int y, int len, int c){
	for(int i = 0; i < len; i++){
		x4_PutPixel(x+i,y,c);
	}
}

//TODO implement this
void x4_Circle(int x, int y, int r, int c);

void x4_FillCircle(int x, int y, int r, int c){
	//(x-h)^2+(y-k)^2<=r^2 -> draw or no draw
	for(int x1 = x-r; x1 <= x+r; x1++){
		for(int y1 = y-r; y1 <=y+r; y1++){
			if((x1-x)*(x1-x)+(y1-y)*(y1-y)<= r*r){
				x4_PutPixel(x1,y1,c);
			}
		}
	}
}

//TODO
/*
 * Draws a character at x,y, with color c
 */
void x4_PutChar(int x, int y, char ch, int color){
	
}


#endif /*libx4.h*/
