#include "editor.h"
#include <limits.h>

const int8_t title_offset = 1;

void redraw_editor(struct estate *state)
{
	// x4_FillScreen(EDIT_BG_COLOR);
	//   x4_FillRectangle(0, 0, 320, 16, STAT_BG_COLOR);
	if (!state->saved || !state->named)
	{
		x4_PutChar(state->font_buffer_statusbar, title_offset + 9 * strlen(state->filename), 0, '*');
	}
	else
	{
		x4_PutChar(state->font_buffer_statusbar, title_offset + 9 * strlen(state->filename), 0, ' ');
	}

	uint8_t r = 0;
	uint8_t c = 0;

	// x4_PutChar(state->font_buffer, 9, 16, state->text[state->cursor_left - 1]);

	for (uint24_t i = state->screen_start_offset; i < state->cursor_left; i++)
	{
		x4_PutChar(state->font_buffer, 1 + c * 9, r * 16 + 16, state->text[i]);
		if (state->text[i] == '\n')
		{
			while (c < 35)
			{
				x4_PutChar(state->font_buffer, 1 + c * 9, r * 16 + 16, '#');
				c++;
			}
			r++;
			c = 0;
		}
		else
		{
			c++;
		}
		if (c >= 35)
		{
			c = 0;
			r++;
		}
		if (r >= 13)
		{
			break;
		}
	}
	// state->cursor_x = c;
	// state->cursor_y = r;
	for (uint24_t i = state->cursor_right + 1; i < state->max_file_size; i++)
	{
		x4_PutChar(state->font_buffer, 1 + c * 9, r * 16 + 16, state->text[i]);
		if (state->text[i] == '\n')
		{
			while (c < 35)
			{
				x4_PutChar(state->font_buffer, 1 + c * 9, r * 16 + 16, '#');
				c++;
			}
			r++;
			c = 0;
		}
		else
		{
			c++;
		}
		if (c >= 35)
		{
			c = 0;
			r++;
		}
		if (r >= 13)
		{
			break;
		}
	}
	while (r < 13)
	{
		x4_PutChar(state->font_buffer, 1 + c * 9, r * 16 + 16, '~');
		c++;
		if (c >= 35)
		{
			c = 0;
			r++;
		}
	}

	x4_Line_EFLA(state->cursor_x * 9 + title_offset, state->cursor_y * 16 + 16, state->cursor_x * 9 + title_offset, state->cursor_y * 16 + 31, TEXT_FG_COLOR);
	// x4_FillRectangle(0, 224, 320, 16, STAT_BG_COLOR);
}

void draw_shell(struct estate *state)
{
	x4_FillScreen(EDIT_BG_COLOR);
	x4_FillRectangle(0, 0, 320, 16, STAT_BG_COLOR);
	x4_PutStr(state->font_buffer_statusbar, 230, 0, "CEdit V2.0");
	x4_PutStr(state->font_buffer_statusbar, title_offset, 0, state->filename);
}

void backspace(struct estate *state)
{
	if (state->cursor_left)
	{
		state->cursor_left--;
		state->cursor_x--;
		state->cursor_line_sub_offset--; // TODO fix this
										 // TODO do the subtraction
	}
}

void delete (struct estate *state)
{
	if (state->cursor_right < state->max_file_size - 1)
		state->cursor_right++;
}

void editor_mainloop(struct estate *state)
{
	draw_shell(state);
	cedit_swapdraw(state);
	draw_shell(state);
	while (1)
	{
		redraw_editor(state);
		cedit_swapdraw(state);
		unsigned char k = 0;
		while (!k)
		{
			k = ngetchx(state);
			// dbg_printf("waiting\n");
			// delay(5);
		}
		// dbg_printf("got keypress\n");
		if (k == KEY_ESCAPE)
		{
			break;
		}
		if (is_control(k))
		{
			handle_control(state, k);
		}
		else
		{
			insert_char(state, k);
			// dbg_printf("Inserting char: %d\n", k);
		}
		dbg_printf("cursor_x: %d cursor_y: %d num_lines: %d cursor_line_raw: %d actual: %d sub: %d \n",
				   state->cursor_x, state->cursor_y, state->num_lines, state->cursor_line_raw,
				   state->cursor_line_actual, state->cursor_line_sub_offset);
		delay(10);
	}
}

bool is_control(unsigned char k)
{
	return k < 9 || k >= 127 || k == KEY_ESCAPE;
}

void insert_char(struct estate *state, char c)
{
	state->text[state->cursor_left++] = c;
	if (c == '\n')
	{
		state->cursor_x = 0;
		state->cursor_y++;
		state->num_lines++;
		state->cursor_line_raw++;
		state->cursor_line_actual++;
		state->cursor_line_sub_offset = 0;
	}
	else
	{
		state->cursor_x++;
		if (state->cursor_x >= 35)
		{
			state->cursor_x = 0;
			state->cursor_y++;
		}
		state->cursor_line_sub_offset++;
		if (state->cursor_line_sub_offset % 35 == 0)
		{
			state->cursor_line_actual++;
		}
	}
}

void move_left(struct estate *state)
{
	if (state->cursor_left)
	{
		state->text[state->cursor_right] = state->text[state->cursor_left - 1];
		state->cursor_right--;
		state->cursor_left--;
		if (state->cursor_x)
		{									 // If we can still move back on this editor row
			state->cursor_x--;				 // Do so
			state->cursor_line_sub_offset--; // Gotta change this too
		}
		else
		{								 // We hit the end
			state->cursor_y--;			 // First, go back a line (with the cursor)
			state->cursor_line_actual--; // It's a real line anyway, so do this
			if (state->cursor_line_sub_offset)
			{									 // If this is a wrapped line
				state->cursor_x = 34;			 // Move the cursor to the end of the previous line
				state->cursor_line_sub_offset--; // Reduce the offset
												 // We went one (real) line back
			}
			else
			{
				if (state->text[state->cursor_right + 1] == '\n')
				{							  // we hit a newline. Sanity check. This shouldn't be needed
					state->cursor_line_raw--; // First, we passed a newline
											  // We happen to be at the end of the previous line. First, count the number of characters in it.
					uint24_t i = 0;
					for (; i < state->cursor_left; i++)
					{
						uint24_t index = state->cursor_left - i - 1;
						if (state->text[index] == '\n')
							break; // Cursed, but we found our newline
					}
					state->cursor_line_sub_offset = i;
					state->cursor_x = i % 35; // TODO check this
				}
				else
				{
					// What the fuck?
					exit(1);
				}
			}
		}
	}
}

void move_right(struct estate *state)
{
	if (state->cursor_right < state->max_file_size - 1)
	{
		state->text[state->cursor_left] = state->text[state->cursor_right + 1];
		state->cursor_right++;
		state->cursor_left++;
		state->cursor_x++;
		state->cursor_line_sub_offset++; // This is fine, if we actually hit a newline we'll undo it later
		if (state->text[state->cursor_left - 1] == '\n')
		{									   // We're moving across a newline
			state->cursor_y++;				   // First move the cursor down one line
			state->cursor_x = 0;			   // Then move it to the left side
			state->cursor_line_raw++;		   // We passed another newline
			state->cursor_line_actual++;	   // This counts toward the actual offset
			state->cursor_line_sub_offset = 0; // Reset this; we start over from this newline
		}
		else if (state->cursor_line_sub_offset % 35 == 0)
		{								 // We're moving across a subline boundary
			state->cursor_y++;			 // First move down
			state->cursor_x = 0;		 // Then back to start
			state->cursor_line_actual++; // Only update the actual count because of the wrap
		}
	}
}

void handle_control(struct estate *state, unsigned char k)
{
	switch (k)
	{
	case KEY_BS:
		backspace(state);
		break;
	case KEY_DEL:
		delete (state);
		break;
	case KEY_LEFT:
		move_left(state);
		break;
	case KEY_RIGHT:
		move_right(state);
		break;
	}
}