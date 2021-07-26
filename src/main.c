/*
 * main.c
 *
 *  Created on: Jul 25, 2021
 *      Author: michael
 */

#include "state.h"
#include "cedit.h"
#include "tigcclib.h"
#include "editor.h"
#include "dialogs.h"
#include "gfx.h"

bool initialize(struct estate *state) {
	state->multi_lines = 5;
	strncpy("Untitled", state->filename, 8);
	state->named = false;
	state->lc1 = 0;
	state->lc2 = MAX_BUFFER_SIZE - 1;
	state->lc_offset = 0;
	state->ls_offset = 0;
	state->c1 = 0;
	state->c2 = MAX_BUFFER_SIZE - 1;
	state->scr_offset = 0;
	state->scr_line_offset = 0;
	state->text_color = 0;
	state->text_highlight_color = 1;
	state->text_selection_color = 1;
	state->text_selection_highlight_color = 30;
	state->background_color = 255;
	state->transparent_color = 1;
	state->statusbar_text_color = 255;
	state->statusbar_color = 13;
	state->border_color = 0;
	state->dropshadow_color = 11;
	strncpy("DrMono", state->fontname);
	state->saved=true;
	state->fonttype = 3;
	state->font = fontlib_GetFontByIndex(state->fontname, state->fonttype);
	if (!state->font) {
		os_ClrHome();
		os_PutStrFull("E1: Font pack not found.");
		ngetchx();
		return 1;
	}
	fontlib_SetFont(state->font, 0);
	fontlib_SetForegroundColor(state->text_color);
	fontlib_SetTransparency(state->transparent_color);
	fontlib_SetBackgroundColor(state->text_highlight_color);
	load_text(state);
	return 0;
}

void main(int argc, char **argv) {
	static struct estate editor_state;

	if (initialize(editor_state)) {
		os_ClrHome();
		os_PutStrFull("E0: gfx-err");
		ngetchx();
		return;
	}
	//Argument parsing
	if (argc == 2) {
		strncpy(filename, argv[1], 8);
		named = true;
	} else if (argc > 2) {
		os_ClrHome();
		os_PutStrFull("Usage: CEdit FILE");
		while (!os_GetCSC())
			continue;
		return;
	}
	gfx_Begin();
	editor_mainloop();
	gfx_End();
}
