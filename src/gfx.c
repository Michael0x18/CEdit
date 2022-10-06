#include "gfx.h"

void init_x4(void)
{
	x4_Begin();
	x4_SetScreenLocation(X4_BUFFER_1);
	x4_SetDrawLocation(X4_BUFFER_2);
}

void end_x4(void)
{
	x4_SetScreenLocation(X4_BUFFER_1);
	x4_End();
}

void draw_shell(struct estate *state)
{
	x4_FillScreen(TEXT_BG_COLOR);
	x4_FillRectangle(0, 0, 320, 16, STAT_BG_COLOR);
}

void cedit_swapdraw(void)
{
	static bool state = false;
	if (state)
	{
		x4_SetDrawLocation(X4_BUFFER_2);
		x4_SetScreenLocation(X4_BUFFER_1);
	}
	else
	{
		x4_SetDrawLocation(X4_BUFFER_1);
		x4_SetScreenLocation(X4_BUFFER_2);
	}
	state = !state;
}

void redraw_editor(struct estate *state)
{
	////Draw top status bar////
	x4_PutStr(state->font_buffer_statusbar, 1, 0, state->filename);
	x4_PutChar(state->font_buffer_statusbar, 1 + 9 * strlen(state->filename), 0, state->saved ? ' ' : '*');
	////Draw meat of editor////
	for (int r = 0; r < state->config->scr_height; r++)
	{
		dbg_printf("=%s=\n", state->cache + r * (1 + state->config->scr_width));
		x4_PutStr(state->font_buffer, 10, 16 + 16 * r, state->cache + r * (1 + state->config->scr_width));
	}
	x4_Line_EFLA(10 + 9 * state->cursor_x, 16 + 16 * state->cursor_y, 10 + 9 * state->cursor_x, 32 + 16 * state->cursor_y, TEXT_FG_COLOR);
}

void render_to_cache(struct estate *state)
{
	// uint24_t offset = state->screen_start_offset;
	// for (int r = 0; r < state->config->scr_height; r++)
	// {
	// 	bool newline = true;
	// 	for (int c = 0; c < state->config->scr_width; c++)
	// 	{
	// 		char w = '!';
	// 		if(!newline && offset < state->text->size){
	// 			w = textbuffer_get(state->text, offset)
	// 		}
	// 	}
	// }

	uint24_t offset = state->screen_start_offset;
	for (int r = 0; r < state->config->scr_height; r++)
	{
		bool newline = false;
		for (int c = 0; c < state->config->scr_width; c++)
		{
			char w = ' ';
			if (!newline && offset < state->text->size)
			{
				w = textbuffer_get(state->text, offset);
				dbg_printf("%c", w);
				if (state->cache[r * (state->config->scr_width + 1) + c] == '\n')
				{
					newline = true;
					// break;
				}
				offset++;
			}
			dbg_printf("%c", w);
			state->cache[r * (state->config->scr_width + 1) + c] = w;
		}
	}
	dbg_printf("Done rendering\n");
}