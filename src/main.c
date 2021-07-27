/*
 * main.c
 *
 *  Created on: Jul 25, 2021
 *      Author: michael
 */

#include "cedit.h"


bool initialize(struct estate *state) {
	char buf1[10]="Untitled";
	char buf2[10]="DrMono";
	state->multi_lines = 5;
	strncpy(buf1, state->filename, 10);
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
	state->text_highlight_color = 255;
	state->text_selection_color = 120;
	state->text_selection_highlight_color = 30;
	state->background_color = 255;
	state->transparent_color = 1;
	state->statusbar_text_color = 255;
	state->statusbar_color = 11;
	state->border_color = 0;
	state->dropshadow_color = 10;
	state->focus_color=142;
	strncpy(buf2, state->fontname,10);
	state->saved=true;
	state->fonttype = 3;
	state->font = fontlib_GetFontByIndex("DrMono", state->fonttype);
	state->clipboard_size = 0;
	state->corner_radius=10;
	if (!state->font) {
		os_ClrHome();
		os_PutStrFull("E1: Font pack not found.");
		ngetchx();
		return 1;
	}
	fontlib_SetFont(state->font, 0);
	fontlib_SetForegroundColor(state->text_color);
	fontlib_SetTransparency(true);
	fontlib_SetBackgroundColor(state->text_highlight_color);

	return 0;
}

int main(int argc, char **argv) {
	static struct estate editor_state;

	if (initialize(&editor_state)) {
		os_ClrHome();
		os_PutStrFull("E0: gfx-err");
		ngetchx();
		return 1;
	}
	//Argument parsing
	if (argc == 2) {
		strncpy(editor_state.filename, argv[1], 8);
		editor_state.named = true;
	} else if (argc > 2) {
		os_ClrHome();
		os_PutStrFull("Usage: CEdit [FILE]");
		while (!os_GetCSC())
			continue;
		return 1;
	}else{
		//Put a little help blurb
	}
	load_text(&editor_state);
	gfx_Begin();
	editor_mainloop(&editor_state);
	gfx_End();
	return 0;
}
