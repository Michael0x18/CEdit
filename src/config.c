#include "config.h"

bool cedit_init(struct estate *state)
{

	// Load defaults
	return cedit_defaults(state) || parse_rc(state);
	// Overwrite some defaults with RC file
}

bool cedit_defaults(struct estate *state)
{
	// Initialize estate
	state->text = mktextbuffer(X4_BUFFER_3, 65536, X4_BUFFER_3 + 65537 + 5, 256);
	state->config = (struct cedit_config *)malloc(sizeof(struct cedit_config));
	state->saved = false;
	state->named = false;
	state->hidden = false;
	memcpy(state->filename, "UNTITLED", 8);
	memcpy(state->clipboard_var, "CLIPDATA", 8);
	state->timeout_max = 100;
	state->timeout_first = 20;

	// initialize config
	state->config->wordwrap = false;
	state->config->blink_cursor = false;
	state->config->scr_width = 34;
	state->config->scr_height = 13;
	state->config->archive_on_save = false;

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
	x4_load_default_font(state->font_buffer_statusbar, 6, 7);

	state->screen_start_offset = 0;
	state->cursor = 0;

	state->cache = (char *)malloc((state->config->scr_width + 1) *
								  (state->config->scr_height));

	return 0;
}

bool parse_rc(struct estate *state)
{
	// TODO
	return 0;
}