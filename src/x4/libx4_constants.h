#ifndef libx4_constants_h
#define libx4_constants_h

#define X4_VRAM (void *)lcd_Ram
#define X4_BUFFER_0 (void *)lcd_Ram
#define X4_BUFFER_1 (void *)(0xD40000 + 38400)
#define X4_BUFFER_2 (void *)(0xD40000 + 76800)
#define X4_BUFFER_3 (void *)(0xD40000 + 115200)

#define X4_fixed_point_factor 64

#define X4_SCREEN_LOCATION (void *)lcd_UpBase
extern void *x4_Buffer;
#define X4_DRAW_LOCATION x4_Buffer

#endif
