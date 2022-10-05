#include "editor.h"

void editor_mainloop(struct estate *state)
{
	// Keypress variable, used in reading
	unsigned char k = 0;

	draw_shell(state);
	cedit_swapdraw();
	draw_shell(state);

	while (true)
	{
	}
}