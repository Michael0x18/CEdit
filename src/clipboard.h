/*
 * clipboard.h
 *
 *  Created on: Jul 26, 2021
 *      Author: michael
 */

#ifndef SRC_CLIPBOARD_H_
#define SRC_CLIPBOARD_H_

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
#include "editor.h"
#define USE_PERSISTENT_CLIPBOARD

void cb_copy(struct estate*);

void cb_cut(struct estate*);

void cb_paste(struct estate*);



#endif /* SRC_CLIPBOARD_H_ */