#include <stdio.h>
#include <stdlib.h>
#include <tice.h>
#include <keypadc.h>
#include <graphx.h>
#include "libx4.h"

int main(void) {

	int8_t frame = 0;
	x4_Begin();
	x4_LoadDefaultPalette();
	x4_FillScreen(15);
	x4_SetDrawLocation(X4_BUFFER_2);
	x4_FillScreen(15);
	int cursor_x = 0;
	int cursor_y = 0;

	while(!kb_IsDown(kb_KeyClear)) {
		x4_FillScreen(15);
		x4_PutPixel(120, 0, 0);

		x4_FastLine_Fix(160, 120, cursor_x, cursor_y, 0);
		kb_Scan();

		if(kb_IsDown(kb_KeyLeft))
			cursor_x--;
		if(kb_IsDown(kb_KeyRight))
			cursor_x++;
		if(kb_IsDown(kb_KeyUp))
			cursor_y--;
		if(kb_IsDown(kb_KeyDown))
			cursor_y++;

		if(cursor_x < 0)
			cursor_x = 0;
		if(cursor_x > 319)
			cursor_x = 319;
		if(cursor_y < 0)
			cursor_y = 0;
		if(cursor_y > 239)
			cursor_y = 239;

		if(frame) {

			frame = 0;
			x4_SetScreenLocation(X4_BUFFER_2);
			x4_SetDrawLocation(X4_BUFFER_1);

		}else {

			frame = 1;
			x4_SetScreenLocation(X4_BUFFER_1);
			x4_SetDrawLocation(X4_BUFFER_2);

		}

	}

	x4_SetScreenLocation(X4_BUFFER_1);
	x4_End();
}

