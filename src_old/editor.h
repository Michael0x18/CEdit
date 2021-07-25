#ifndef editor_h
#define editor_h

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

#define fw 8
#define ls 12
#define numl 17

#include "../src/gfx.h"

/*
 * Maximum size of the editor buffer, in bytes.
 * The default (and maximum) is 16 Kb.
 */
static int24_t max_buffer_size = 16384;

/*
 * The number of columns in the editor.
 * The default is 38
 */
static int24_t num_cols = 38;

/*
 * The number of lines scrolled by multi_up and multi_down
 * The default is 5
 */
static int24_t multi_lines = 5;

/*
 * The filename.
 * Default is "Untitled" (without the quotes)
 */
static char filename[10] = "Untitled";

/*
 * True if the filename has been changed from
 * the default.
 */
static bool named = false;

/*
 * The editor buffer.
 * The text is divided into two chunks: one before the cursor,
 * and one after. The one before the cursor is aligned with the
 * start of the text, and the one after is aligned at the end.
 * This allows the insertion and deletion of characters in O(1)
 * time. However, this limits the motion of the cursor to just a
 * left and right movement in its most basic form; all other
 * movements, like up and down, must come from the base functions.
 */
static char text[16385];

/*
 * The line length cache.
 * The number of characters in each line is saved while editing,
 * allowing the offset and wrap points to be computed in O(1)
 * time instead of in O(n) time, which is an advantage for larger
 * files.
 */
static int24_t lines[16385];

/*
 * A pointer within the line array that resides on the same line
 * as the text cursor.
 */
static int24_t lc1;

/*
 * A pointer within the line array that resides on the line after
 * the text cursor.
 */
static int24_t lc2;

/*
 * The offset of the cursor from the start of a line, not counting
 * line wrap.
 */
static int24_t lc_offset;

/*
 * The offset of the screen from the start of a line.
 * Always a multiple of num_cols.
 */
static int24_t ls_offset;

/*
 * A pointer within the text array that is just to the left of the
 * text cursor, because the cursor goes in between characters.
 */
static int24_t c1;

/*
 * A pointer within the text array that is just to the right of the
 * text cursor, because the cursor goes in between characters.
 */
static int24_t c2;

/*
 * The offset of the screen from the start of the file.
 */
static int24_t scr_offset;

/*
 * The line at which scr_offset is positioned at.
 */
static int24_t scr_line;

/*
 * The line offset of the screen position.
 */
static int24_t scr_line_offset;

////////////FUNC////////////

/*
 * Initializes all the global variables.
 */
void init_editor(void);

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
int draw_editor(void);

/*
 * Main loop for the editor.
 * Runs until exit.
 */
void editor_mainloop(void);

/*
 * Handles a non-quit keypress
 * Arguments:
 */
void handle_key(short);

/*
 * Inserts a new line into the line buffer.
 * Also splits.
 */
void insert_newline(void);

/*
 * Inserts a character into the buffer.
 */
void insert_char(char);

/*
 * Move the text cursor one character left.
 */
void cursor_left(void);

/*
 * Move the text cursor one character right.
 */
void cursor_right(void);

/*
 * Move the text cursor one line up.
 */
void cursor_up(void);

/*
 * Moves up (cleanup)
 */
void line_up(void);

/*
 * Moves down(cleanup)
 */
void line_down(void);

/*
 * Move the text cursor one line down.
 */
void cursor_down(void);

/*
 * Performs backspace
 */
void bs(void);

/*
 * Performs delete.
 */
void del(void);

/*
 * Scrolls the screen so that the cursor is on the first line.
 */
void scroll_up(void);

/*
 * Scrolls the screen so that the cursor is on the last line.
 */
void scroll_down(void);

/*
 * Moves the text cursor to the start of the buffer.
 */
void cursor_to_start(void);

/*
 * Moves the text cursor to the end of the buffer.
 */
void cursor_to_end(void);

/*
 * Moves the text cursor one word left.
 */
void cursor_to_left_word(void);

/*
 * Moves the text cursor one word right.
 */
void cursor_to_right_word(void);

/*
 * Moves the text cursor multi_lines lines up.
 */
void cursor_multi_up(void);

/*
 * Moves the text cursor multi_lines lines down.
 */
void cursor_multi_down(void);

/*
 * Moves the text cursor to start of line
 */
void cursor_to_l_start(void);

/*
 * Moves cursor to end of line
 */
void cursor_to_l_end(void);

/*
 * Loads text from filename into the editor.
 */
void load_text(void);

void write_file(void);

#include "../src/editor.c"

#endif
