#include <stdio.h>
#include <stdlib.h>
#include <tice.h>
#include <intce.h>
#include <keypadc.h>
#include <graphx.h>
#include <string.h>
#include <debug.h>

#include "x4/libx4.h"

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

int main(int argc, char **argv)
{
	init_x4();

	end_x4();
}