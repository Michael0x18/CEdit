/////////////////////////////////////////////////
// FILE main.h                                 //
// Contains prototypes of functions in main.c  //
// as well as constants and macros             //
/////////////////////////////////////////////////
#ifndef main_h
#define main_h
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

//Maximum size of the editor buffer
#define MAX_BUFFER_SIZE 16384
//The color used for the text
#define FG_COLOR 255
//The color used for the editor background
#define BG_COLOR 0
//The transparent color
#define TRANSPARENT_COLOR 1
//The color for the status bar backgrounds
#define STATUSBAR_COLOR 120

//True if the filename is set, false otherwise.
bool hasfilename = 0;
//The filename that is currently open for editing
static char filename[10];
//The text currently in the editor buffer
static char text[MAX_BUFFER_SIZE];
//The line lengths buffer
static char lines[MAX_BUFFER_SIZE];
//left line cursor -- is on the line with the cursor
static int24_t lc1;
static int24_t lc2;
static int24_t lc_offset;
static int24_t ls_offset;
//The left side of the cursor
static int24_t c1;
//The right side of the cursor
static int24_t c2;
//The position of the start of the screen
static int24_t scr_offset;
//Contents of the ANS variable -- used for
//Cesium compatibility
static string_t* Ans_Data;

//Returns true if the short passed as an argument
//is a control character, false otherwise.
bool is_control(short);

//Redraws the main editor screen, scrolling if the cursor
//is not visible
void redraw_editor(void);

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

//Attempts to fetch a string from the ANS variable.
//If such a string exists, e.g. if this is called
//as an editor program from Cesium, it sets filename.
void attempt_load_cesium(void);

//Attempts to load file names in the following order:
//1) Cesium
//2) BOSshell
//3) Xenon
//4) VYSion
void load_file_name(void);

//Reads into the buffer the contents of the file
//denoted by filename, if it exists.
void open_file(void);

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

//scrolls up a single row
void scroll_up(void);

//scrolls down a single row
void scroll_down(void);

//main function
void main(int argc, char** argv);
#endif
