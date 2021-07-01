/////////////////////////////////////////////////
// FILE main.h                                 //
// Contains prototypes of functions in main.c  //
// as well as constants and macros             //
/////////////////////////////////////////////////

//Version

#ifndef main_h
#define main_h
#define VERSION_STRING "CEdit V0.01 ALPHA"
//Headers
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

//Definitions

//Maximum size of the editor buffer
#define MAX_BUFFER_SIZE 16384
//the number of columns to wrap to
//Here it is 30, because 32 is the max, one on the left is reserved for the newline indicator ":", and one on the right is reserved for the scrollbar.
#define NUM_COLS 36
//The color used for the text
#define FG_COLOR 255
//The color used for the editor background
#define BG_COLOR 0
//The transparent color
#define TRANSPARENT_COLOR 1
//The color for the status bar backgrounds
#define STATUSBAR_COLOR 120
//The number of lines scrolled by multi_up and multi_down
#define MULTI_LINES 5

//Smart wrap is currently borked.
//#define SMART_WRAPPING

fontlib_font_t *drmono;

//GLobals

//True if the filename is set, false otherwise.
bool hasfilename = 0;
//The filename that is currently open for editing
static char filename[10];
//The text currently in the editor buffer
static char text[MAX_BUFFER_SIZE+1];
//The line lengths buffer
static int24_t lines[MAX_BUFFER_SIZE+1];
//left line cursor -- is on the line with the cursor
static int24_t lc1;
//right line cursor -- points to one past the right side
static int24_t lc2;
//Offset of the cursor from the start of a line
static int24_t lc_offset;
//Offset of the screen from the start of a line. Always a multiple of NUM_COLS
static int24_t ls_offset;
//The left side of the cursor
static int24_t c1;
//The right side of the cursor
static int24_t c2;
//The position of the start of the screen
static int24_t scr_offset;
//Last drawn X position of the cursor, used for animation
static int24_t cursor_x;
//Last drawn Y position of the cursor, used for animation
static int24_t cursor_y;
//True if the cursor is drawn
static bool c_on;
//True if the editor is up
static bool editor_on;
//The line which scr_offset is positioned at.
static int24_t scr_line;

//Returns true if the short passed as an argument
//is a control character, false otherwise.
bool is_control(short);

//Redraws the main editor screen, scrolling if the cursor
//is not visible
void redraw_editor(void);

//Inserts a newline into the line buffer
void insert_newline(void);

//Inserts the specified character into the buffer, updating
//the pointers accordingly.
void insert_char(char);

//Draws a file save screen
void draw_file_save_dialog(void);

//Tests if the static filename variable is a valid file name
bool is_valid(void);

//Writes the contents of the buffer to a file.
//Prompts the user for a filename if not already specified.
void save_file(void);

//Reads into the buffer the contents of the file
//denoted by filename, if it exists.
void open_file(void);

//Move to the previous line
void line_up(void);

//Move to the next line
void line_down(void);

//moves the text cursor one character left
void cursor_left(void);

//moves the text cursor one character right
void cursor_right(void);

//moves the text cursor one character up
void cursor_up(void);

//moves the text cursor one character down
void cursor_down(void);

//backspace
void bs(void);

//delete
void del(void);

//scrolls up from the cursor
void scroll_up(void);

//scrolls down from the cursor
void scroll_down(void);

//scrolls down a single row
void scroll_down_line();

//Moves cursor to start of buffer
void cursor_to_start(void);

//Moves cursor to end of buffer
void cursor_to_end(void);

//Moves cursor left by one word
void cursor_left_word(void);

//Moves cursor right by one word
void cursor_right_word(void);

//Moves cursor up by MULTI_LINES lines
void cursor_multi_up(void);

//Moves cursor down by MULTI_LINES lines
void cursor_multi_down(void);

//Moves cursor to start of line
void cursor_to_l_start(void);

//Moves cursor to end of line
void cursor_to_l_end(void);

//Draws a scroll bar
void draw_scroll(void);

//main function
void main(int argc, char** argv);
#endif
