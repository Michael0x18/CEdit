#ifndef cedit_h
#define cedit_h

#include <stdio.h>
#include <stdlib.h>
#include <tice.h>
#include <intce.h>
#include <keypadc.h>
#include <graphx.h>
#include <string.h>
#include <debug.h>

#include "x4/libx4.h"
#include "keys.h"
#include "engine/textbuffer.h"

#define TEXT_FG_COLOR 0
#define TEXT_BG_COLOR 1
#define HIGH_FG_COLOR 2
#define HIGH_BG_COLOR 3
#define SELE_FG_COLOR 4
#define SELE_BG_COLOR 5
#define STAT_FG_COLOR 6
#define STAT_BG_COLOR 7
#define EDIT_BG_COLOR 8
#define SHAD_FG_COLOR 8

struct estate
{
	struct textbuffer_t *text;		// Holds the text buffer in operation
	struct cedit_config *config;	// Holds the editor config
	bool saved;						// True if the file is synced with disk
	bool named;						// True if the user has assigned a name to the file
	unsigned char filename[8];		// Holds file name
	bool hidden;					// True if the file should be hidden on save
	unsigned char clipboard_var[8]; // Holds the variable to stash the clipboard to

	uint8_t font_buffer[128][8][8];
	uint8_t font_buffer_statusbar[128][8][8];

	uint8_t modifiers[4];  // Holds modifier keys
	int24_t timeout_max;   // Low latency normal timeout
	int24_t timeout_first; // Low latency trigger timeout

	int24_t screen_start_offset; // The starting point of the screen

	int24_t cursor; // The index the user's cursor is at

	int8_t cursor_x;
	int8_t cursor_y;

	unsigned char *cache; // buffer of size (scr_width+1) * scr_height. Stores the text that will be drawn onto the screen.
};

struct cedit_config
{
	bool wordwrap;
	bool blink_cursor;
	uint8_t scr_width;
	uint8_t scr_height;
	bool archive_on_save;
};

// extern void editor_mainloop(struct estate *state);

#endif