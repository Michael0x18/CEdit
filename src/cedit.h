/*
 * cedit.h
 *
 *  Created on: Jul 25, 2021
 *      Author: michael
 */

#ifndef SRC_CEDIT_H_
#define SRC_CEDIT_H_

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
#include "tigcclib.h"
#include "editor.h"
#include "dialogs.h"
#include "gfx.h"
#include "libmalloc.h"

#define CEDIT_VERSION_STRING "CEDIT 0.07 BETA"

/*
 * Main function
 */
int main(int,char**);

/*
 * Initializes the editor
 */
bool initialize(struct estate*);

#endif /* SRC_CEDIT_H_ */
