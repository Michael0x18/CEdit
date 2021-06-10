/////////////////////////////////////////////////
// FILE main.h                                 //
// Contains prototypes of functions in main.c  //
// as well as constants and macros             //
/////////////////////////////////////////////////

//Version
#define VERSION_STRING "CEdit V0.00 ALPHA"

#ifndef main_h
#define main_h
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

//Definitions

//Maximum size of the editor buffer
#define MAX_BUFFER_SIZE 16384
//the number of columns to wrap to
#define NUM_COLS 32
//The color used for the text
#define FG_COLOR 255
//The color used for the editor background
#define BG_COLOR 0
//The transparent color
#define TRANSPARENT_COLOR 1
//The color for the status bar backgrounds
#define STATUSBAR_COLOR 120

//GLobals

//True if the filename is set, false otherwise.
bool hasfilename = 0;
//The filename that is currently open for editing
static char filename[10];
//The text currently in the editor buffer
static char text[MAX_BUFFER_SIZE];
//The line lengths buffer
static int24_t lines[MAX_BUFFER_SIZE];
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
//Contents of the ANS variable -- used for

//

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

//main function
void main(int argc, char** argv);
#endif
