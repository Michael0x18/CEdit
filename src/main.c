#include "cedit.h"
#include "engine/textbuffer.h"
#include "config.h"
#include "gfx.h"

int main(int argc, char **argv)
{
	static struct estate state;
	dbg_printf("Begin CEdit execution\n");
	dbg_printf("argc: %d\n", argc);
	dbg_printf("File IO is unimplemented. TODO!\n");
	cedit_defaults(&state);
	init_x4();
	editor_mainloop(&state);
	end_x4();
	free(state.config);
	free(state.text);
	dbg_printf("End Execution\nBye!\n");
}