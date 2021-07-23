#ifndef dialogs_c
#define dialogs_c

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>
#include <fileioc.h>
#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <graphx.h>
#include <keypadc.h>
#include <fontlibc.h>

#include "dialogs.h"
#include "gfx.h"
#include "editor.h"

#define CEDIT_VERSION_STRING "CEdit 0.05 BETA"

void draw_dialog(int x, int y, int w, int h) {
	draw_editor();

	gfx_SetColor(dropshadow_color);
	gfx_FillCircle_NoClip(5 + x + cr, 5 + y + cr, cr);
	gfx_FillCircle_NoClip(5 + x + w - cr - 1, 5 + y + cr, cr);
	gfx_FillCircle_NoClip(5 + x + cr, 5 + y + h - cr - 1, cr);
	gfx_FillCircle_NoClip(5 + x + w - cr - 1, 5 + y + h - cr - 1, cr);
	gfx_FillRectangle_NoClip(5 + x + cr, 5 + y, w - cr - cr, h);
	gfx_FillRectangle_NoClip(5 + x, 5 + y + cr, w, h - cr - cr);

	gfx_SetColor(border_color);
	gfx_Circle_NoClip(x + cr, y + cr, cr);
	gfx_Circle_NoClip(x + w - cr - 1, y + cr, cr);
	gfx_Circle_NoClip(x + cr, y + h - cr - 1, cr);
	gfx_Circle_NoClip(x + w - cr - 1, y + h - cr - 1, cr);
	gfx_Rectangle_NoClip(x + cr, y, w - cr - cr, h);
	gfx_Rectangle_NoClip(x, y + cr, w, h - cr - cr);

	gfx_SetColor(background_color);
	gfx_FillCircle_NoClip(x + cr, y + cr, cr - 1);
	gfx_FillCircle_NoClip(x + w - cr - 1, y + cr, cr - 1);
	gfx_FillCircle_NoClip(x + cr, y + h - cr - 1, cr - 1);
	gfx_FillCircle_NoClip(x + w - cr - 1, y + h - cr - 1, cr - 1);
	gfx_FillRectangle_NoClip(x + cr + 1, y + 1, w - cr - cr + 2, h - 2);
	gfx_FillRectangle_NoClip(x + 1, y + cr - 1, w - 2, h - cr - cr + 2);
}

void show_open_dialog(void) {

}

void show_save_dialog(void) {
	short k = 0;
	int numchars = 0;
	char buffer[10];
	memset(buffer, 0, 10);
	while (true) {
		draw_dialog(20, 60, 280, 100);
		gfx_SetColor(border_color);
		gfx_HorizLine_NoClip(20, 80, 280);
		//fontlib_SetCursorPosition(115,80);
		fontlib_SetCursorPosition(115, 65);
		fontlib_DrawString("Save File");
		fontlib_SetCursorPosition(30, 90);
		fontlib_DrawString("Enter File Name to (Over)write:");
		gfx_SetColor(dropshadow_color);
		gfx_Rectangle_NoClip(51, 111, 220, 16);
		gfx_SetColor(border_color);
		gfx_Rectangle_NoClip(50, 110, 220, 16);
		fontlib_SetCursorPosition(52, 112);
		fontlib_DrawString(buffer);
		gfx_VertLine(52+fw*numchars,112,12);
		gfx_SwapDraw();
		k = ngetchx();
		if (k == KEY_CLEAR) {
			return;
		}
		if (k == '\n') {
			if (!numchars) {
				return;
			}
			named=true;
			strncpy(filename, buffer, 8);
			return;
		}
		if (!is_control(k)) {
			if (numchars < 8) {
				buffer[numchars] = k;
				numchars++;
			}
		}
		if (k == KEY_BS) {
			buffer[--numchars] = 0;
		}

	}
}

void show_about_dialog(void) {
	draw_dialog(60, 60, 200, 120);
	gfx_SetColor(border_color);
	gfx_HorizLine_NoClip(60, 80, 200);
	//fontlib_SetCursorPosition(115,80);
	fontlib_SetCursorPosition(115, 65);
	fontlib_DrawString("About CEdit");
	fontlib_SetCursorPosition(80, 120);
	fontlib_DrawString(CEDIT_VERSION_STRING);
	gfx_SwapDraw();
	ngetchx();
}

#endif
