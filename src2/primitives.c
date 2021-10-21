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

#include "primitives.h"
#include "cedit.h"
#include "editor.h"
#include "state.h"
#include "gfx.h"
#include "tigcclib.h"

void draw_radio_button(struct estate *state, int x, int y, bool on){
    return;
}
void draw_checkbox(struct estate *state, int x, int y, bool on){
    return;
}
void draw_switch(struct estate *state, int x, int y, bool on){
        gfx_SetColor(on?state->focus_color:state->background_color);
        gfx_FillCircle_NoClip(x+7,y+7,7);
        gfx_FillCircle_NoClip(x+21,y+7,7);
        gfx_SetColor(state->border_color);
        gfx_Circle_NoClip(x+7,y+7,7);
        gfx_Circle_NoClip(x+21,y+7,7);
        gfx_HorizLine_NoClip(x+7,y,14);
        gfx_HorizLine_NoClip(x+7,y+14,14);
        gfx_SetColor(on?state->focus_color:state->background_color);
        gfx_FillRectangle_NoClip(x+7,y+1,14,13);
        gfx_SetColor(state->statusbar_color);
        gfx_FillCircle_NoClip(x+(on?21:7),y+7,7);
        gfx_SetColor(state->border_color);
        gfx_Circle_NoClip(x+(on?21:7),y+7,7);
}
void draw_slider_rail(struct estate *state, int x, int y, int length){
    return;
}
void draw_slider_arrow(struct estate *state, int x, int y, bool on){
    return;
}
