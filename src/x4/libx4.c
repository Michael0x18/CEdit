#include "libx4.h"

/*
 * EFLA routine
 */
void x4_Line_EFLA(int x, int y, int x2, int y2, int c)
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