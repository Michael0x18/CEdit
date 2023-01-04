#include "font.h"

extern uint8_t topaz_font[128][8][2];

void x4_load_default_font(uint8_t font_buffer[128][8][8], uint8_t fg, uint8_t bg)
{
    // int bg_val = bg+(bg<<4);
    memset(font_buffer, 0, 128 * 64);
    for (int i = 0; i < 128; i++)
    {
        // For each character
        for (int j = 0; j < 8; j++)
        {
            // Iterate by column
            for (int k = 0; k < 2; k++)
            {
                // Iterate by packed row, trying to expand it
                for (int l = 0; l < 8; l++)
                {
                    if ((topaz_font[i][j][k] & (1 << (7 - l))) > 0)
                    {
                        // We use the foreground color
                        font_buffer[i][j][k * 4 + l / 2] = (l % 2 == 0) ? fg : font_buffer[i][j][k * 4 + l / 2] | (fg << 4);
                    }
                    else
                    {
                        font_buffer[i][j][k * 4 + l / 2] = (l % 2 == 0) ? bg : font_buffer[i][j][k * 4 + l / 2] | (bg << 4);
                    }
                }
            }
        }
    }
}

void x4_PutChar(uint8_t font_buffer[128][8][8], int x, int y, char ch)
{
    for (int i = 0; i < 8; i++)
    {
        // col
        int offset = (x + i) * 120 + y / 2;
        // int offset = x4_GetPixelAddress(x + i, y);
        // memcpy(x4_Buffer + offset, font_buffer[(uint8_t)ch][i], 8);
        x4_Copy8Bytes(x4_Buffer + offset, font_buffer[(uint8_t)ch][i]);
    }
    x4_Copy8x8(x, y, font_buffer[(uint8_t)ch]);
    // int offset = x4_GetPixelAddress(x, y);
    // calc84maniac_Copy8x8(x4_Buffer + offset, font_buffer[(uint8_t)ch]);
}

void x4_PutStr(uint8_t font_buffer[128][8][8], int x, int y, char *str)
{
    uint8_t i = 0;
    while (str[i])
    {
        x4_PutChar(font_buffer, x + 9 * i, y, str[i]);
        i++;
    }
}