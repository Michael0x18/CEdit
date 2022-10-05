#include "scroll.h"

bool check_scroll_and_execute(struct estate *state)
{
	if (state->cursor_y < 0)
	{
		scroll_up();
		return 1;
	}
	else if (state->cursor_y >= 13)
	{
		scroll_down();
		return 1;
	}
	return 0;
}

void scroll_up(struct estate *state)
{
}