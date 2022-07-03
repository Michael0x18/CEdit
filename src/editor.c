#include "editor.h"
#include <limits.h>

void redraw_editor(struct estate *state)
{
	const int8_t title_offset = 1;

	// x4_FillScreen(EDIT_BG_COLOR);
	//  x4_FillRectangle(0, 0, 320, 16, STAT_BG_COLOR);
	x4_PutStr(state->font_buffer_statusbar, 230, 0, "CEdit V2.0");
	x4_PutStr(state->font_buffer_statusbar, title_offset, 0, state->filename);
	if (!state->saved || !state->named)
	{
		x4_PutChar(state->font_buffer, title_offset + 9 * strlen(state->filename), 0, '*');
	}

	uint8_t r = 0;
	uint8_t c = 0;

	// x4_PutChar(state->font_buffer, 9, 16, state->text[state->cursor_left - 1]);

	for (uint24_t i = state->screen_start_offset; i < state->cursor_left; i++)
	{
		x4_PutChar(state->font_buffer, 1 + c * 9, r * 16 + 16, state->text[i]);
		c++;
		if (c >= 35)
		{
			c = 0;
			r++;
		}
		if (r >= 13)
		{
			break;
		}
	}

	// x4_FillRectangle(0, 224, 320, 16, STAT_BG_COLOR);
}

void draw_shell(struct estate *state)
{
	x4_FillScreen(EDIT_BG_COLOR);
	x4_FillRectangle(0, 0, 320, 16, STAT_BG_COLOR);
}

void editor_mainloop(struct estate *state)
{
	draw_shell(state);
	cedit_swapdraw(state);
	draw_shell(state);
	while (1)
	{
		redraw_editor(state);
		cedit_swapdraw(state);
		char k = 0;
		while (!k)
		{
			k = ngetchx(state);
			// dbg_printf("waiting\n");
			// delay(5);
		}
		// dbg_printf("got keypress\n");
		if (k == KEY_ESCAPE)
		{
			break;
		}
		if (is_control(k))
		{
		}
		else
		{
			insert_char(state, k);
			// dbg_printf("Inserting char: %d\n", k);
		}
		delay(10);
	}
}

bool is_control(char k)
{
	return k < 9 || k >= 127;
}

void insert_char(struct estate *state, char c)
{
	state->text[state->cursor_left++] = c;
}