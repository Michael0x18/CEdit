#include "editor.h"
#include <limits.h>

const int8_t title_offset = 10;

void redraw_editor(struct estate *state)
{
	// x4_FillScreen(EDIT_BG_COLOR);
	//   x4_FillRectangle(0, 0, 320, 16, STAT_BG_COLOR);
	/////////////////////////////////DRAW STATUSBAR UPDATE//////////////////////////////////////
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
	int draw_count = 0; // Count of the number of characters drawn. Used to update the screen parameters.
	if (!state->screen_start_offset)
	{
		x4_PutChar(state->font_buffer_select, 1, 16, ':');
	}
	// x4_PutChar(state->font_buffer, 9, 16, state->text[state->cursor_left - 1]);

	for (uint24_t i = state->screen_start_offset; i < state->cursor_left; i++)
	{
		x4_PutChar(state->font_buffer, 9 + 1 + c * 9, r * 16 + 16, state->text[i]);
		draw_count++;
		if (state->text[i] == '\n')
		{
			while (c < state->scr_width)
			{
				x4_PutChar(state->font_buffer, 9 + 1 + c * 9, r * 16 + 16, ' ');
				c++;
			}
			r++;
			c = 0;
			x4_PutChar(state->font_buffer_select, 1, r * 16 + 16, ':');
		}
		else
		{
			c++;
		}
		if (c >= state->scr_width)
		{
			c = 0;
			r++;
			x4_PutChar(state->font_buffer_select, 1, r * 16 + 16, '+');
		}
		if (r >= state->scr_height)
		{
			break;
		}
	}
	state->cursor_x = c;
	state->cursor_y = r;
	for (uint24_t i = state->cursor_right + 1; i < state->max_file_size; i++)
	{
		x4_PutChar(state->font_buffer, 9 + 1 + c * 9, r * 16 + 16, state->text[i]);
		draw_count++;
		if (state->text[i] == '\n')
		{
			while (c < state->scr_width)
			{
				// Clear rest of the line
				x4_PutChar(state->font_buffer, 9 + 1 + c * 9, r * 16 + 16, ' ');
				c++;
			}
			r++;
			c = 0;
			x4_PutChar(state->font_buffer_select, 1, r * 16 + 16, ':');
		}
		else
		{
			c++;
		}
		if (c >= state->scr_width)
		{
			c = 0;
			r++;
			x4_PutChar(state->font_buffer_select, 1, r * 16 + 16, '+');
		}
		if (r >= state->scr_height)
		{
			break;
		}
	}
	while (r < state->scr_height)
	{
		// Clear rest of the line
		x4_PutChar(state->font_buffer, 9 + 1 + c * 9, r * 16 + 16, ' ');
		c++;
		if (c >= state->scr_width)
		{
			c = 0;
			r++;
			x4_PutChar(state->font_buffer, 1, r * 16 + 16, ' '); // Remove line indicators, if present
		}
	}

	x4_Line_EFLA(state->cursor_x * 9 + 1 + 9, state->cursor_y * 16 + 16, state->cursor_x * 9 + 1 + 9, state->cursor_y * 16 + 31, TEXT_FG_COLOR);
	// x4_FillRectangle(0, 224, 320, 16, STAT_BG_COLOR);
}

void draw_shell(struct estate *state)
{
	x4_FillScreen(EDIT_BG_COLOR);
	x4_FillRectangle(0, 0, 320, 16, STAT_BG_COLOR);
	// x4_PutStr(state->font_buffer_statusbar, 230, 0, "CEdit V2.0");
	x4_PutStr(state->font_buffer_statusbar, title_offset, 0, state->filename);
}

/**
 * Handles a backspace operation, as opposed to delete, which deletes to the right
 */
void backspace(struct estate *state)
{
	// First check: if you can still move left
	if (state->cursor_left)
	{
		// Move left
		state->cursor_left--;
		if (state->cursor_x)
		{									 // If we can still move on the line
			state->cursor_x--;				 // Scoot this over
			state->cursor_line_sub_offset--; // And this
		}
		else
		{
			state->cursor_line_actual--; // Gotta reduce this val
			// Oh no, we just scooted over a line wrap or a newline
			state->cursor_y--; // Move up.
			if (state->text[state->cursor_left] == '\n')
			{							  // We just deleted a newline
				state->num_lines--;		  // Again, we deleted a newline
				state->cursor_line_raw--; // And now there's one less before the cursor
				uint24_t i = 0;
				for (; i < state->cursor_left; i++)
				{
					uint24_t index = state->cursor_left - i - 1;
					if (state->text[index] == '\n')
						break; // Cursed, but we found our newline
				}
				state->cursor_line_sub_offset = i;
				state->cursor_x = i % state->scr_width; // TODO check this
			}
			else
			{											// Oh well. We crossed a boundary, but it wasn't a newline.
				state->cursor_line_sub_offset--;		// Looks like this gets changed
				state->cursor_x = state->scr_width - 1; // Scoot to end
			}
		}
	}
}

void delete (struct estate *state)
{
	if (state->cursor_right < state->max_file_size - 1)
		state->cursor_right++;
}

bool editor_handle_keypress(struct estate *state, unsigned char k)
{
	if (k == KEY_ESCAPE)
	{
		return 1;
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
	return 0;
}

void editor_mainloop(struct estate *state)
{
	draw_shell(state);
	cedit_swapdraw(state);
	draw_shell(state);
	unsigned char k;
	while (1)
	{

		// Each large cycle, redraw the editor in full
		redraw_editor(state);
		// Swap draw to display the drawn editor
		cedit_swapdraw(state);
		// Reset the keypress
		k = 0;

		// Wait for keypress
		while (!k)
		{
			k = ngetchx(state, true);
			// dbg_printf("waiting\n");
			delay(5);
		}
		// Handle it rq
		if (editor_handle_keypress(state, k))
			goto end;
		// After initial keypress, enter hyper-responsive burst mode
		int timeout_max = state->timeout_max;
		int timeout_first = state->timeout_first;
		// Initialize the timeout
		int timeout = timeout_first;
		while ((timeout > 0))
		{
			// Poll for keypress
			if ((k = ngetchx(state, false)))
			{
				if (editor_handle_keypress(state, k))
					goto end;
				timeout = timeout_max;
			}
			else
			{
				timeout--;
				delay(1);
			}
		}
		// dbg_printf("got keypress\n");
		check_scroll_and_execute(state);
		dbg_printf("cursor_x: %d cursor_y: %d num_lines: %d cursor_line_raw: %d actual: %d sub: %d \n",
				   state->cursor_x, state->cursor_y, state->num_lines, state->cursor_line_raw,
				   state->cursor_line_actual, state->cursor_line_sub_offset);
	}
end:;
	// TODO cleanup
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
		if (state->cursor_x >= state->scr_width)
		{
			state->cursor_x = 0;
			state->cursor_y++;
		}
		state->cursor_line_sub_offset++;
		if (state->cursor_line_sub_offset % state->scr_width == 0)
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
			{											// If this is a wrapped line
				state->cursor_x = state->scr_width - 1; // Move the cursor to the end of the previous line
				state->cursor_line_sub_offset--;		// Reduce the offset
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
					state->cursor_x = i % state->scr_width; // TODO check this. Checked
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
		else if (state->cursor_line_sub_offset % state->scr_width == 0)
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