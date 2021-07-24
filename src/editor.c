#ifndef editor_c
#define editor_c

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>
#include <fileioc.h>
#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <graphx.h>
#include <keypadc.h>
#include <fontlibc.h>

#include "tigcclib.h"
#include "editor.h"
#include "gfx.h"
#include "dialogs.h"

/*
 * Cursor x position
 */
static int c_x = 0;

/*
 * Cursor y position
 */
static int c_y = 0;

/*
 * True if the open document was saved
 */
static bool saved = false;

bool is_control(short k) {
	return (k <= 0) || (k >= 256);
}

void insert_newline() {
	//Line split
	int tmp = lines[lc1] - lc_offset;
	lines[lc1] = lc_offset;
	//Create new entry in line buffer.
	lc1++;
	lines[lc1] = tmp;
	lc_offset = 0;
}

void insert_char(char c) {
	saved=false;
	text[c1] = c;
	c1++;
	if (text[c1 - 1] == '\n') {
		insert_newline();
	} else {
		lines[lc1]++;
		lc_offset++;
	}
}

void line_down(void) {
	if (lc2 < max_buffer_size) {
		lc2++;
		lc1++;
		lines[lc1] = lines[lc2];
		lc_offset = 0;
	}
}

void line_up(void) {
	if (lc1 > 0) {
		lines[lc2] = lines[lc1];
		lc1--;
		lc2--;
		lc_offset = lines[lc1];
	}
}

void cursor_left(void) {
	if (c1 > 0) {
		if (lc_offset == 0) {
			line_up();
		} else {
			//Moving on same line
			lc_offset--;
		}
		c1--;
		text[c2] = text[c1];
		c2--;
	}
}

void cursor_right(void) {
	if (c2 < max_buffer_size - 1) {
		if (/*text[c2+1]=='\n' || */lc_offset == lines[lc1]) {
			line_down();
			//lc_offset=0;
		} else {
			lc_offset++;
		}
		c2++;
		text[c1] = text[c2];
		c1++;
	}
}

void cursor_up(void) {
	//if the current line is long enough
	if (lc_offset >= num_cols) {
		for (int i = 0; i < num_cols; i++) {
			cursor_left();
		}
	} else {
		//cache the current offset -- use this later
		int old = lc_offset;
		while (lc_offset > 0) {
			cursor_left();
		}
		if (!c1)
			return;
		cursor_left();
		//on last char of next line
		//now need to move until old

		//return if the end is what you want
		if (lc_offset % num_cols < old)
			return;
		int c = lc_offset - lc_offset % num_cols;
		c += old;		//Offset to move to from start of line
		int to_move = lc_offset - c;
		for (int i = 0; i < to_move; i++) {
			cursor_left();
		}
	}
}

void cursor_down(void) {
	if (lines[lc1] - lc_offset > num_cols) {
		for (int i = 0; i < num_cols; i++) {
			cursor_right();
		}
	} else {
		int old = lc_offset;
		int oldb = lines[lc1];
		for (int i = 0; i < oldb - old; i++) {
			cursor_right();
		}
		cursor_right();
		if (lines[lc1] < old % num_cols) {
			for (int i = 0; i < lines[lc1]; i++) {
				cursor_right();
			}
		} else {
			for (int i = 0; i < old % num_cols; i++) {
				cursor_right();
			}
		}
	}
}

void init_editor(void) {
	lc1 = 0;
	lc2 = max_buffer_size - 1;
	lc_offset = 0;
	ls_offset = 0;
	c1 = 0;
	c2 = max_buffer_size - 1;
	scr_offset = 0;
	scr_line = 0;
	scr_line_offset = 0;
	load_text();
}

void handle_key(short k) {
	if (!is_control(k)) {
		insert_char(k);
	} else {
		switch (k) {
		case KEY_LEFT:		//left
			cursor_left();
			break;
		case KEY_RIGHT:		//right
			cursor_right();
			break;
		case KEY_DOWN:		//down
			cursor_down();
			break;
		case KEY_UP:		//up
			cursor_up();
			break;
		case KEY_BS:		//backspace
			bs();
			break;
		case KEY_DEL:		//delete
			del();
			break;
		case KEY_SAVE_AS:
			draw_editor();
			gfx_SwapDraw();
			show_save_dialog();
			write_file();
			break;
		case KEY_SAVE:		//save
			if (!named) {
				draw_editor();
				gfx_SwapDraw();
				show_save_dialog();
			}
			write_file();
			break;
		case KEY_WLEFT:		//2nd-left
			cursor_to_left_word();
			break;
		case KEY_WRIGHT:		//2nd-right
			cursor_to_right_word();
			break;
		case KEY_WUP:		//2nd-up
			cursor_multi_up();
			break;
		case KEY_WDOWN:		//2nd-down
			cursor_multi_down();
			break;
		case KEY_LLEFT:		//meta-left
			cursor_to_l_start();
			break;
		case KEY_LRIGHT:		//meta-right
			cursor_to_l_end();
			break;
		case KEY_LUP:		//meta-up
			cursor_to_start();
			break;
		case KEY_LDOWN:		//meta-down
			cursor_to_end();
			break;
		case KEY_BREAK:
			draw_editor();
			gfx_SwapDraw();
			show_menu_dialog();
			break;
		}
	}
}

int draw_editor(void) {
	gfx_FillScreen(background_color);
	//Initialize temporary variables
	int24_t i = scr_offset;
	int8_t row = 0;
	int8_t col = 0;
	int24_t cp = 0;
	bool drawn = false;
	//Start drawing
	fontlib_SetCursorPosition(0, ls);
	fontlib_DrawGlyph(scr_line_offset ? '+' : ':');
	//Iterate buffer
	while (i < max_buffer_size && (cp < max_buffer_size - c2 + c1) && row < numl+1) {
		if (i == c1) {
			if (col >= num_cols) {
				gfx_VertLine_NoClip(319, ls * row + fw + 1, ls);
				c_x=319,c_y=ls * row + fw + 1;

			} else {
				gfx_VertLine_NoClip((fw + fw * col), ls * row + ls + 1, ls);
				c_x = (fw+fw*col), c_y = ls * row + ls + 1;

			}

			i = c2 + 1;
			drawn = 1;
			if (i >= max_buffer_size)
				break;
		}

		if (text[i] == '\n') {
			row++;
			col = 0;
			i++;
			cp++;
			fontlib_SetCursorPosition(0, ls * row + ls);
			fontlib_DrawGlyph(':');
			continue;
		}

		fontlib_DrawGlyph(text[i]);

		i++;
		cp++;
		col++;
		if (col >= num_cols) {
			col = 0;
			row++;
			fontlib_SetCursorPosition(fw, ls * row + ls);
		}
	}

	gfx_SetColor(statusbar_color);
	gfx_FillRectangle_NoClip(0, 0, 320, 12);
	gfx_FillRectangle_NoClip(0, 228, 320, 12);
	fontlib_SetCursorPosition(0, 0);
	if(!saved)
		fontlib_DrawGlyph('*');
	fontlib_DrawString(named ? filename : "Untitled Document");
	if(!saved)
		fontlib_DrawGlyph('*');
	if(!drawn) {
		if(c1<scr_offset) {
			scroll_up();
		}else{
			scroll_down();
		}
		draw_editor();
	}
	return 0;
}

void editor_mainloop(void) {
	short k = 0;
	while (true) {
		draw_editor();
		gfx_SwapDraw();
		k = ngetchx_xy(c_x,c_y);
		if (k == KEY_CLEAR)
			break;
		handle_key(k);
	}
}

void bs(void) {
	if (c1) {
		if (lc_offset == 0) {
			lc1--;		//Delete line
			lc_offset = lines[lc1];
			lines[lc1] += lines[lc1 + 1];
		} else {
			lc_offset--;		//else go back
			lines[lc1]--;
		}
		c1--;
	}
}

void del(void) {
	if (c2 < max_buffer_size - 1) {
		if (lc_offset == lines[lc1]) {
			lc2++;
			lines[lc1] += lines[lc2 + 1];
		} else {
			lines[lc1]--;
		}
		c2++;
	}
}

void scroll_up(void) {
//WTH I don't know if this is gonna work, but I'm hella tired rn.
	scr_offset = c1 - lc_offset % num_cols;
	scr_line = lc1;
	scr_line_offset = lc_offset - lc_offset % num_cols;

}

void scroll_down(void) {
//18 lines total, currently 38 chars
	int pre_offset = lc_offset;
	for (int i = 0; i < 17; i++) {
		cursor_up();
	}
	scroll_up();
	for (int i = 0; i < 17; i++) {
		cursor_down();
	}
	while (lc_offset < pre_offset) {
		cursor_right();
	}
	while (lc_offset > pre_offset) {
		cursor_left();
	}
}

void cursor_to_start(void) {
	while (c1) {
		cursor_left();
	}
}

void cursor_to_end(void) {
	while (c2 < max_buffer_size - 1) {
		cursor_right();
	}
}

void cursor_to_left_word(void) {
}

void cursor_to_right_word(void) {

}

void cursor_multi_up(void) {
	for (int i = 0; i < multi_lines; i++) {
		cursor_up();
	}
}

void cursor_multi_down(void) {
	for (int i = 0; i < multi_lines; i++) {
		cursor_down();
	}
}

void cursor_to_l_start(void) {
	while (lc_offset) {
		cursor_left();
	}
}

void cursor_to_l_end(void) {
	while (lc_offset < lines[lc1]) {
		cursor_right();
	}
}

void load_text(void) {
	ti_var_t var;
	ti_CloseAll();
	var = ti_Open(filename, "r");
	if (var == 0) {
		return;		//no error out
	}
	char c;
	while ((c = ti_GetC(var)) != EOF) {
		insert_char(c);
	}
}

void write_file(void) {
	ti_var_t var;
	ti_CloseAll();
	var = ti_Open(filename, "w");
	int i = 0;
	while (i < max_buffer_size) {
		if (i == c1)
			i = c2 + 1;
		if (i >= max_buffer_size)
			break;
		ti_PutC(text[i], var);
		i++;
	}
	saved=true;
}

#endif
