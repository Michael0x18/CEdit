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
	x4_PutStr(state->font_buffer_statusbar, 0, 0, state->filename);
}