#include "config.h"

void cedit_init(struct estate *state)
{

	// Load defaults
	cedit_defaults(state);
	// Overwrite some defaults with RC file
	parse_rc(state);
}

void cedit_defaults(struct estate *state)
{
	// Initialize estate
	state->text = mktextbuffer(X4_BUFFER_3, 65536, x4_Buffer_3 + 65537 + 5, 256);
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
	state->config->scr_height = 12;
	state->config->archive_on_save = false;
}

void parse_rc(struct estate *state)
{
	// TODO
}