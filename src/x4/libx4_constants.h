#ifndef libx4_constants_h
#define libx4_constants_h

#define X4_VRAM (void *)lcd_Ram
#define X4_BUFFER_0 (void *)lcd_Ram
#define X4_BUFFER_1 (void *)(lcd_Ram + 38400)
#define X4_BUFFER_2 (void *)(lcd_Ram + 76800)
#define X4_BUFFER_3 (void *)(lcd_Ram + 115200)

#define X4_fixed_point_factor 64

#define X4_SCREEN_LOCATION lcd_UpBase
extern void *x4_Buffer;
#define X4_DRAW_LOCATION x4_Buffer

#endif
