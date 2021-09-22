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
 * Presents to the user a color selection dialog.
 */
uint8_t show_color_selection_dialog(struct estate *, uint8_t);

/*
 * Links to the keybind information
 */
void show_keybind_dialog(struct estate *);
/*
 * Displays the editor settings:
 * tabstop, preserve clipboard on exit,
 * multi_lines
 */
void show_editor_settings_dialog(struct estate *);

/* Allows customizing Appearance settings
 */
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
 */
void show_open_dialog(struct estate *);

/*
 * Draws the save file dialog
 */
bool show_save_dialog(struct estate *);
/*
 * Draws the about dialog
 */
void show_about_dialog(struct estate *);

/*
 * TODO - for a later data.
 */
void show_persistence_dialog(struct estate *state)

void show_search_dialog(struct estate *state);

#endif /* SRC_DIALOGS_H_ */
