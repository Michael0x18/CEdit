#ifndef main_c
#define main_c

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

#include "../src/cedit.h"
#include "../src/dialogs.h"
#include "../src_old/editor.h"
#include "../src_old/gfx.h"
#include "../src_old/tigcclib.h"

void main(int argc, char **argv) {
	//Argument parsing
	if (argc == 2) {
		strncpy(filename, argv[1], 8);
		named = true;
	} else if (argc > 2) {
		os_ClrHome();
		os_PutStrFull("Usage: CEdit FILE");
		while (!os_GetCSC())
			;
		return;
	}
	init_editor();
	if (init_gfx()) {
		os_ClrHome();
		os_PutStrFull("E0: gfx-err");
		ngetchx();
		return;
	}
	editor_mainloop();
	end_gfx();
}

#endif
