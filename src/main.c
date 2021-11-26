/*
 * main.c
 *
 *  Created on: Jul 25, 2021
 *      Author: michael
 *      Edited for BOS by Beck
 */

#include "cedit.h"
#include "libmalloc.h"
#ifdef BOS_BUILD
#include <bos.h>
#define BOS_SAFERAM 0xD00E00
void gui_PrintLine_wrapper(const char *str);
#endif

bool initialize(struct estate *state)
{
#ifdef BOS_BUILD
	fontlib_font_pack_t *font;
	state->lines = sys_Malloc(10000 * sizeof(int16_t));
#else
	char fontname[10] = "DrMono";
#endif
    memset(state->search_buffer,0,255);
	//Default is false, if true, files will be archived after writes. Does nothing on BOS.
	state->autoarchive = false;
	//Default is true, if enabled, unsaved file = prompt
	state->saveprompt = true;
	//Default is true, if enabled, used regular expressions in the search box
	state->useregex = true;
	//Default is true, if enabled, blink the cursor slowly
	state->blinkcursor = true;
	//Default is true, if enabled, write files under a different filename, then remove the existing and rename the new file.
	state->backupfiles = true;
	//Default is true, if enabled, parse ceditrc from /etc/cedit/ceditrc. Otherwise use /home/.ceditrc
	//Does nothin on TIOS
	state->bos_use_system_config = true;
	//Default is false. If enabled, boost BOS maximum buffer size to 128Kb
	//Does nothing on TIOS
	state->bos_use_extra_buffer = false;
	char buf1[10] = "Untitled";
	char buf2[10] = "DrMono";
	state->multi_lines = 5;
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
	state->focus_color = 142;
#ifdef BOS_BUILD
	if (!state->fontname) state->fontname = "/etc/fontlibc/DrMono";
#else
	strncpy(state->fontname, fontname, 10);
#endif
	state->saved = true;

	state->clipboard_size = 0;
	state->corner_radius = 10;

	state->font = 0;
	state->fonttype = 3;
    state->hide_special_files=1;
#ifndef BOS_BUILD
    //os_MemChk(&state->text);
    state->text=(char*)gfx_vram;
    state->text+=76800;
	//state->text=malloc_noheap(MAX_BUFFER_SIZE);
	//state->text = malloc(MAX_BUFFER_SIZE);
	//Temporary workaround to avoid buffer being yeeted by fileIO.
#else
	//BOS toolchain is okay with more than 64Kb, so just use static buffer
	state->text = BOS_SAFERAM;
#endif
#ifdef BOS_BUILD
	if ((font = (fontlib_font_pack_t *)fs_GetFilePtr("/etc/fontlibc/DrMono")) != -1)
	{
		if (font->fontCount >= state->fonttype)
		{
			state->font = ((void *)font) + font->font_list[state->fonttype];
		}
	}
#else
	state->font = fontlib_GetFontByIndex("DrMono", state->fonttype);
#endif
	if (!state->font)
	{
		os_ClrHome();
		os_PutStrFull("E1: Font pack not found.");
		return 1;
	}
	if (!fontlib_SetFont(state->font, 0))
	{
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
int main(int argc, char *argv[]) {
	static struct estate editor_state;

	if (initialize(&editor_state)) {
		gui_PrintLine_wrapper("E0: gfx-err");
		ngetchx();
		return 1;
	}
	editor_state.filename = sys_Malloc(256);
	//Argument parsing
	if (argc > 1) {
		if (argc > 2) {
			editor_state.fontname = argv[2];
		} else {
			editor_state.fontname = 0;
		}
		memcpy(editor_state.filename, argv[1], 256);
		editor_state.named = true;
	}
	gfx_Begin();
	parseRC(&editor_state);
	load_text(&editor_state);
	//draw_editor(&editor_state);
	editor_mainloop(&editor_state);
	gfx_End();
	return 0;
}
#else
int main(int argc, char *argv[])
{
	static struct estate editor_state;
    //editor_state.text = (char*)malloc_noheap_safe(65536,"CEDITBUF");
	if (initialize(&editor_state))
	{
		os_ClrHome();
		os_PutStrFull("E0: gfx-err");
		ngetchx();
		return 1;
	}
	//Argument parsing
	if (argc == 2)
	{
		strncpy(editor_state.filename, argv[1], 8);
		editor_state.named = true;
	}
	else if (argc > 2)
	{
		os_ClrHome();
		os_PutStrFull("Usage: CEdit [FILE]");
		while (!os_GetCSC())
			continue;
		return 1;
	}
	else
	{
		//Put a little help blurb
	}
	gfx_Begin();
	parseRC(&editor_state);
	load_text(&editor_state);
    draw_editor_full(&editor_state);
	editor_mainloop(&editor_state);
	gfx_End();
	return 0;
}
#endif
