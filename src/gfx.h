#ifndef gfx_h
#define gfx_h

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

static uint8_t text_color			=	0;
static uint8_t text_highlight_color	=	1;
static uint8_t background_color		=	255;
static uint8_t transparent_color	=	1;
static uint8_t statusbar_color		=	11;
static uint8_t border_color			=	0;
static uint8_t dropshadow_color		=	11;
static char fontname[] 				=	"DrMono";
static int8_t fonttype 				=	3;
fontlib_font_t *font;

/*
 * Loads the graphics configuration from
 * the config file.
 * Also configures font data.
 */
bool load_gfx_config(void);


/*
 * Initialize graphics
 */
bool init_gfx(void);

/*
 * Return to OS state
 */
void end_gfx(void);

#include "gfx.c"

#endif
