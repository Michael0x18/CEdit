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
		x4_PutStr(state->font_buffer, 10, 16 + 16 * r, state->cache + r * (1 + state->config->scr_width));
	}
}

void render_to_cache(struct estate *state)
{
	uint24_t offset = 0;
	for (int r = 0; r < state->config->scr_height; r++)
	{
		for (int c = 0; c < state->config->scr_width; c++)
		{
			if (offset + state->screen_start_offset >= state->text->size)
			{
				dbg_printf("Offset is %d, with max %d. Exiting.", offset + state->screen_start_offset, state->text->size);
				goto end;
			}
			dbg_printf("%c", textbuffer_get(state->text, offset));
			state->cache[r * (state->config->scr_width + 1) + c] =
				textbuffer_get(state->text,
							   state->screen_start_offset + offset);
			if (state->cache[r * (state->config->scr_width + 1) + c] == '\n')
			{
				break;
			}
		}
	}
end:;
	dbg_printf("Done rendering\n");
}