/*
 * gfx.h
 *
 *  Created on: Jul 25, 2021
 *      Author: michael
 */

#ifndef SRC_GFX_H_
#define SRC_GFX_H_

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

/*
 * Loads the graphics configuration from
 * the config file.
 * Also configures font data.
 */
bool load_gfx_config(struct estate*);


/*
 * Initialize graphics
 */
bool init_gfx(void);

/*
 * Return to OS state
 */
void end_gfx(void);

#endif /* SRC_GFX_H_ */
