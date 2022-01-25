#include <stdio.h>
#include <stdlib.h>
#include <tice.h>
#include <keypadc.h>
#include <graphx.h>
#include "libx4.h"
/*
int main(void)
{

	int8_t frame = 0;
	x4_Begin();
	x4_LoadDefaultPalette();
	x4_FillScreen(15);
	x4_SetDrawLocation(X4_BUFFER_2);
	x4_FillScreen(15);
	int cursor_x = 0;
	int cursor_y = 0;

	while (!kb_IsDown(kb_KeyClear))
	{
		x4_FillScreen(15);
		x4_PutPixel(120, 0, 0);

		x4_FastLine_Fix(160, 120, cursor_x, cursor_y, 0);
		kb_Scan();

		if (kb_IsDown(kb_KeyLeft))
			cursor_x--;
		if (kb_IsDown(kb_KeyRight))
			cursor_x++;
		if (kb_IsDown(kb_KeyUp))
			cursor_y--;
		if (kb_IsDown(kb_KeyDown))
			cursor_y++;

		if (cursor_x < 0)
			cursor_x = 0;
		if (cursor_x > 319)
			cursor_x = 319;
		if (cursor_y < 0)
			cursor_y = 0;
		if (cursor_y > 239)
			cursor_y = 239;

		if (frame)
		{

			frame = 0;
			x4_SetScreenLocation(X4_BUFFER_2);
			x4_SetDrawLocation(X4_BUFFER_1);
		}
		else
		{

			frame = 1;
			x4_SetScreenLocation(X4_BUFFER_1);
			x4_SetDrawLocation(X4_BUFFER_2);
		}
	}

	x4_SetScreenLocation(X4_BUFFER_1);
	x4_End();
}*/
#define lcd_CrsrImage ((uint32_t*)0xE30800)

unsigned char cursor_bin[256]={
	0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};

void main(void) {
	x4_Begin();
	x4_FillScreen(15);
	uint16_t x = 0, y = 0;
	
	// set the CPL
	lcd_Timing2 = (uint32_t)(lcd_Timing2 & ~(uint32_t)0x03FF0000) | (uint32_t)(LCD_WIDTH - 1) << 16;
	memcpy(lcd_CrsrImage, cursor_bin, 256); // set cursor image

	lcd_CrsrConfig = 0; // select 32x32, image0
	lcd_CrsrPalette0 = 0x00000000; // set black palette color
	lcd_CrsrPalette1 = 0x00FFFFFF; // set white palette color
	lcd_CrsrXY = 0; // reset cursor position
	lcd_CrsrClip = 0; // reset clipping
	lcd_CrsrCtrl = 1; // enable cursor

	while(!kb_IsDown(kb_KeyClear)) {
		kb_Scan();
		if(kb_IsDown(kb_KeyLeft)) x--;
		if(kb_IsDown(kb_KeyRight)) x++;
		if(kb_IsDown(kb_KeyUp)) y--;
		if(kb_IsDown(kb_KeyDown)) y++;
		lcd_CrsrX = x; // update the position of the cursor
		lcd_CrsrY = y;
	}

	lcd_CrsrCtrl = 0; // disable cursor
	// reset CPL
	lcd_Timing2 = (uint32_t)(lcd_Timing2 & ~(uint32_t)0x03FF0000) | (uint32_t)(LCD_HEIGHT - 1) << 16;
	x4_End();
}
