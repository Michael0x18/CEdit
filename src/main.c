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

#include "cedit.h"
#include "gfx.h"
#include "dialogs.h"
#include "editor.h"
#include "tigcclib.h"

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
