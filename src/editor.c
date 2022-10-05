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
		textbuffer_insert(state->text, k);
		// dbg_printf("Inserting char: %d\n", k);
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
		redraw_editor(state);
		cedit_swapdraw();
		// Reset the keypress
		k = 0;

		// Wait for keypress
		while (!k)
		{
			k = ngetchx(state, true);
			// dbg_printf("waiting\n");
			delay(5);
		}
		if (editor_handle_keypress(state, k))
		{
			goto end;
		}
	}
end:;
}