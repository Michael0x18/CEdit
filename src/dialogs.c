/*
 * dialogs.c
 *
 *  state->corner_radiuseated on: Jul 25, 2021
 *      Author: michael
 */

#include "dialogs.h"

void show_menu_dialog(struct estate *state) {
	draw_dialog(state, 20, 20, 280, 200);
	gfx_SetColor(state->border_color);
	gfx_HorizLine_NoClip(20, 40, 280);
	fontlib_SetCursorPosition(104, 25);
	fontlib_DrawString("CEdit Settings");
	gfx_SwapDraw();
	ngetchx();
}

void draw_dialog(struct estate *state, int x, int y, int w, int h) {
	//draw_editor();

	gfx_SetColor(state->dropshadow_color);
	gfx_FillCircle_NoClip(5 + x + state->corner_radius,
			5 + y + state->corner_radius, state->corner_radius);
	gfx_FillCircle_NoClip(5 + x + w - state->corner_radius - 1,
			5 + y + state->corner_radius, state->corner_radius);
	gfx_FillCircle_NoClip(5 + x + state->corner_radius,
			5 + y + h - state->corner_radius - 1, state->corner_radius);
	gfx_FillCircle_NoClip(5 + x + w - state->corner_radius - 1,
			5 + y + h - state->corner_radius - 1, state->corner_radius);
	gfx_FillRectangle_NoClip(5 + x + state->corner_radius, 5 + y,
			w - state->corner_radius - state->corner_radius, h);
	gfx_FillRectangle_NoClip(5 + x, 5 + y + state->corner_radius, w,
			h - state->corner_radius - state->corner_radius);

	gfx_SetColor(state->border_color);
	gfx_Circle_NoClip(x + state->corner_radius, y + state->corner_radius,
			state->corner_radius);
	gfx_Circle_NoClip(x + w - state->corner_radius - 1,
			y + state->corner_radius, state->corner_radius);
	gfx_Circle_NoClip(x + state->corner_radius,
			y + h - state->corner_radius - 1, state->corner_radius);
	gfx_Circle_NoClip(x + w - state->corner_radius - 1,
			y + h - state->corner_radius - 1, state->corner_radius);
	gfx_Rectangle_NoClip(x + state->corner_radius, y,
			w - state->corner_radius - state->corner_radius, h);
	gfx_Rectangle_NoClip(x, y + state->corner_radius, w,
			h - state->corner_radius - state->corner_radius);

	gfx_SetColor(state->background_color);
	gfx_FillCircle_NoClip(x + state->corner_radius, y + state->corner_radius,
			state->corner_radius - 1);
	gfx_FillCircle_NoClip(x + w - state->corner_radius - 1,
			y + state->corner_radius, state->corner_radius - 1);
	gfx_FillCircle_NoClip(x + state->corner_radius,
			y + h - state->corner_radius - 1, state->corner_radius - 1);
	gfx_FillCircle_NoClip(x + w - state->corner_radius - 1,
			y + h - state->corner_radius - 1, state->corner_radius - 1);
	gfx_FillRectangle_NoClip(x + state->corner_radius + 1, y + 1,
			w - state->corner_radius - state->corner_radius + 2, h - 2);
	gfx_FillRectangle_NoClip(x + 1, y + state->corner_radius - 1, w - 2,
			h - state->corner_radius - state->corner_radius + 2);
}

void show_open_dialog(struct estate *state) {
	//TODO TODO TODO TODO TODO TODO TODO      TODO TODO TODO
	//TODO TODO TODO TODO TODO TODO TODO      TODO TODO TODO
	//TODO TODO TODO TODO TODO TODO TODO      TODO TODO TODO
	//TODO TODO TODO TODO TODO TODO TODO      TODO TODO TODO
	//TODO TODO TODO TODO TODO TODO TODO      TODO TODO TODO
	//TODO TODO TODO TODO TODO TODO TODO      TODO TODO TODO
	//TODO TODO TODO TODO TODO TODO TODO      TODO TODO TODO
	//TODO TODO TODO TODO TODO TODO TODO      TODO TODO TODO
	//TODO TODO TODO TODO TODO TODO TODO      TODO TODO TODO
	//TODO TODO TODO                          TODO TODO TODO
	//TODO TODO TODO                          TODO TODO TODO
	//TODO TODO TODO      TODO TODO TODO      TODO TODO TODO
	//TODO TODO TODO      TODO TODO TODO      TODO TODO TODO
	//TODO TODO TODO      TODO TODO TODO      TODO TODO TODO
	//TODO TODO TODO      TODO TODO TODO      TODO TODO TODO
	//TODO TODO TODO      TODO TODO TODO      TODO TODO TODO
	//TODO TODO TODO      TODO TODO TODO      TODO TODO TODO
	//TODO TODO TODO      TODO TODO TODO      TODO TODO TODO
	//TODO TODO TODO      TODO TODO TODO      TODO TODO TODO
	//TODO TODO TODO      TODO TODO TODO      TODO TODO TODO
	//TODO TODO TODO      TODO TODO TODO      TODO TODO TODO
	//TODO TODO TODO      TODO TODO TODO      TODO TODO TODO
	//TODO TODO TODO      TODO TODO TODO      TODO TODO TODO
	//TODO TODO TODO      TODO TODO TODO      TODO TODO TODO
	//TODO TODO TODO      TODO TODO TODO      TODO TODO TODO

}

void show_save_dialog(struct estate *state) {
	short k = 0;
	int numchars = 0;
	char buffer[10];
	memset(buffer, 0, 10);
	int cx = 52;
	while (true) {
		draw_dialog(state, 20, 60, 280, 100);
		gfx_SetColor(state->border_color);
		gfx_HorizLine_NoClip(20, 80, 280);
		//fontlib_SetCursorPosition(115,80);
		fontlib_SetCursorPosition(115, 65);
		fontlib_DrawString("Save File");
		fontlib_SetCursorPosition(30, 90);
		fontlib_DrawString("Enter File Name to (Over)write:");
		gfx_SetColor(state->dropshadow_color);
		gfx_Rectangle_NoClip(51, 111, 220, 16);
		gfx_SetColor(state->border_color);
		gfx_Rectangle_NoClip(50, 110, 220, 16);
		fontlib_SetCursorPosition(52, 112);
		fontlib_DrawString(buffer);
		gfx_VertLine(52 + FONT_WIDTH * numchars, 112, 12);
		cx = 52 + FONT_WIDTH * numchars;
		gfx_SwapDraw();
		k = ngetchx_xy(state, cx, 112);
		if (k == KEY_CLEAR) {
			return;
		}
		if (k == '\n') {
			if (!numchars) {
				return;
			}
			state->named = true;
			strncpy(state->filename, buffer, 8);
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

void show_about_dialog(struct estate *state) {
	draw_dialog(state, 60, 60, 200, 120);
	gfx_SetColor(state->border_color);
	gfx_HorizLine_NoClip(60, 80, 200);
	//fontlib_SetCursorPosition(115,80);
	fontlib_SetCursorPosition(115, 65);
	fontlib_DrawString("About CEdit");
	fontlib_SetCursorPosition(80, 120);
	fontlib_DrawString(CEDIT_VERSION_STRING);
	gfx_SwapDraw();
	ngetchx();
}
