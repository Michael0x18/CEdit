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

void swapdraw(void){
	static bool a;
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
	x4_Begin();
	x4_LoadDefaultPalette();
	x4_SetDrawLocation(X4_BUFFER_1);

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
		swapdraw();
		x4_FillScreen(15);
		x4_Line(0,0,a,b,0);
		//while(!k)
		//	k = os_GetCSC();
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
		//swapdraw();
		delay(10);
		//gfx_Wait();
	}
	x4_SetScreenLocation(X4_BUFFER_1);
	x4_End();
}

