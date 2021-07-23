/*
 * CEdit is a text editor for the TI-84 plus CE graphing calculator
 * It is currently under development.
 * CEdit is Free and Open Source Software, and may be used under the
 * terms of the GNU Lesser General Public License
 */

#ifndef cedit_h
#define cedit_h

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


/*
 * Main function
 */
void main(int, char**);

#include "main.c"

#endif
