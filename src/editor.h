/*
 * editor.h
 *
 *  Created on: Jul 25, 2021
 *      Author: michael
 */

#ifndef SRC_EDITOR_H_
#define SRC_EDITOR_H_

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
#include "gfx.h"

void cursor_up_select(struct estate*);
void cursor_down_select(struct estate*);
void cursor_left_select(struct estate*);
void cursor_right_select(struct estate*);
/*
 * Event loop
 */
void editor_mainloop(struct estate*);

/*
 * Initializes all the global variables.
 */
void init_editor(struct estate*);

/*
 * Returns true if the character passed is a control character,
 * or false if it isn't.
 */
bool is_control(short);

/*
 * Draws the editor interface
 * Returns true if the cursor was drawn on the screen,
 * false otherwise.
 */
int draw_editor(struct estate*);

/*
 * Handles a non-quit keypress
 * Arguments:
 */
void handle_key(struct estate*, short);

/*
 * Inserts a new line into the line buffer.
 * Also splits.
 */
void insert_newline(struct estate*);

/*
 * Inserts a character into the buffer.
 */
void insert_char(struct estate*, char);

/*
 * Move the text cursor one character left.
 */
void cursor_left(struct estate*);

/*
 * Move the text cursor one character right.
 */
void cursor_right(struct estate*);

/*
 * Move the text cursor one line up.
 */
void cursor_up(struct estate*);

/*
 * Moves up (cleanup)
 */
void line_up(struct estate*);

/*
 * Moves down(cleanup)
 */
void line_down(struct estate*);

/*
 * Move the text cursor one line down.
 */
void cursor_down(struct estate*);

/*
 * Performs backspace
 */
void bs(struct estate*);

/*
 * Performs delete.
 */
void del(struct estate*);

/*
 * Scrolls the screen so that the cursor is on the first line.
 */
void scroll_up(struct estate*);

/*
 * Scrolls the screen so that the cursor is on the last line.
 */
void scroll_down(struct estate*);

/*
 * Moves the text cursor to the start of the buffer.
 */
void cursor_to_start(struct estate*);

void cursor_to_start_select(struct estate*);

/*
 * Moves the text cursor to the end of the buffer.
 */
void cursor_to_end(struct estate*);

void cursor_to_end_select(struct estate*);

/*
 * Moves the text cursor one word left.
 */
void cursor_to_left_word(struct estate*);
void cursor_to_left_word_select(struct estate*);

/*
 * Moves the text cursor one word right.
 */
void cursor_to_right_word(struct estate*);
void cursor_to_right_word_select(struct estate*);

/*
 * Moves the text cursor multi_lines lines up.
 */
void cursor_multi_up(struct estate*);
void cursor_multi_up_select(struct estate*);

/*
 * Moves the text cursor multi_lines lines down.
 */
void cursor_multi_down(struct estate*);
void cursor_multi_down_select(struct estate*);

/*
 * Moves the text cursor to start of line
 */
void cursor_to_l_start(struct estate*);
void cursor_to_l_start_select(struct estate*);

/*
 * Moves cursor to end of line
 */
void cursor_to_l_end(struct estate*);
void cursor_to_l_end_select(struct estate*);

/*
 * Loads text from filename into the editor.
 */
void load_text(struct estate*);

/*
 * Writes the file to disk.
 */
void write_file(struct estate*);

#endif /* SRC_EDITOR_H_ */
