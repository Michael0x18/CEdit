#include <stdio.h>
#include <stdlib.h>
#include <tice.h>
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
    x4_SetDrawLocation(X4_BUFFER_2);
    x4_FillScreen(7);
    x4_SetDrawLocation(X4_BUFFER_3);
    x4_FillScreen(6);
    //while(!os_GetCSC());
    x4_BlitBuffer(X4_BUFFER_1,X4_BUFFER_2);
    while(!os_GetCSC());
    //x4_BlitBuffer(X4_BUFFER_1,X4_BUFFER_3);
    x4_SetScreenLocation(X4_BUFFER_3);
    while(!os_GetCSC());
    x4_SetScreenLocation(X4_BUFFER_1);
    x4_End();
}
*/
int main(void){
    x4_Begin();
    x4_LoadDefaultPalette();
    x4_SetDrawLocation(X4_BUFFER_1);

    x4_FillScreen(15);

    for(int x = 0; x < 200; x++)
        for(int y = 0; y < 200; y++)
            x4_PutPixel(y,x,0);

    while(!os_GetCSC());

    x4_End();
}