#ifndef primitives_h
#define primitives_h

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
#include "editor.h"
#include "state.h"
#include "gfx.h"
#include "tigcclib.h"


void draw_radio_button(struct estate *state, int x, int y, bool on);
void draw_checkbox(struct estate *state, int x, int y, bool on);
void draw_switch(struct estate *state, int x, int y, bool on);
void draw_slider_rail(struct estate *state, int x, int y, int length);
void draw_slider_arrow(struct estate *state, int x, int y, bool on);

#endif