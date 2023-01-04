#include <stdio.h>
#include <stdlib.h>
#include <tice.h>
#include <keypadc.h>
#include <graphx.h>
#include <string.h>

#include <debug.h>

#include "x4/libx4.h"

//#define lcd_CrsrImage ((uint32_t *)0xE30800)

unsigned char cursor_bin[] = {
	0x00, 0x00, 0x00, 0x00, 0x2a, 0xaa, 0xaa, 0xaa, 0x85, 0x55, 0x55, 0x55,
	0x2a, 0xaa, 0xaa, 0xaa, 0xa1, 0x55, 0x55, 0x54, 0xaa, 0xaa, 0xaa, 0xaa,
	0xa8, 0x55, 0x55, 0x52, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0x15, 0x55, 0x4a,
	0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0x85, 0x55, 0x50, 0xaa, 0xaa, 0xaa, 0xaa,
	0xaa, 0xa1, 0x55, 0x55, 0x0a, 0xaa, 0xaa, 0xaa, 0xaa, 0xa8, 0x55, 0x05,
	0x52, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0x15, 0x20, 0x52, 0xaa, 0xaa, 0xaa,
	0xaa, 0xaa, 0x85, 0x2a, 0x0a, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xa1, 0x2a,
	0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xa8, 0x2a, 0xaa, 0xaa, 0xaa, 0xaa,
	0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
	0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
	0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
	0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
	0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
	0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
	0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
	0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
	0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
	0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
	0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
	0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
	0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
	0xaa, 0xaa, 0xaa, 0xaa};
unsigned int cursor_bin_len = 256;

int main(void)
{
	x4_Begin();
	x4_LoadDefaultPalette();
	x4_FillScreen(15);
	x4_SetDrawLocation(X4_BUFFER_0);
	uint16_t x = 300, y = 0;

	// set the CPL
	// lcd_Timing2 = (uint32_t)(lcd_Timing2 & ~(uint32_t)0x03FF0000) | (uint32_t)(LCD_WIDTH - 1) << 16;
	memcpy(lcd_CrsrImage, cursor_bin, 256); // set cursor image

	lcd_CrsrConfig = 0;			   // select 32x32, image0
	lcd_CrsrPalette0 = 0x00000000; // set black palette color
	lcd_CrsrPalette1 = 0x00FFFFFF; // set white palette color
	lcd_CrsrXY = 0;				   // reset cursor position
	lcd_CrsrClip = 0;			   // reset clipping
	lcd_CrsrCtrl = 1;			   // enable cursor
	uint8_t bg = 0;
	bool pressed = false;
	while (!kb_IsDown(kb_KeyClear))
	{
		kb_Scan();
		if (kb_IsDown(kb_KeyLeft))
			x--;
		if (kb_IsDown(kb_KeyRight))
			x++;
		if (kb_IsDown(kb_KeyUp))
			y--;
		if (kb_IsDown(kb_KeyDown))
			y++;
		if (kb_IsDown(kb_KeyEnter))
		{
			if (pressed == false)
			{
				bg++;
				pressed = true;

				if (bg >= 16)
					bg = 0;
				x4_FillScreen(bg);
				dbg_printf("%u\n", X4_DRAW_LOCATION);
				if (X4_SCREEN_LOCATION == X4_BUFFER_2)
				{
					x4_SetDrawLocation(X4_BUFFER_1);
					x4_SetScreenLocation(X4_BUFFER_0);
				}
				else if (X4_SCREEN_LOCATION == X4_BUFFER_0)
				{
					x4_SetDrawLocation(X4_BUFFER_2);
					x4_SetScreenLocation(X4_BUFFER_1);
				}
				else if (X4_SCREEN_LOCATION == X4_BUFFER_1)
				{
					x4_SetDrawLocation(X4_BUFFER_0);
					x4_SetScreenLocation(X4_BUFFER_2);
				}
			}
		}
		else
		{
			pressed = false;
		}

		if (x > 1000)
			x = 0;
		if (x >= 320)
			x = 319;
		if (y > 1000)
			y = 0;
		if (y >= 240)
			y = 239;

		lcd_CrsrYFull = x; // update the position of the cursor
		lcd_CrsrX = y;
	}

	lcd_CrsrCtrl = 0; // disable cursor
	x4_SetScreenLocation(X4_BUFFER_0);
	x4_End();
}
