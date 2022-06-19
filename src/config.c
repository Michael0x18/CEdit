#include "cedit.h"
#include "config.h"

void load_rc(struct estate *state)
{
	initialize_default_state(state);
}

void initialize_default_state(struct estate *state)
{
	state->max_file_size = 65536;
	state->cursor_left = 0;
	state->cursor_right = 65536;
	state->highlight_anchor = 0;
	state->highlight_enabled = false;
	state->saved = false;
	state->named = false;
	state->filename = "UNTITLED";
}

void initialize_x4(void)
{
	x4_Begin;
	x4_SetDrawLocation(X4_BUFFER_1);
}