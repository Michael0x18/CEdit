/*
dialogs.c
CEDIT project
Copyright (C) 2021  Michael "Michael0x18"

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
You may use version 2.1 or later only.
*/

#include "dialogs.h"
#include "primitives.h"
#include <math.h>

uint8_t show_color_selection_dialog(struct estate *state, uint8_t current_value)
{
	short k = 0;
	uint8_t temp_transparent_color = state->transparent_color;
	short index = current_value;
	while (k != KEY_CLEAR)
	{
		state->transparent_color = temp_transparent_color;
		draw_dialog(state, 20, 20, 280, 200);
		gfx_SetColor(state->border_color);
		gfx_HorizLine_NoClip(20, 40, 280);
		fontlib_SetCursorPosition(110, 25);
		fontlib_SetForegroundColor(state->text_color);
		fontlib_DrawString("Select Color");
		fontlib_SetCursorPosition(31, 42);
		fontlib_DrawString("Selected: ");
		fontlib_DrawUInt(index, 1);
		state->transparent_color = state->background_color;
		const int J_MAX = 8;
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 32; j++)
			{
				gfx_SetColor(32 * i + j);
				gfx_FillRectangle_NoClip(32 + 8 * j, 72 + 8 * i, 8, 8);
			}
		}
		gfx_SetColor(state->border_color);
		gfx_Rectangle_NoClip(32 + 8 * (index % 32), 72 + 8 * (index >> 5), 8, 8);
		gfx_Rectangle_NoClip(31 + 8 * (index % 32), 71 + 8 * (index >> 5), 10, 10);
		gfx_BlitBuffer();
		k = ngetchx();
		if (k == KEY_CLEAR)
		{
			return current_value;
		}
		if (k == KEY_RIGHT)
		{
			index++;
		}
		if (k == KEY_LEFT)
		{
			index--;
		}
		if (k == KEY_UP)
		{
			index -= 256 / J_MAX;
		}
		if (k == KEY_DOWN)
		{
			index += 256 / J_MAX;
		}
		if (k == '\n')
		{
			state->transparent_color = temp_transparent_color;
			return index;
		}
		index += 256;
		index %= 256;
	}
	return current_value;
}

void show_editor_settings_dialog(struct estate *state)
{
	short k = 0;
	short index = 0;
	while (k != KEY_CLEAR)
	{
		draw_dialog(state, 20, 20, 280, 200);
		gfx_SetColor(state->border_color);
		gfx_HorizLine_NoClip(20, 40, 280);
		fontlib_SetCursorPosition(100, 25);
		fontlib_SetForegroundColor(state->text_color);
		fontlib_DrawString("Editor Settings");
		//~~//~~//~~//~~//~~//~~//~~//~~//~~//~~//
		draw_switch(state, 24, 42, state->autoarchive); //autoarchive
		fontlib_SetForegroundColor(index == 0 ? state->focus_color : state->text_color);
		fontlib_SetCursorPosition(24 + 32, 43);
		fontlib_DrawString("Auto archive files");
		draw_switch(state, 24, 60, state->saveprompt); //saveprompt
		fontlib_SetForegroundColor(index == 1 ? state->focus_color : state->text_color);
		fontlib_SetCursorPosition(24 + 32, 61);
		fontlib_DrawString("Show save prompt on exit");
		draw_switch(state, 24, 78, state->useregex); //regex
		fontlib_SetForegroundColor(index == 2 ? state->focus_color : state->text_color);
		fontlib_SetCursorPosition(24 + 32, 79);
		fontlib_DrawString("Use regex in search");
		draw_switch(state, 24, 96, state->blinkcursor); //blinkcursor
		fontlib_SetForegroundColor(index == 3 ? state->focus_color : state->text_color);
		fontlib_SetCursorPosition(24 + 32, 97);
		fontlib_DrawString("Blink cursor");
		draw_switch(state, 24, 96 + 18, state->backupfiles); //backup
		fontlib_SetForegroundColor(index == 4 ? state->focus_color : state->text_color);
		fontlib_SetCursorPosition(24 + 32, 96 + 19);
		fontlib_DrawString("Copy on write");
		draw_switch(state, 24, 96 + 36, state->bos_use_system_config); //bos_system
		fontlib_SetForegroundColor(index == 5 ? state->focus_color : state->text_color);
		fontlib_SetCursorPosition(24 + 32, 96 + 37);
		fontlib_DrawString("Use config file in /etc");
		draw_switch(state, 24, 96 + 54, state->bos_use_extra_buffer); //extra_buffer
		fontlib_SetForegroundColor(index == 6 ? state->focus_color : state->text_color);
		fontlib_SetCursorPosition(24 + 32, 96 + 55);
		fontlib_DrawString("128Kb edit buffer (BOS)");
		fontlib_SetForegroundColor(state->text_color);
		fontlib_SetCursorPosition(24, 96 + 55 + 18);
		fontlib_DrawString("Permanent changes can be made");
		fontlib_SetCursorPosition(24, 96 + 55 + 30);
		fontlib_DrawString("by editing CEDITRC");
		//~~//~~//~~//~~//~~//~~//~~//~~//~~//~~//
		gfx_BlitBuffer();
		k = ngetchx();
		if (k == KEY_DOWN)
		{
			index++;
			if (index >= 7)
				index = 6;
		}
		if (k == KEY_UP)
		{
			index--;
			if (index < 0)
			{
				index = 0;
			}
		}
		if (k == KEY_RIGHT || k == '\n')
		{
			switch (index)
			{
			case 0:
				state->autoarchive = !(state->autoarchive);
				break;
			case 1:
				state->saveprompt = !(state->saveprompt);
				break;
			case 2:
				state->useregex = !(state->useregex);
				break;
			case 3:
				state->blinkcursor = !(state->blinkcursor);
				break;
			case 4:
				state->backupfiles = !(state->backupfiles);
				break;
			case 5:
				state->bos_use_system_config = !(state->bos_use_system_config);
				break;
			case 6:
				state->bos_use_extra_buffer = !(state->bos_use_extra_buffer);
				break;
			}
		}
	}
}

void show_keybind_dialog(struct estate *state)
{
	//short k = 0;
	draw_dialog(state, 40, 40, 240, 160);
	gfx_SetColor(state->border_color);
	gfx_HorizLine_NoClip(40, 60, 240);
	fontlib_SetCursorPosition(80, 45);
	fontlib_SetForegroundColor(state->text_color);
	fontlib_DrawString("Keybind Information");
	fontlib_SetCursorPosition(51, 62);
	fontlib_DrawString("Press [CLEAR] to quit.");
	fontlib_SetCursorPosition(51, 74);
	fontlib_DrawString("Hold modifiers like 2nd.");
	fontlib_SetCursorPosition(51, 86);
	fontlib_DrawString("See docs for more info.");
	gfx_BlitBuffer();
	ngetchx();
}

void show_appearance_settings_dialog(struct estate *state)
{
	short k = 0;
	int index = 0;
	while (k != KEY_CLEAR)
	{
		draw_dialog(state, 20, 20, 280, 200);
		gfx_SetColor(state->border_color);
		gfx_HorizLine_NoClip(20, 40, 280);
		fontlib_SetCursorPosition(84, 25);
		fontlib_SetForegroundColor(state->text_color);
		fontlib_DrawString("Appearance Settings");

		fontlib_SetCursorPosition(45, 45);
		fontlib_SetForegroundColor(
			index == 0 ? state->focus_color : state->text_color);
		fontlib_DrawString("Text color");

		fontlib_SetCursorPosition(45, 57);
		fontlib_SetForegroundColor(
			index == 1 ? state->focus_color : state->text_color);
		fontlib_DrawString("Text highlight color");

		fontlib_SetCursorPosition(45, 69);
		fontlib_SetForegroundColor(
			index == 2 ? state->focus_color : state->text_color);
		fontlib_DrawString("Text selection color");

		fontlib_SetCursorPosition(45, 81);
		fontlib_SetForegroundColor(
			index == 3 ? state->focus_color : state->text_color);
		fontlib_DrawString("Text selection highlight color");

		fontlib_SetCursorPosition(45, 93);
		fontlib_SetForegroundColor(
			index == 4 ? state->focus_color : state->text_color);
		fontlib_DrawString("Background color");

		fontlib_SetCursorPosition(45, 105);
		fontlib_SetForegroundColor(
			index == 5 ? state->focus_color : state->text_color);
		fontlib_DrawString("Transparent color");

		fontlib_SetCursorPosition(45, 117);
		fontlib_SetForegroundColor(
			index == 6 ? state->focus_color : state->text_color);
		fontlib_DrawString("Status bar color");

		fontlib_SetCursorPosition(45, 129);
		fontlib_SetForegroundColor(
			index == 7 ? state->focus_color : state->text_color);
		fontlib_DrawString("Status bar text color");

		fontlib_SetCursorPosition(45, 141);
		fontlib_SetForegroundColor(
			index == 8 ? state->focus_color : state->text_color);
		fontlib_DrawString("Border color");

		fontlib_SetCursorPosition(45, 153);
		fontlib_SetForegroundColor(
			index == 9 ? state->focus_color : state->text_color);
		fontlib_DrawString("Drop shadow color");

		fontlib_SetCursorPosition(45, 165);
		fontlib_SetForegroundColor(
			index == 10 ? state->focus_color : state->text_color);
		fontlib_DrawString("Focus color");

		gfx_SetColor(state->text_color);
		gfx_FillRectangle_NoClip(31, 46, 10, 10);
		gfx_SetColor(state->text_highlight_color);
		gfx_FillRectangle_NoClip(31, 58, 10, 10);
		gfx_SetColor(state->text_selection_color);
		gfx_FillRectangle_NoClip(31, 70, 10, 10);
		gfx_SetColor(state->text_selection_highlight_color);
		gfx_FillRectangle_NoClip(31, 82, 10, 10);
		//sike!
		//gfx_SetColor(state->background_color);
		//gfx_FillRectangle_NoClip(31, 94, 10, 10);
		//Sike!
		//gfx_SetColor(state->transparent_color);
		//gfx_FillRectangle_NoClip(31, 106, 10, 10);
		gfx_SetColor(state->statusbar_color);
		gfx_FillRectangle_NoClip(31, 118, 10, 10);
		gfx_SetColor(state->statusbar_text_color);
		gfx_FillRectangle_NoClip(31, 130, 10, 10);
		gfx_SetColor(state->border_color);
		gfx_FillRectangle_NoClip(31, 142, 10, 10);
		gfx_SetColor(state->dropshadow_color);
		gfx_FillRectangle_NoClip(31, 154, 10, 10);
		gfx_SetColor(state->focus_color);
		gfx_FillRectangle_NoClip(31, 166, 10, 10);

		fontlib_SetForegroundColor(state->text_color);
		fontlib_SetCursorPosition(31, 178);
		fontlib_DrawString("These settings are temporary.");
		fontlib_SetCursorPosition(31, 190);
		fontlib_DrawString("Edit CEDITRC to make changes");
		fontlib_SetCursorPosition(31, 202);
		fontlib_DrawString("permanent.");

		gfx_BlitBuffer();
		k = ngetchx();
		if (k == KEY_RIGHT || k == '\n')
		{
			switch (index)
			{
			case 0:
				state->text_color = show_color_selection_dialog(state, state->text_color);
				/*gfx_FillScreen(255);
				fontlib_SetForegroundColor(state->text_color);
				fontlib_SetCursorPosition(0,0);
				fontlib_DrawUInt(state->text_color,1);
				gfx_BlitBuffer();
				ngetchx();*/
				break;
			case 1:
				state->text_highlight_color = show_color_selection_dialog(state, state->text_highlight_color);
				break;
			case 2:
				state->text_selection_color = show_color_selection_dialog(state, state->text_selection_color);
				break;
			case 3:
				state->text_selection_highlight_color = show_color_selection_dialog(state, state->text_selection_highlight_color);
				break;
			case 4:
				state->background_color = show_color_selection_dialog(state, state->background_color);
				break;
			case 5:
				state->transparent_color = show_color_selection_dialog(state, state->transparent_color);
				break;
			case 6:
				state->statusbar_color = show_color_selection_dialog(state, state->statusbar_color);
				break;
			case 7:
				state->statusbar_text_color = show_color_selection_dialog(state, state->statusbar_text_color);
				break;
			case 8:
				state->border_color = show_color_selection_dialog(state, state->border_color);
				break;
			case 9:
				state->dropshadow_color = show_color_selection_dialog(state, state->dropshadow_color);
				break;
			case 10:
				state->focus_color = show_color_selection_dialog(state, state->focus_color);
				break;
			}
		}
		if (k == KEY_UP)
		{
			if (index)
			{
				index--;
			}
		}
		if (k == KEY_DOWN)
		{
			if (index < 10)
			{
				index++;
			}
		}
	}
}

//TODO embed color picker in dialog
void show_appearance_settings_dialog_nocolor(struct estate *state)
{
	short k = 0;
	int index = 0;
	while (k != KEY_CLEAR)
	{
		draw_dialog(state, 20, 20, 280, 200);
		gfx_SetColor(state->border_color);
		gfx_HorizLine_NoClip(20, 40, 280);
		fontlib_SetCursorPosition(84, 25);
		fontlib_SetForegroundColor(state->text_color);
		fontlib_DrawString("Appearance Settings");
		fontlib_SetCursorPosition(45, 45);
		fontlib_SetForegroundColor(
			index == 0 ? state->focus_color : state->text_color);
		fontlib_DrawString("Text color");

		fontlib_SetCursorPosition(45, 57);
		fontlib_SetForegroundColor(
			index == 1 ? state->focus_color : state->text_color);
		fontlib_DrawString("Text highlight color");

		fontlib_SetCursorPosition(45, 69);
		fontlib_SetForegroundColor(
			index == 2 ? state->focus_color : state->text_color);
		fontlib_DrawString("Text selection color");

		fontlib_SetCursorPosition(45, 81);
		fontlib_SetForegroundColor(
			index == 3 ? state->focus_color : state->text_color);
		fontlib_DrawString("Text selection highlight color");

		fontlib_SetCursorPosition(45, 93);
		fontlib_SetForegroundColor(
			index == 4 ? state->focus_color : state->text_color);
		fontlib_DrawString("Background color");

		fontlib_SetCursorPosition(45, 105);
		fontlib_SetForegroundColor(
			index == 5 ? state->focus_color : state->text_color);
		fontlib_DrawString("Transparent color");

		fontlib_SetCursorPosition(45, 117);
		fontlib_SetForegroundColor(
			index == 6 ? state->focus_color : state->text_color);
		fontlib_DrawString("Status bar color");

		fontlib_SetCursorPosition(45, 129);
		fontlib_SetForegroundColor(
			index == 7 ? state->focus_color : state->text_color);
		fontlib_DrawString("Status bar text color");

		fontlib_SetCursorPosition(45, 141);
		fontlib_SetForegroundColor(
			index == 8 ? state->focus_color : state->text_color);
		fontlib_DrawString("Border color");

		fontlib_SetCursorPosition(45, 153);
		fontlib_SetForegroundColor(
			index == 9 ? state->focus_color : state->text_color);
		fontlib_DrawString("Drop shadow color");

		fontlib_SetCursorPosition(45, 165);
		fontlib_SetForegroundColor(
			index == 10 ? state->focus_color : state->text_color);
		fontlib_DrawString("Focus color");

		gfx_SetColor(state->text_color);
		gfx_FillRectangle_NoClip(31, 46, 10, 10);
		gfx_SetColor(state->text_highlight_color);
		gfx_FillRectangle_NoClip(31, 58, 10, 10);
		gfx_SetColor(state->text_selection_color);
		gfx_FillRectangle_NoClip(31, 70, 10, 10);
		gfx_SetColor(state->text_selection_highlight_color);
		gfx_FillRectangle_NoClip(31, 82, 10, 10);
		//sike!
		//gfx_SetColor(state->background_color);
		//gfx_FillRectangle_NoClip(31, 94, 10, 10);
		//Sike!
		//gfx_SetColor(state->transparent_color);
		//gfx_FillRectangle_NoClip(31, 106, 10, 10);
		gfx_SetColor(state->statusbar_color);
		gfx_FillRectangle_NoClip(31, 118, 10, 10);
		gfx_SetColor(state->statusbar_text_color);
		gfx_FillRectangle_NoClip(31, 130, 10, 10);
		gfx_SetColor(state->border_color);
		gfx_FillRectangle_NoClip(31, 142, 10, 10);
		gfx_SetColor(state->dropshadow_color);
		gfx_FillRectangle_NoClip(31, 154, 10, 10);
		gfx_SetColor(state->focus_color);
		gfx_FillRectangle_NoClip(31, 166, 10, 10);

		fontlib_SetForegroundColor(state->text_color);
		fontlib_SetCursorPosition(31, 178);
		fontlib_DrawString("These settings are temporary.");
		fontlib_SetCursorPosition(31, 190);
		fontlib_DrawString("Edit CEDITRC to make changes");
		fontlib_SetCursorPosition(31, 202);
		fontlib_DrawString("permanent.");

		gfx_BlitBuffer();
		k = ngetchx();
		if (k == KEY_RIGHT || k == '\n')
		{
			show_color_selection_dialog(state, 1);
		}
		if (k == KEY_UP)
		{
			if (index)
			{
				index--;
			}
		}
		if (k == KEY_DOWN)
		{
			if (index < 10)
			{
				index++;
			}
		}
	}
}

/*
 * Draws the main menu given the state parameters and the selection index
 */
void menu_backend_draw(struct estate *state, int index)
{
	draw_dialog(state, 20, 20, 280, 200);
	gfx_SetColor(state->border_color);
	gfx_HorizLine_NoClip(20, 40, 280);
	fontlib_SetCursorPosition(104, 25);
	fontlib_SetForegroundColor(state->text_color);
	fontlib_DrawString("CEdit Settings");
	fontlib_SetCursorPosition(30, 45);
	if (index == 0)
	{
		fontlib_SetForegroundColor(state->focus_color);
		//fontlib_DrawString(">");
	}
	fontlib_DrawString("Editor Settings");
	fontlib_SetForegroundColor(state->text_color);
	fontlib_SetCursorPosition(30, 60);
	if (index == 1)
	{
		fontlib_SetForegroundColor(state->focus_color);
		//fontlib_DrawString(">");
	}
	fontlib_DrawString("Appearance Settings");
	fontlib_SetForegroundColor(state->text_color);
	fontlib_SetCursorPosition(30, 75);
	if (index == 2)
	{
		fontlib_SetForegroundColor(state->focus_color);
		//fontlib_DrawString(">");
	}
	fontlib_DrawString("Persistence Settings");
	fontlib_SetForegroundColor(state->text_color);
	fontlib_SetCursorPosition(30, 90);
	if (index == 3)
	{
		fontlib_SetForegroundColor(state->focus_color);
		//fontlib_DrawString(">");
	}
	fontlib_DrawString("About Cedit");
	fontlib_SetForegroundColor(state->text_color);
	fontlib_SetCursorPosition(30, 105);
	if (index == 4)
	{
		fontlib_SetForegroundColor(state->focus_color);
		//fontlib_DrawString(">");
	}
	fontlib_DrawString("Keybind information");
	fontlib_SetForegroundColor(state->text_color);
	fontlib_SetCursorPosition(30, 120);
	if (index == 5)
	{
		fontlib_SetForegroundColor(state->focus_color);
		//fontlib_DrawString(">");
	}
	fontlib_DrawString("Bug report");
	fontlib_SetForegroundColor(state->text_color);
	fontlib_SetCursorPosition(30, 135);
	if (index == 6)
	{
		fontlib_SetForegroundColor(state->focus_color);
		//fontlib_DrawString(">");
	}
	fontlib_DrawString("Back");
	fontlib_SetForegroundColor(state->text_color);
	fontlib_SetCursorPosition(30, 150);
	if (index == 7)
	{
		fontlib_SetForegroundColor(state->focus_color);
		//fontlib_DrawString(">");
	}
	fontlib_DrawString("Quit CEdit");
}

void show_persistence_dialog(struct estate *state)
{
	//short k = 0;
	draw_dialog(state, 20, 20, 280, 200);
	gfx_SetColor(state->border_color);
	gfx_HorizLine_NoClip(20, 40, 280);
	fontlib_SetCursorPosition(100, 25);
	fontlib_SetForegroundColor(state->text_color);
	fontlib_DrawString("Editor Settings");
	fontlib_SetCursorPosition(31, 42);
	fontlib_DrawString("Changing settings graphically is");
	fontlib_SetCursorPosition(31, 54);
	fontlib_DrawString("not currently supported.");
	fontlib_SetCursorPosition(31, 66);
	fontlib_DrawString("Please edit CEDITRC instead.");
	gfx_BlitBuffer();
	ngetchx();
}

void show_menu_dialog(struct estate *state)
{
	short k = 0;
	int index = 0;
	while (k != KEY_CLEAR)
	{
		if (k == '\n' || k == KEY_RIGHT)
		{
			switch (index)
			{
			case 0:
				show_editor_settings_dialog(state);
				break;
			case 1:
				show_appearance_settings_dialog(state);
				break;
			case 2:
				show_persistence_dialog(state);
				break;
			case 3:
				show_about_dialog(state);
				break;
			case 4:
				show_keybind_dialog(state);
				break;
			case 5:
				break;
			case 6:
				return;
			case 7:
				gfx_End();
				exit(0);
			}
		}
		if (k == KEY_UP)
		{
			if (index)
			{
				index--;
			}
		}
		if (k == KEY_DOWN)
		{
			if (index < 7)
			{
				index++;
			}
		}
		menu_backend_draw(state, index);

		gfx_BlitBuffer();
		k = ngetchx();
	}
}

void draw_dialog(struct estate *state, int x, int y, int w, int h)
{
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

int min(int a, int b)
{
	return a < b ? a : b;
}

#ifdef BOS_BUILD
//TODO!!!
#else
bool show_open_dialog(struct estate *state)
{

	const int num_rows = 13;
	short k = 0;
	//Selected index
	int index = 0;
	//index on screen
	int sindex = 0;
	//index of start of screen
	int scrstart = 0;
	char *var_name;
	void *search_pos = NULL;
	int i = 0;
	void *arr;
	os_MemChk(&arr);
	//array is blocked into 24s first 8 chars are the title, next 16 are the first characters of the file
	while ((var_name = ti_Detect(&search_pos, NULL)) != NULL)
	{
		strncpy((char *)arr + 24 * i, var_name, 8);
		ti_var_t slot1 = ti_Open(var_name, "r");
		for (int j = 0; j < 16; j++)
		{
			char c = ti_GetC(slot1);
			if (c == EOF)
				break;
			//Save the char
			*((char *)arr + 24 * i + 8 + j) = c;
		}
		ti_Close(slot1);
		i++;
	}
	int numfiles = i;
	while (k != KEY_CLEAR)
	{
		draw_dialog(state, 20, 20, 280, 200);
		gfx_SetColor(state->border_color);
		gfx_HorizLine_NoClip(20, 40, 280);
		fontlib_SetCursorPosition(84, 25);
		fontlib_SetForegroundColor(state->text_color);
		fontlib_DrawString("Open File (filename)");
		fontlib_SetCursorPosition(45, 205);
		fontlib_DrawString("Press enter to open");
		gfx_SetColor(state->statusbar_color);
		gfx_Rectangle_NoClip(25, 45, 270, 160);
		gfx_SetColor(state->border_color);
		gfx_Rectangle_NoClip(26, 46, 270, 160);
		for (i = 0; i < min(num_rows, numfiles); i++)
		{
			if (i == sindex)
			{
				fontlib_SetForegroundColor(state->focus_color);
				gfx_SetColor(state->statusbar_color);
				gfx_FillRectangle_NoClip(27, 46 + 12 * i, 268, 12);
			}
			else
			{
				fontlib_SetForegroundColor(state->text_color);
			}
			//Set initial cursor position
			fontlib_SetCursorPosition(32, 45 + 12 * i);
			//Draw the name
			fontlib_DrawStringL(arr + 24 * (i + scrstart), 8);
			//Draw separator
			fontlib_SetCursorPosition(32 + 8 * 8, 12 * i + 45);
			fontlib_DrawString(" - ");
			//Draw file preview.
			fontlib_DrawStringL(arr + 24 * (i + scrstart) + 8, 16);
		}
		gfx_BlitBuffer();
		k = ngetchx();
		if (k == KEY_UP)
		{
			index--;
			if (index < 0)
				index = 0;
			sindex--;
			if (sindex < 0)
			{
				sindex = 0;
				scrstart--;
				if (scrstart < 0)
				{
					scrstart = 0;
				}
			}
		}
		if (k == KEY_DOWN)
		{
			index++;
			if (index >= numfiles)
				index = numfiles;
			sindex++;
			if (sindex >= num_rows)
			{
				sindex = num_rows - 1;
				scrstart++;
				if (scrstart >= numfiles - num_rows)
				{
					if (numfiles - num_rows > 0)
					{
						scrstart = numfiles - num_rows;
					}
					else
					{
						scrstart = 0;
					}
				}
			}
			//Edge case - no trap
			if (sindex >= numfiles)
			{
				sindex = numfiles - 1;
			}
		}
		if (k == '\n')
		{
			if (state->saved || show_unsaved_dialog(state))
			{
				strncpy(state->filename, (char *)arr + 24 * index, 8);
				initialize(state);
				parseRC(state);
				load_text(state);
				state->named = true;
				return true;
			}
		}
	}
	return false;
}
#endif

//==========================//END_OF_OPEN_FUNCTIONS//==========================//

//1 means canceled
bool show_save_dialog(struct estate *state)
{
	short k = 0;
	int numchars = 0;
#ifdef BOS_BUILD
	char buffer[256];
	memset(buffer, 0, 256);
#else
	char buffer[9];
	memset(buffer, 0, 9);
#endif

	int cx = 52;
	while (true)
	{
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
		if (k == KEY_CLEAR)
		{
			return true;
		}
		if (k == '\n')
		{
			if (!numchars)
			{
				return true;
			}
			state->named = true;
#ifdef BOS_BUILD
			strncpy(state->filename, buffer, 256);
#else
			strncpy(state->filename, buffer, 8);
#endif
			return false;
		}
		if (!is_control(k))
		{
#ifdef BOS_BUILD
			if (numchars < 255)
#else
			if (numchars < 8)
#endif
			{
				buffer[numchars] = k;
				numchars++;
			}
		}
		if (k == KEY_BS)
		{
			if (numchars)
				buffer[--numchars] = 0;
		}
	}
	return false;
}

void show_about_dialog(struct estate *state)
{
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

bool show_unsaved_dialog(struct estate *state)
{
	draw_dialog(state, 60, 60, 200, 120);
	gfx_SetColor(state->border_color);
	gfx_HorizLine_NoClip(60, 80, 200);
	//fontlib_SetCursorPosition(115,80);
	fontlib_SetCursorPosition(115, 65);
	fontlib_DrawString("Warning: Unsaved");
	fontlib_SetCursorPosition(80, 120);
	fontlib_DrawString("Press enter to discard unsaved changes");
	gfx_BlitBuffer();
	short k = ngetchx();
	if (k == '\n')
	{
		return true;
	}
	return false;
}
