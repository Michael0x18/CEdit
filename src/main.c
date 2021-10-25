#include <stdio.h>
#include <stdlib.h>
#include <tice.h>
#include "libx4.h"

int main(int argc, char** argv){
    x4_Begin();
    x4_LoadDefaultPalette();
    //x4_SetDrawLocation(X4_BUFFER_1);
    for(int8_t i = 0; i < 16; i++){
        x4_FillScreen(i);
        while(!os_GetCSC());
    }
    //x4_SetDrawLocation(X4_BUFFER_2);
    //x4_FillScreen(15);
    //x4_SetDrawLocation(X4_BUFFER_3);
    //x4_FillScreen(0);
    //while(!os_GetCSC());
    //x4_BlitBuffer(X4_BUFFER_1,X4_BUFFER_2);
    //while(!os_GetCSC());
    //x4_BlitBuffer(X4_BUFFER_1,X4_BUFFER_3);
    while(!os_GetCSC());
    x4_End();
}
