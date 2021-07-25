#ifndef gfx_c
#define gfx_c

#include "../src_old/gfx.h"

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

#include "../src/tigcclib.h"

bool load_gfx_config(void) {
	font = fontlib_GetFontByIndex(fontname,fonttype);
	if(!font){
		os_ClrHome();
		os_PutStrFull("E1: Font pack not found.");
		ngetchx();
		return 1;
	}
	fontlib_SetFont(font,0);
	fontlib_SetForegroundColor(text_color);
	fontlib_SetTransparency(transparent_color);
	fontlib_SetBackgroundColor(background_color);
	//TODO implement graphics config loading
	//load defaults
	return 0;
}

bool init_gfx(void) {
	if(load_gfx_config())
		return 1;
	gfx_SetDrawBuffer();
	gfx_Begin();
	return 0;
}

void end_gfx(void) {
	gfx_End();
}

#endif
