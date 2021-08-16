/*
 * editor.c
 *
 *  Created on: Jul 25, 2021
 *      Author: michael
 */

#include "dialogs.h"
#include "editor.h"
#include "tigcclib.h"

bool is_control(short k) {
	return (k <= 0) || (k >= 256);
}

void insert_newline(struct estate *state) {
	//Line split
	int tmp = state->lines[state->lc1] - state->lc_offset;
	state->lines[state->lc1] = state->lc_offset;
	//Create new entry in line buffer.
	state->lc1++;
	state->lines[state->lc1] = tmp;
	state->lc_offset = 0;
}

void insert_char(struct estate *state, char c) {
	if (state->selection_active) {
		bs(state);
	}
	state->saved = false;
	state->text[state->c1] = c;
	state->c1++;
	if (state->text[state->c1 - 1] == '\n') {
		insert_newline(state);
	} else {
		state->lines[state->lc1]++;
		state->lc_offset++;
	}
}

void line_down(struct estate *state) {
	if (state->lc2 < MAX_BUFFER_SIZE) {
		state->lc2++;
		state->lc1++;
		state->lines[state->lc1] = state->lines[state->lc2];
		state->lc_offset = 0;
	}
}

void line_up(struct estate *state) {
	if (state->lc1 > 0) {
		state->lines[state->lc2] = state->lines[state->lc1];
		state->lc1--;
		state->lc2--;
		state->lc_offset = state->lines[state->lc1];
	}
}

void cursor_left(struct estate *state) {
	if (state->selection_active) {
		state->selection_active = false;
		if (state->selection_anchor > state->c2 + 1)
			return;
		while (state->selection_anchor < state->c1 - 2)
			cursor_left(state);
	}
	if (state->c1 > 0) {
		if (state->lc_offset == 0) {
			line_up(state);
		} else {
			//Moving on same line
			state->lc_offset--;
		}
		state->c1--;
		state->text[state->c2] = state->text[state->c1];
		state->c2--;
	}
}

void cursor_left_select(struct estate *state) {
	if (!state->selection_active) {
		state->selection_active = true;
		state->selection_anchor = state->c2;
	}
	if (state->c1 == state->selection_anchor) {
		state->selection_anchor = state->c2;
	}
	if (state->c1 > 0) {
		if (state->lc_offset == 0) {
			line_up(state);
		} else {
			//Moving on same line
			state->lc_offset--;
		}
		state->c1--;
		state->text[state->c2] = state->text[state->c1];
		state->c2--;
	}
}

void cursor_right(struct estate *state) {
	if (state->selection_active) {
		state->selection_active = false;
		if (state->selection_anchor < state->c1 - 1)
			return;
		while (state->selection_anchor > state->c2 + 2)
			cursor_right(state);
	}
	if (state->c2 < MAX_BUFFER_SIZE - 1) {
		if (state->lc_offset == state->lines[state->lc1]) {
			line_down(state);
		} else {
			state->lc_offset++;
		}
		state->c2++;
		state->text[state->c1] = state->text[state->c2];
		state->c1++;
	}
}

void cursor_right_select(struct estate *state) {
	if (!state->selection_active) {
		state->selection_active = true;
		state->selection_anchor = state->c1;
	}
	if (state->c2 == state->selection_anchor) {
		state->selection_anchor = state->c1;
	}
	if (state->c2 < MAX_BUFFER_SIZE - 1) {
		if (state->lc_offset == state->lines[state->lc1]) {
			line_down(state);
		} else {
			state->lc_offset++;
		}
		state->c2++;
		state->text[state->c1] = state->text[state->c2];
		state->c1++;
	}
}

void cursor_up(struct estate *state) {
	//if the current line is long enough
	if (state->selection_active) {
		cursor_left(state);
	}
	if (state->lc_offset >= NUM_COLS) {
		for (int i = 0; i < NUM_COLS; i++) {
			cursor_left(state);
		}
	} else {
		//cache the current offset -- use this later
		int old = state->lc_offset;
		while (state->lc_offset > 0) {
			cursor_left(state);
		}
		if (!state->c1)
			return;
		cursor_left(state);
		//on last char of next line
		//now need to move until old

		//return if the end is what you want
		if (state->lc_offset % NUM_COLS < old)
			return;
		int c = state->lc_offset - state->lc_offset % NUM_COLS;
		c += old;		//Offset to move to from start of line
		int to_move = state->lc_offset - c;
		for (int i = 0; i < to_move; i++) {
			cursor_left(state);
		}
	}
}

void cursor_up_select(struct estate *state) {
	//if the current line is long enough
	if (state->lc_offset >= NUM_COLS) {
		for (int i = 0; i < NUM_COLS; i++) {
			cursor_left_select(state);
		}
	} else {
		//cache the current offset -- use this later
		int old = state->lc_offset;
		while (state->lc_offset > 0) {
			cursor_left_select(state);
		}
		if (!state->c1)
			return;
		cursor_left_select(state);
		//on last char of next line
		//now need to move until old

		//return if the end is what you want
		if (state->lc_offset % NUM_COLS < old)
			return;
		int c = state->lc_offset - state->lc_offset % NUM_COLS;
		c += old;		//Offset to move to from start of line
		int to_move = state->lc_offset - c;
		for (int i = 0; i < to_move; i++) {
			cursor_left_select(state);
		}
	}
}

void cursor_down(struct estate *state) {
	if (state->selection_active) {
		state->selection_active=0;
		cursor_down(state);
	}
	if (state->lines[state->lc1] - state->lc_offset > NUM_COLS) {
		for (int i = 0; i < NUM_COLS; i++) {
			cursor_right(state);
		}
	} else {
		int old = state->lc_offset;
		int oldb = state->lines[state->lc1];
		for (int i = 0; i < oldb - old; i++) {
			cursor_right(state);
		}
		cursor_right(state);
		if (state->lines[state->lc1] < old % NUM_COLS) {
			for (int i = 0; i < state->lines[state->lc1]; i++) {
				cursor_right(state);
			}
		} else {
			for (int i = 0; i < old % NUM_COLS; i++) {
				cursor_right(state);
			}
		}
	}
}

void cursor_down_select(struct estate *state) {
	if (state->lines[state->lc1] - state->lc_offset > NUM_COLS) {
		for (int i = 0; i < NUM_COLS; i++) {
			cursor_right_select(state);
		}
	} else {
		int old = state->lc_offset;
		int oldb = state->lines[state->lc1];
		for (int i = 0; i < oldb - old; i++) {
			cursor_right_select(state);
		}
		cursor_right_select(state);
		if (state->lines[state->lc1] < old % NUM_COLS) {
			for (int i = 0; i < state->lines[state->lc1]; i++) {
				cursor_right_select(state);
			}
		} else {
			for (int i = 0; i < old % NUM_COLS; i++) {
				cursor_right_select(state);
			}
		}
	}
}

void handle_key(struct estate *state, short k) {
	if (!is_control(k)) {
		insert_char(state, k);
	} else {
		switch (k) {
		case KEY_SUP:
			cursor_up_select(state);
			break;
		case KEY_SDOWN:
			cursor_down_select(state);
			break;
		case KEY_SLEFT:
			cursor_left_select(state);
			break;
		case KEY_SRIGHT:
			cursor_right_select(state);
			break;
		case KEY_LEFT:		//left
			cursor_left(state);
			break;
		case KEY_RIGHT:		//right
			cursor_right(state);
			break;
		case KEY_DOWN:		//down
			cursor_down(state);
			break;
		case KEY_UP:		//up
			cursor_up(state);
			break;
		case KEY_BS:		//backspace
			bs(state);
			break;
		case KEY_DEL:		//delete
			del(state);
			break;
		case KEY_SAVE_AS:
			draw_editor(state);
			gfx_SwapDraw();
			if (!show_save_dialog(state))
				write_file(state);
			break;
		case KEY_SAVE:		//save
			if (!state->named) {
				draw_editor(state);
				gfx_SwapDraw();
				if (show_save_dialog(state))
					break;
			}
			write_file(state);
			break;
		case KEY_WSLEFT:
			cursor_to_left_word_select(state);
			break;
		case KEY_WSRIGHT:
			cursor_to_right_word_select(state);
			break;
		case KEY_WSDOWN:
			cursor_multi_down_select(state);
			break;
		case KEY_WSUP:
			cursor_multi_up_select(state);
			break;
		case KEY_WLEFT:		//2nd-left
			cursor_to_left_word(state);
			break;
		case KEY_WRIGHT:		//2nd-right
			cursor_to_right_word(state);
			break;
		case KEY_WUP:		//2nd-up
			cursor_multi_up(state);
			break;
		case KEY_WDOWN:		//2nd-down
			cursor_multi_down(state);
			break;
		case KEY_LSLEFT:
			cursor_to_l_start_select(state);
			break;
		case KEY_LSRIGHT:
			cursor_to_l_end_select(state);
			break;
		case KEY_LSUP:
			cursor_to_start_select(state);
			break;
		case KEY_LSDOWN:
			cursor_to_end_select(state);
			break;
		case KEY_LLEFT:		//meta-left
			cursor_to_l_start(state);
			break;
		case KEY_LRIGHT:		//meta-right
			cursor_to_l_end(state);
			break;
		case KEY_LUP:		//meta-up
			cursor_to_start(state);
			break;
		case KEY_LDOWN:		//meta-down
			cursor_to_end(state);
			break;
		case KEY_F1:
			cb_cut(state);
			break;
		case KEY_F2:
			cb_copy(state);
			break;
		case KEY_F3:
			cb_paste(state);
			break;
		case KEY_F5:
			draw_editor(state);
			gfx_SwapDraw();
			show_menu_dialog(state);
			break;
		}
	}
}

void cursor_to_start_select(struct estate *state) {
	while (state->c1) {
		cursor_left_select(state);
	}
}
void cursor_to_end_select(struct estate *state) {
	while (state->c2 < MAX_BUFFER_SIZE - 1) {
		cursor_right_select(state);
	}
}
void cursor_multi_up_select(struct estate *state) {
	for (int i = 0; i < state->multi_lines; i++) {
		cursor_up_select(state);
	}
}
void cursor_multi_down_select(struct estate *state) {
	for (int i = 0; i < state->multi_lines; i++) {
		cursor_down_select(state);
	}
}
void cursor_to_l_start_select(struct estate *state) {
	while (state->lc_offset) {
		cursor_left_select(state);
	}
}
void cursor_to_l_end_select(struct estate *state) {
	while (state->lc_offset < state->lines[state->lc1]) {
		cursor_right_select(state);
	}
}

void cursor_to_left_word_select(struct estate *state) {
	//while(state->eof)
}

void cursor_to_right_word_select(struct estate *state) {

}

int draw_editor(struct estate *state) {
	gfx_FillScreen(state->background_color);
	//Initialize temporary variables
	int24_t i = state->scr_offset;
	int8_t row = 0;
	int8_t col = 0;
	int24_t cp = 0;
	bool drawn = false;
	//Start drawing
	fontlib_SetCursorPosition(0, LINE_SPACING);
	fontlib_DrawGlyph(state->scr_line_offset ? '+' : ':');
	//Iterate buffer
	while (i < MAX_BUFFER_SIZE && (cp < MAX_BUFFER_SIZE - state->c2 + state->c1)
			&& row < NUM_LINES + 1) {
		fontlib_SetForegroundColor(state->text_color);
		fontlib_SetBackgroundColor(state->text_highlight_color);
		fontlib_SetTransparency(true);
		if (i == state->c1) {
			if (col >= NUM_COLS) {
				gfx_VertLine_NoClip(319, LINE_SPACING * row + FONT_WIDTH + 1,
				LINE_SPACING);
				state->cx = 319, state->cy = LINE_SPACING * row + FONT_WIDTH + 1;

			} else {
				gfx_VertLine_NoClip((FONT_WIDTH + FONT_WIDTH * col),
				LINE_SPACING * row + LINE_SPACING + 1, LINE_SPACING);
				state->cx = (FONT_WIDTH + FONT_WIDTH * col), state->cy =
				LINE_SPACING * row + LINE_SPACING + 1;

			}

			i = state->c2 + 1;
			drawn = 1;
			if (i >= MAX_BUFFER_SIZE)
				break;
		}

		if (state->text[i] == '\n') {
			row++;
			col = 0;
			i++;
			cp++;
			fontlib_SetCursorPosition(0, LINE_SPACING * row + LINE_SPACING);
			fontlib_DrawGlyph(':');
			continue;
		}
		if (state->selection_active
				&& ((state->selection_anchor <= i && i < state->c1)
						|| (state->selection_anchor >= i && i > state->c2))) {
			fontlib_SetForegroundColor(state->text_selection_color);
			fontlib_SetBackgroundColor(state->text_selection_highlight_color);
			fontlib_SetTransparency(false);
		} else {
			fontlib_SetForegroundColor(state->text_color);
			fontlib_SetBackgroundColor(state->text_highlight_color);
			fontlib_SetTransparency(true);
		}
		fontlib_DrawGlyph(state->text[i]);

		i++;
		cp++;
		col++;
		if (col >= NUM_COLS) {
			col = 0;
			row++;
			fontlib_SetCursorPosition(FONT_WIDTH,
			LINE_SPACING * row + LINE_SPACING);
		}
	}
	fontlib_SetForegroundColor(state->statusbar_text_color);
	fontlib_SetBackgroundColor(state->text_highlight_color);
	fontlib_SetTransparency(true);
	//Draw statusbars
	gfx_SetColor(state->statusbar_color);
	gfx_FillRectangle_NoClip(0, 0, 320, 12);		//Top
	gfx_FillRectangle_NoClip(1, 228, 62, 12);		//Floating segments
	gfx_FillRectangle_NoClip(65, 228, 62, 12);
	gfx_FillRectangle_NoClip(129, 228, 62, 12);
	gfx_FillRectangle_NoClip(193, 228, 62, 12);
	gfx_FillRectangle_NoClip(257, 228, 62, 12);
	//Draw text on segs
	fontlib_SetCursorPosition(20, 228);
	fontlib_DrawString("Cut");
	fontlib_SetCursorPosition(80, 228);
	fontlib_DrawString("Copy");
	fontlib_SetCursorPosition(140, 228);
	fontlib_DrawString("Paste");
	fontlib_SetCursorPosition(200, 228);
	fontlib_DrawString("Search");
	fontlib_SetCursorPosition(272, 228);
	fontlib_DrawString("Menu");
	//Draw drop shadows
	gfx_SetColor(state->dropshadow_color);
	gfx_VertLine_NoClip(63, 229, 11);
	gfx_VertLine_NoClip(127, 229, 11);
	gfx_VertLine_NoClip(191, 229, 11);
	gfx_VertLine_NoClip(255, 229, 11);
	gfx_VertLine_NoClip(319, 229, 11);
	//Top
	gfx_HorizLine_NoClip(0, 12, 320);

	//Draw top text
	fontlib_SetCursorPosition(0, 0);
	if (!state->saved)
		fontlib_DrawGlyph('*');
	fontlib_DrawString(state->named ? state->filename : "Untitled Document");
	if (!state->saved)
		fontlib_DrawGlyph('*');
	fontlib_SetForegroundColor(state->text_color);
	fontlib_SetBackgroundColor(state->text_highlight_color);
	fontlib_SetTransparency(true);
	if (!drawn) {
		if (state->c1 < state->scr_offset) {
			scroll_up(state);
		} else {
			scroll_down(state);
		}
		gfx_SwapDraw();
		draw_editor(state);
	}

	//fontlib_DrawInt(state->selection_anchor, 5);
	return 0;
}

void editor_mainloop(struct estate *state) {
	short k = 0;
	while (true) {
		draw_editor(state);
		gfx_SwapDraw();
		k = ngetchx_xy(state, state->cx, state->cy);
		if (k == KEY_CLEAR)
			break;
		handle_key(state, k);
	}
}

void bs(struct estate *state) {
	if (state->selection_active) {
		state->selection_active = false;
		while (state->selection_anchor < state->c1) {//if selection is to left
			bs(state);
		}
		while (state->selection_anchor > state->c2) {//if selection is to left
			del(state);
		}
	} else if (state->c1) {
		if (state->lc_offset == 0) {
			state->lc1--;		//Delete line
			state->lc_offset = state->lines[state->lc1];
			state->lines[state->lc1] += state->lines[state->lc1 + 1];
		} else {
			state->lc_offset--;		//else go back
			state->lines[state->lc1]--;
		}
		state->c1--;
	}
}

void del(struct estate *state) {
	if (state->selection_active) {
		state->selection_active = false;
		while (state->selection_anchor < state->c1) {//if selection is to left
			bs(state);
		}
		while (state->selection_anchor > state->c2) {//if selection is to left
			del(state);
		}
	} else if (state->c2 < MAX_BUFFER_SIZE - 1) {
		if (state->lc_offset == state->lines[state->lc1]) {
			state->lc2++;
			state->lines[state->lc1] += state->lines[state->lc2 + 1];
		} else {
			state->lines[state->lc1]--;
		}
		state->c2++;
	}
}

void scroll_up(struct estate *state) {
	state->scr_offset = state->c1 - state->lc_offset % NUM_COLS;
	state->scr_line = state->lc1;
	state->scr_line_offset = state->lc_offset - state->lc_offset % NUM_COLS;

}

void scroll_down(struct estate *state) {
//18 lines total, currently 38 chars
	if (!state->selection_active) {
		int pre_offset = state->lc_offset;
		for (int i = 0; i < 17; i++) {
			cursor_up(state);
		}
		scroll_up(state);
		for (int i = 0; i < 17; i++) {
			cursor_down(state);
		}
		while (state->lc_offset < pre_offset) {
			cursor_right(state);
		}
		while (state->lc_offset > pre_offset) {
			cursor_left(state);
		}
	} else {
		int pre_offset = state->lc_offset;
		for (int i = 0; i < 17; i++) {
			cursor_up_select(state);
		}
		scroll_up(state);
		for (int i = 0; i < 17; i++) {
			cursor_down_select(state);
		}
		while (state->lc_offset < pre_offset) {
			cursor_right_select(state);
		}
		while (state->lc_offset > pre_offset) {
			cursor_left_select(state);
		}
	}

}

void cursor_to_start(struct estate *state) {
	while (state->c1) {
		cursor_left(state);
	}
}

void cursor_to_end(struct estate *state) {
	while (state->c2 < MAX_BUFFER_SIZE - 1) {
		cursor_right(state);
	}
}

void cursor_to_left_word(struct estate *state) {
}

void cursor_to_right_word(struct estate *state) {

}

void cursor_multi_up(struct estate *state) {
	for (int i = 0; i < state->multi_lines; i++) {
		cursor_up(state);
	}
}

void cursor_multi_down(struct estate *state) {
	for (int i = 0; i < state->multi_lines; i++) {
		cursor_down(state);
	}
}

void cursor_to_l_start(struct estate *state) {
	while (state->lc_offset) {
		cursor_left(state);
	}
}

void cursor_to_l_end(struct estate *state) {
	while (state->lc_offset < state->lines[state->lc1]) {
		cursor_right(state);
	}
}

void load_text(struct estate *state) {
#ifdef BOS_BUILD
	void *fd = fs_OpenFile(state->filename);
	if (fd != -1){
		char *ptr = fs_GetFDPtr(fd);
		char *end = &ptr[fs_GetFDLen(fd)];
		while (ptr < end){
			insert_char(state, *ptr++);
		}
	}
#else
	ti_var_t var;
	ti_CloseAll();
	var = ti_Open(state->filename, "r");
	if (var == 0) {
		return;		//no error out
	}
	char c;
	while ((c = ti_GetC(var)) != EOF) {
		insert_char(state, c);
	}
#endif
}

void write_file(struct estate *state) {
	int fullsize = state->c1 + MAX_BUFFER_SIZE - (state->c2 + 1);
#ifdef BOS_BUILD
	void *fd = fs_OpenFile(state->filename);
	if (fd == -1) {
		fd = fs_CreateFile(state->filename, 0, fullsize);
	} else {
		fs_SetSize(fullsize, fd);
	}
	if (fullsize > 0) {
		fs_Write(&state->text, state->c1, 1, fd, 0);
		fs_Write(&state->text[state->c2 + 1], MAX_BUFFER_SIZE - (state->c2 + 1), 1, fd, state->c1);
	}
#else
	ti_var_t var;
	int i = 0;
	var = ti_Open(state->filename, "w");
 	ti_Resize(fullsize, var); //makes saving a lot faster due to only needing to resize the variable once
	while (i < MAX_BUFFER_SIZE) {
		if (i == state->c1)
			i = state->c2 + 1;
		if (i >= MAX_BUFFER_SIZE)
			break;
		ti_PutC(state->text[i], var);
		i++;
	}
	/*
	 if (state->eof > 0){
	 ti_Resize(state->eof, var);
	 ti_Write(&state->text, state->eof, 1, var);
	 }
	 */
	ti_Close(var);
#endif
	state->saved = true;
}

