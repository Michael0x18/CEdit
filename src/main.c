#include <stdio.h>
#include <stdlib.h>
#include <tice.h>
#include <keypadc.h>
#include <graphx.h>
#include "libx4.h"
/*
   int main(int argc, char** argv){
   x4_Begin();
   x4_LoadDefaultPalette();
   x4_SetDrawLocation(X4_BUFFER_1);
   for(int8_t i = 0; i < 16; i++){
   x4_FillScreen(i);
   while(!os_GetCSC());
   }
//x4_SetDrawLocation(X4_BUFFER_2);
//x4_FillScreen(7);
//x4_SetDrawLocation(X4_BUFFER_3);
//x4_FillScreen(6);
//while(!os_GetCSC());
//x4_BlitBuffer(X4_BUFFER_1,X4_BUFFER_2);
//while(!os_GetCSC());
//x4_BlitBuffer(X4_BUFFER_1,X4_BUFFER_3);
//x4_SetScreenLocation(X4_BUFFER_3);
//while(!os_GetCSC());
x4_SetScreenLocation(X4_BUFFER_1);
x4_End();
}*/

bool a = false;
void swapdraw(void){
	if(a){
		x4_SetScreenLocation(X4_BUFFER_1);
		x4_SetDrawLocation(X4_BUFFER_2);
		a=false;
	}else{
		x4_SetScreenLocation(X4_BUFFER_2);
		x4_SetDrawLocation(X4_BUFFER_1);
		a=true;
	}
}

int main(void){
	bool f = false;
	//int32_t andit= 0b00000111111111111111111111111111l;
	//int32_t orit = 0b00000000000000000000000000000000l;
	//lcd_Timing2&=andit;
	//lcd_Timing2|=orit;
	x4_Begin();
	x4_LoadDefaultPalette();
	x4_FillScreen(15);
	x4_SetDrawLocation(X4_BUFFER_2);
	x4_FillScreen(15);

	//for(int x = 0; x < 20; x++){
	//    for(int y = 0; y < 20; y++){
	//        x4_PutPixel(y,x,0);
	//  
	//     }
	// }
	//x4_PutPixel(1,0,0);
	//x4_HorizLine(40,40,40,6);
	//x4_SetScreenLocation(X4_BUFFER_2);
	int a = 0;int b=0;short k = 0;
	while(!kb_IsDown(kb_KeyClear)){
		//k=0;
		//swapdraw();
		if(f){
			x4_SetDrawLocation(X4_BUFFER_2);
		}else{
			x4_SetDrawLocation(X4_BUFFER_1);
		}
		x4_FillScreen(15);
		x4_PutPixel(120,0,0);
		x4_FastLine_Fix(160,120,a,b,0);
		//while(!k)
		//	k = os_GetCSC();
		kb_Scan();
		if(kb_IsDown(kb_KeyLeft)){
			a--;
		}
		if(kb_IsDown(kb_KeyRight)){
			a++;
		}
		if(kb_IsDown(kb_KeyUp)){
			b--;
		}
		if(kb_IsDown(kb_KeyDown)){
			b++;
		}
		if(a<0)a=0;
		if(a>319)a=319;
		if(b<0)b=0;
		if(b>239)b=239;
//x4_BlitBuffer(X4_BUFFER_1,X4_BUFFER_2);
		//gfx_Wait();
		//swapdraw();
		if(f){
			x4_SetScreenLocation(X4_BUFFER_2);
		}else{
			x4_SetScreenLocation(X4_BUFFER_1);
		}
		f=!f;
		//delay(250);
		//gfx_Wait();
	}
	x4_SetScreenLocation(X4_BUFFER_1);
	x4_End();
}

/*
int main(void){
	int x=0;
	int y=0;
	x4_Begin();
	x4_LoadDefaultPalette();
	x4_FillScreen(15);
	while(!kb_IsDown(kb_KeyClear)){
		if(kb_IsDown(kb_KeyUp)){
			y--;
		}
		if(kb_IsDown(kb_KeyDown)){
			y++;
		}
		if(kb_IsDown(kb_KeyRight)){
			x++;
		}
		if(kb_IsDown(kb_KeyLeft)){
			x--;
		}
		if(y<0)y=0;
		if(y>239)y=239;
		if(x<0)x=0;
		if(x>319)x=319;
		x4_PutPixel(x,y,0);
		delay(10);
	}
	x4_End();
}*/
/*

int main(void){
	x4_Begin();
	x4_LoadDefaultPalette();
	x4_FillScreen(6);
	x4_SetDrawLocation(X4_BUFFER_2);
	x4_FillScreen(7);
	while(!kb_IsDown(kb_KeyClear)){
		swapdraw();
		delay(100);
	}
	x4_SetScreenLocation(X4_BUFFER_1);
	x4_End();
}*/










