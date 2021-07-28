/*
 * dialogs.c
 *
 *  state->corner_radiuseated on: Jul 25, 2021
 *      Author: michael
 */

#include "dialogs.h"

void show_editor_settings_dialog(struct estate *state) {
	short k = 0;
	while (k != KEY_CLEAR) {
		draw_dialog(state, 40, 40, 240, 160);
		gfx_SetColor(state->border_color);
		gfx_HorizLine_NoClip(40, 60, 240);
		fontlib_SetCursorPosition(100, 45);
		fontlib_SetForegroundColor(state->text_color);
		fontlib_DrawString("Editor Settings");
		gfx_BlitBuffer();
		k = ngetchx();
	}
}

void menu_backend_draw(struct estate *state, int index) {
	draw_dialog(state, 20, 20, 280, 200);
	gfx_SetColor(state->border_color);
	gfx_HorizLine_NoClip(20, 40, 280);
	fontlib_SetCursorPosition(104, 25);
	fontlib_SetForegroundColor(state->text_color);
	fontlib_DrawString("CEdit Settings");
	fontlib_SetCursorPosition(30, 45);
	if (index == 0) {
		fontlib_SetForegroundColor(state->focus_color);
		//fontlib_DrawString(">");
	}
	fontlib_DrawString("Editor Settings");
	fontlib_SetForegroundColor(state->text_color);
	fontlib_SetCursorPosition(30, 60);
	if (index == 1) {
		fontlib_SetForegroundColor(state->focus_color);
		//fontlib_DrawString(">");
	}
	fontlib_DrawString("Appearance Settings");
	fontlib_SetForegroundColor(state->text_color);
	fontlib_SetCursorPosition(30, 75);
	if (index == 2) {
		fontlib_SetForegroundColor(state->focus_color);
		//fontlib_DrawString(">");
	}
	fontlib_DrawString("Persistence Settings");
	fontlib_SetForegroundColor(state->text_color);
	fontlib_SetCursorPosition(30, 90);
	if (index == 3) {
		fontlib_SetForegroundColor(state->focus_color);
		//fontlib_DrawString(">");
	}
	fontlib_DrawString("About Cedit");
	fontlib_SetForegroundColor(state->text_color);
	fontlib_SetCursorPosition(30, 105);
	if (index == 4) {
		fontlib_SetForegroundColor(state->focus_color);
		//fontlib_DrawString(">");
	}
	fontlib_DrawString("Keybind information");
	fontlib_SetForegroundColor(state->text_color);
	fontlib_SetCursorPosition(30, 120);
	if (index == 5) {
		fontlib_SetForegroundColor(state->focus_color);
		//fontlib_DrawString(">");
	}
	fontlib_DrawString("Bug report");
	fontlib_SetForegroundColor(state->text_color);
	fontlib_SetCursorPosition(30, 135);
	if (index == 6) {
		fontlib_SetForegroundColor(state->focus_color);
		//fontlib_DrawString(">");
	}
	fontlib_DrawString("Back");
	fontlib_SetForegroundColor(state->text_color);
	fontlib_SetCursorPosition(30, 150);
	if (index == 7) {
		fontlib_SetForegroundColor(state->focus_color);
		//fontlib_DrawString(">");
	}
	fontlib_DrawString("Quit CEdit");
}

void show_menu_dialog(struct estate *state) {
	short k = 0;
	int index = 0;
	while (k != KEY_CLEAR) {
		if (k == '\n' || k == KEY_RIGHT) {
			switch (index) {
			case 0:
				show_editor_settings_dialog(state);
				break;
			case 1:
			case 2:
			case 3:
				show_about_dialog(state);
				break;
			case 4:
			case 5:
			case 6:
				return;
			case 7:
				gfx_End();
				exit(0);
			}
		}
		if (k == KEY_UP) {
			if (index) {
				index--;
			}
		}
		if (k == KEY_DOWN) {
			if (index < 7) {
				index++;
			}
		}
		menu_backend_draw(state, index);

		gfx_BlitBuffer();
		k = ngetchx();

	}
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

//1 means canceled
bool show_save_dialog(struct estate *state) {
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
		gfx_BlitBuffer();
		k = ngetchx_xy(state, cx, 112);
		if (k == KEY_CLEAR) {
			return true;
		}
		if (k == '\n') {
			if (!numchars) {
				return true;
			}
			state->named = true;
			strncpy(state->filename, buffer, 8);
			return false;
		}
		if (!is_control(k)) {
			if (numchars < 8) {
				buffer[numchars] = k;
				numchars++;
			}
		}
		if (k == KEY_BS) {
			if (numchars)
				buffer[--numchars] = 0;
		}

	}
	return false;
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
	gfx_BlitBuffer();
	ngetchx();
}
