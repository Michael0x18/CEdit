#include "font.h"



void x4_load_default_font(uint8_t font_buffer[128][8][8], uint8_t fg, uint8_t bg){
static uint8_t topaz_font[128][8][2]={
{{85, 85, },{170, 170, },{85, 85, },{170, 170, },{85, 85, },{170, 170, },{85, 85, },{170, 170, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{60, 0, },{255, 204, },{255, 204, },{60, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{240, 0, },{240, 0, },{0, 0, },{240, 0, },{240, 0, },{0, 0, },{0, 0, },},
{{12, 192, },{255, 252, },{255, 252, },{12, 192, },{255, 252, },{255, 252, },{12, 192, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
{{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },{0, 0, },},
};
    memset(font_buffer,0,128*64);
    for(int i = 0; i < 128; i++){
        for(int j = 0; j < 8; j++){
            for(int k = 0; k < 2; k++){
                for(int l = 0; l < 8; l++){
                    if((topaz_font[i][j][k] & (1<<l)) > 0){
                        //We use the foreground color
                        font_buffer[i][j][k*2+l/2]=(l%2==0)?font_buffer[i][j][k*2+l/2]|fg:font_buffer[i][j][k*2+l/2]|(fg<<4);
                    }else{
                        font_buffer[i][j][k*2+l/2]=(l%2==0)?font_buffer[i][j][k*2+l/2]|bg:font_buffer[i][j][k*2+l/2]|(bg<<4);
                    }
                }
            }
        }
    }
}

void x4_PutChar(int x, int y, char ch, int color){
    
}