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
	state->cursor_right = state->max_file_size - 1;
	state->highlight_anchor = 0;
	state->highlight_enabled = false;
	state->saved = false;
	state->named = false;
	memcpy(state->filename, "UNTITLED", 8);
	state->hidden = false;
	memcpy(state->clipboard_var, "CLIPDATA", 8);
	state->text = X4_BUFFER_3;
	state->wordwrap = false;
	state->mouse_enabled = false;
	state->blink_cursor = true;
	state->screen_start_offset = 0;
	state->screen_line_raw_offset = 0;
	state->screen_line_actual_offset = 0;
	state->screen_line_sub_offset = 0;
	state->screen_end_offset = 0;
	state->cursor_x = 0;
	state->cursor_y = 0;
	state->num_lines = 0;
	state->cursor_line_raw = 0;
	state->scr_width = 34;
	state->scr_height = 12;

	gfx_palette[0] = 0;
	gfx_palette[1] = 0xFFFF;
	gfx_palette[2] = 0;
	gfx_palette[3] = 6318;
	gfx_palette[4] = 0x025F;
	gfx_palette[5] = 0xFFFF;
	gfx_palette[6] = 0xFFFF;
	gfx_palette[7] = 0x025F;
	gfx_palette[8] = 0xFFFF;
	gfx_palette[9] = 6318;

	x4_load_default_font(state->font_buffer, 0, 1);
	// x4_load_default_font(state->font_buffer_highlight, 2, 3);
	// x4_load_default_font(state->font_buffer_select, 4, 5);
	x4_load_default_font(state->font_buffer_statusbar, 6, 7);

	state->cedit_enable_triplebuffer = false;

	state->timeout_first = 20;
	state->timeout_max = 100;
}

void initialize_x4(void)
{
	x4_Begin();
	x4_SetScreenLocation(X4_BUFFER_1);
	x4_SetDrawLocation(X4_BUFFER_2);
}

void release_x4(void)
{
	x4_SetScreenLocation(X4_BUFFER_1);
	x4_End();
}