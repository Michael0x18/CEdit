#ifndef routines_h
#define routines_h

#include "cedit.h"

void b4_Begin(void);
void b4_End(void);
void b4_FillRect(int24_t x, int24_t y,int24_t w,int24_t h,int24_t c);
void b4_Rect(int24_t x, int24_t y,int24_t w,int24_t h,int24_t c);
void b4_Circle(int24_t x, int24_t y,int24_t r,int24_t c);
void b4_FillCircle(int24_t x, int24_t y,int24_t r,int24_t c);
void b4_Line(int24_t x1,int24_t y1,int24_t x2,int24_t y2,int24_t c);
void b4_HorizLine(int24_t x, int24_t y, int24_t len, int24_t c);
void b4_VertLine(int24_t x, int24_t y, int24_t len, int24_t c);
void b4_FillScreen(int24_t c);

//Puts da screen in 4bpp
//void b4_Begin(void){
//    asm(    "ld	a, ti.lcdBpp4                 \n"
//	        "ld	(ti.mpLcdCtrl), a               ");
//}

#endif