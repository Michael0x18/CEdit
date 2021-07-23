#ifndef dialogs_c
#define dialogs_c

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

#include "dialogs.h"
#include "gfx.h"
#include "editor.h"

void draw_dialog(int x, int y, int w, int h) {
	draw_editor();
	gfx_SetColor(border_color);
	gfx_Circle_NoClip(x + cr, y + cr, cr);
	gfx_Circle_NoClip(x + w - cr - 1, y + cr, cr);
	gfx_Circle_NoClip(x + cr, y + h - cr - 1, cr);
	gfx_Circle_NoClip(x + w - cr - 1, y + h - cr - 1, cr);
	gfx_Rectangle_NoClip(x + cr, y, w - cr - cr, h);
	gfx_Rectangle_NoClip(x, y + cr, w, h - cr - cr);
	gfx_SetColor(background_color);
	gfx_FillCircle_NoClip(x + cr, y + cr, cr-1);
	gfx_FillCircle_NoClip(x + w - cr - 1, y + cr, cr-1);
	gfx_FillCircle_NoClip(x + cr, y + h - cr - 1, cr-1);
	gfx_FillCircle_NoClip(x + w - cr - 1, y + h - cr - 1, cr-1);
	gfx_FillRectangle_NoClip(x + cr+1, y+1, w - cr - cr+2, h-2);
	gfx_FillRectangle_NoClip(x+1, y + cr-1, w-2, h - cr - cr+2);
}

void show_open_dialog(void) {

}

void show_save_dialog(void) {

}

void show_about_dialog(void) {
	draw_dialog(60, 60, 200, 120);
	gfx_SwapDraw();
	ngetchx();
}

#endif
