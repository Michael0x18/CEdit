#include "gfx.h"

void init_x4(void)
{
	x4_Begin();
	x4_SetScreenLocation(X4_BUFFER_1);
	x4_SetDrawLocation(X4_BUFFER_2);
}

void end_x4(void)
{
	x4_SetScreenLocation(X4_BUFFER_1);
	x4_End();
}