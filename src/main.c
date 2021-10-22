#include <stdio.h>
#include <stdlib.h>
#include <tice.h>
#include "libx4.h"

int main(int argc, char** argv){
    x4_Begin();
    x4_LoadDefaultPalette();
    for(int8_t i = 0; i < 16; i++){
        x4_FillScreen(i);
        while(!os_GetCSC());
    }
    x4_End();
}