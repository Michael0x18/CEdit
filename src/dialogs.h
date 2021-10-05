/*
 * dialogs.h
 *
 *  Created on: Jul 25, 2021
 *      Author: michael
 */

#ifndef SRC_DIALOGS_H_
#define SRC_DIALOGS_H_

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

/*
 * Displays the editor settings:
 * tabstop, preserve clipboard on exit,
 * multi_lines
 */
void show_editor_settings_dialog(struct estate *);

void show_appearance_settings_dialog(struct estate *);

/*
 * Draws the main menu
 * The main menu will open various sub-dialogs for additional settings/options.
 * They will open on top of each other.
 */
void show_menu_dialog(struct estate *);

/*
 * The backend drawing for the menu. Used to restore state after being
 * damaged by submenus, and for smaller drawing routines.
 */
void menu_backend_draw(struct estate *, int);

/*
 * Draws a dialog with an empty background
 * params x,y,width,height
 */
void draw_dialog(struct estate *, int, int, int, int);

/*
 * Draws the open file dialog
 * returns true if a new file was picked, false otherwise
 */
bool show_open_dialog(struct estate *);

/*
 * Draws the save file dialog
 */
bool show_save_dialog(struct estate *);
/*
 * Draws the about dialog
 */
void show_about_dialog(struct estate *);

//returns true if discard
bool show_unsaved_dialog(struct estate *);

#endif /* SRC_DIALOGS_H_ */
