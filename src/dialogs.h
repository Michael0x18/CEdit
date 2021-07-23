#ifndef dialogs_h
#define dialogs_h

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

#define cr 20

/*
 * Draws a dialog with an empty background
 * params x,y,width,height
 */
void draw_dialog(int,int,int,int);

/*
 * Draws the open file dialog
 */
void show_open_dialog(void);

/*
 * Draws the save file dialog
 */
void show_save_dialog(void);
/*
 * Draws the about dialog
 */
void show_about_dialog(void);

#include "dialogs.c"

#endif
