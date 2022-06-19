#include "editor.h"

void redraw_editor(struct estate *state)
{
	x4_FillScreen(EDIT_BG_COLOR);
	x4_FillRectangle(0, 0, 320, 16, STAT_BG_COLOR);
	x4_PutStr(state->font_buffer_statusbar, 230, 0, "CEdit V2.0");
}