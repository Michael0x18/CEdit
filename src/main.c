/*
 * main.c
 *
 *  Created on: Jul 25, 2021
 *      Author: michael
 *      Edited for BOS by Beck
 */

#include "cedit.h"
#ifdef BOS_BUILD
#include <bos.h>
#endif

bool initialize(struct estate *state) {
#ifdef BOS_BUILD
	fontlib_font_pack_t *font;
#endif
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

	state->clipboard_size = 0;
	state->corner_radius=10;
	state->eof = 0;

	state->font = 0;
	state->fonttype = 3;
#ifdef BOS_BUILD
	if ((font = (fontlib_font_pack_t*)fs_GetFilePtr("/etc/fonts/DrMono")) == -1) {
		if (font->fontCount >= state->fonttype){
			state->font = font->font_list[state->fonttype];
		}
	}
	if (!state->font) {
		os_ClrHome();
		os_PutStrFull("E1: Font pack not found.");
		return 1;
	}
#else
	state->font = fontlib_GetFontByIndex("DrMono", state->fonttype);

	if (!state->font) {
		os_ClrHome();
		os_PutStrFull("E1: Font pack not found.");
		return 1;
	}
#endif
	if (!fontlib_SetFont(state->font, 0)){
		os_ClrHome();
		os_PutStrFull("E2: Font pack Invalid.");
		return 1;
	}
	fontlib_SetForegroundColor(state->text_color);
	fontlib_SetTransparency(true);
	fontlib_SetBackgroundColor(state->text_highlight_color);

	return 0;
}

#ifdef BOS_BUILD
int main(int argc, char **argv) {
	char *args = (char*)argc;
	static struct estate editor_state;

	if (initialize(&editor_state)) {
		os_ClrHome();
		os_PutStrFull("E0: gfx-err");
		ngetchx();
		return 1;
	}
	editor_state.filename = sys_Malloc(256);
	//Argument parsing
	if (*args) {
		memcpy(editor_state.filename, args, 256);
		editor_state.named = true;
	}
	load_text(&editor_state);
	gfx_Begin();
	editor_mainloop(&editor_state);
	gfx_End();
	return 0;
}
#else
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
#endif
