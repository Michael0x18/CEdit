/*
 * main.c
 *
 *  Created on: Jul 25, 2021
 *      Author: michael
 */

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

#include "state.h"
#include "cedit.h"
#include "tigcclib.h"
#include "editor.h"
#include "dialogs.h"
#include "gfx.h"

void initialize(struct estate *state) {
	state->multi_lines=5;
	strncpy("Untitled",state->filename,8);
	state->named=false;
	state->lc1=
}

void main(int argc, char **argv) {
	static struct estate editor_state;
	initialize(editor_state);
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
