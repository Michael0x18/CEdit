#include "editor.h"

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
		textbuffer_insert(state->text, state->cursor, k);
		state->cursor++;
		dbg_printf("Inserting char: %c\n", k);
	}
	return 0;
}

bool is_control(unsigned char k)
{
	return k < 9 || k >= 127 || k == KEY_ESCAPE;
}

bool editor_handle_keypress_fast(struct estate *state, unsigned char k)
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
		textbuffer_buffered_insert(state->text, k);
	}
	return 0;
}

void handle_control(struct estate *state, unsigned char k)
{
	// TODO
}

void editor_mainloop(struct estate *state)
{
	// Keypress variable, used in reading
	unsigned char k = 0;

	draw_shell(state);
	cedit_swapdraw();
	draw_shell(state);

	while (true)
	{
		render_to_cache(state);
		// TODO scroll
		redraw_editor(state);
		cedit_swapdraw();
		// Reset the keypress
		k = 0;

		// Wait for keypress
		while (!k)
		{
			delay(2);
			k = ngetchx(state, false);
			// dbg_printf("waiting\n");
		}
		if (editor_handle_keypress(state, k))
		{
			goto end;
		}
	}
end:;
}