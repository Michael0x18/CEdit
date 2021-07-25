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

#include "../src/cfg.h"

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

#include "../src/gfx.c"

#endif
