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
	if(len>0){
			for(int i = 0; i < len; i++){
			*((char*)x4_Buffer+offset)&=mask;
			*((char*)x4_Buffer+offset)|=c;
			offset+=120;
		}
	}else{
		for(int i = 0; i > len;i--){
			*((char*)x4_Buffer+offset)&=mask;
			*((char*)x4_Buffer+offset)|=c;
			offset-=120;
		}
	}	
}

//TODO implement this
void x4_Rectangle(int x, int y, int width, int height){
}


const int fixfactor = 64;
void x4_FastLine_Fix(int x, int y, int x2, int y2, int c) {
	bool yl=0;
	int sl=y2-y;
	int ll=x2-x;
	if (abs(sl)>abs(ll)) {
		int tmp=sl;
		sl=ll;
		ll=tmp;
		yl=1;
	}
	int24_t end=ll;
	int24_t inc=0;
	if (ll<0) {
		inc=-1;
		ll=-ll;
	} else inc=1;
	//fix
	int dec;
	if (ll==0) dec=sl*fixfactor;
	else dec=fixfactor*sl/ll;
	int j=0;//fix
	if (yl) {
		for (int i=0;i!=end;i+=inc) {
			x4_PutPixel(x+(j/fixfactor),y+i,c);
			j+=dec;
		}
	} else {
		for (int i=0;i!=end;i+=inc) {
			x4_PutPixel(x+i,y+(j/fixfactor),c);
			j+=dec;
		}
	}
	x4_PutPixel(x2,y2,c);
}




//EFLA type C fastline, adapted from the TIGCCLIB one
void x4_FastLine(int x, int y, int x2, int y2, int c) {
	bool yl=0;
	int sl=y2-y;
	int ll=x2-x;
	if (abs(sl)>abs(ll)) {
		int tmp=sl;
		sl=ll;
		ll=tmp;
		yl=1;
	}
	int24_t end=ll;
	int24_t inc=0;
	if (ll<0) {
		inc=-1;
		ll=-ll;
	} else inc=1;
	double dec;
	if (ll==0) dec=(double)sl;
	else dec=((double)sl/(double)ll);
	double j=0.0;
	if (yl) {
		for (int i=0;i!=end;i+=inc) {
			x4_PutPixel(x+(int)j,y+i,c);
			j+=dec;
		}
	} else {
		for (int i=0;i!=end;i+=inc) {
			x4_PutPixel(x+i,y+(int)j,c);
			j+=dec;
		}
	}


}

void x4_VertLine(int x, int y, int len, int c){
	if(len>0){
		for(int i = 0; i < len; i++){
			x4_PutPixel(x,y+i,c);//F this I'm not writing a real routine
		}
	}else{
		for(int i = 0; i > len; i++){
			x4_PutPixel(x,y+i,c);
		}
	}
}

void x4_Line(int x1, int y1, int x2, int y2, int c){
	short dx=x2-x1;
	short dy=y2-y1;
	if(dx<0)dx=-dx;
	if(dy<0)dy=-dy;
	if(dx==0){
		x4_VertLine(x1,y1,y2-y1,c);
		return;
	}
	if(dy==0){
		x4_HorizLine(x1,y1,x2-x1,c);
		return;
	}
	//The real stuff,
	if(dx>dy){
		//Run this x major
		short py = y1 < y2 ? 1 : -1;
		for(int i = 0; i < dx; i++){
			x4_PutPixel(x1+i,y1+py*(dy*i/dx),c);
		}
	}else{
		short px = x1 < x2 ? 1 : -1;
		for(int i = 0; i < dy; i++){
			x4_PutPixel(x1+px*(dx*i/dy),y1+i,c);
		}
	}
	x4_PutPixel(x1,y1,c);
	x4_PutPixel(x2,y2,c);
}

#endif
