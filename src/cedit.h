#ifndef cedit_h
#define cedit_h

#include <stdio.h>
#include <stdlib.h>
#include <tice.h>
#include <intce.h>
#include <keypadc.h>
#include <graphx.h>
#include <string.h>

#include "x4/libx4.h"

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

/*
in the graphics palette
0   text foreground
1   text bg
2   highlight text fg
3   htbg
4   selection fg
5   selection bg
6   statusbar fg
7   statusbar bg
8   editor bg
9   shadow color
10
11
12
13
14
15
*/

struct estate
{
    // Maximum size of the file being edited.
    // Default is 65536. Changin this is mainly relevant for BOS
    uint24_t max_file_size;

    // Points to the character just to the left of the cursor, i.e. where
    // to write a character that is going to be typed
    uint24_t cursor_left;
    // Points to the character just to the right of the cursor
    uint24_t cursor_right;

    // The offset in the file where the highlighted text starts. It can
    // be either smaller than cursor_left, in which case the user is highlighting
    // to the right, or larger than cursor_right, in which case the user is
    // highlighting to the left
    uint24_t highlight_anchor;
    // True if the user is currently doing a highlight operation, false otherwise
    bool highlight_enabled;

    // True if the contents of the buffer match what is in the output file
    bool saved;
    // True if:
    // 1) The user has opened an already existing file
    // 2) The user has chosen a name during the first save operation of a new file
    // 3) The user has chosen to save a copy of an existing file
    bool named;
    // Eight character (maximum) file name.
    // This is the name that is displayed to the user.
    char filename[8];
    // If true, the first letter of the file name will be XOR'd with 64 before each
    // save, and then the unhidden version of the file (if it exists)
    bool hidden;
    // The variable to store the clipboard data to.
    // On TIOS, the default is CLIPBOARD
    // On BOS, the clipboard is stored in system memory (hopefully?)
    char clipboard_var[8];
    // A pointer to the text buffer.
    // In both TIOS, this is a pointer to the latter half of VRAM.
    // Using 4bpp mode means that we can double-buffer using only the first half.
    // On TIOS, the text can go up to a maximum of 64KiB.
    // On BOS, this will still point to VRAM, except with an optional extension
    // to allow larger files. Note that this is unlikely, as a human edited text file
    // is unlikely to exceed 64KiB
    char *text;

    // True if CEdit should apply wordwrap.
    // Separater characters (between words) are the following:
    // Spaces, periods, commas, line feeds, colons, semicolons, single quotes,
    // double quotes, the forward slash, the asterix and the plus sign.
    // Note that enabling this setting causes the editor core to reparse the
    // ENTIRE file, as things like line offsets must be recalculated from scratch.
    bool wordwrap;

    // If true, the hardware cursor will be shown and the arrow keys will
    // control it. The 2nd key will click to move the cursor, and holding
    // it and moving the cursor will select. If false, the arrow keys will
    // move the text cursor, the hardware cursor will be hidden, and the 2nd
    // key will go back to being a modifier key for shortcuts.
    bool mouse_enabled;
    // If true, the cursor will pulse to make it easier to locate.
    bool blink_cursor;

    // The character offset, in bytes, from the beginning of the file, for
    // the character just before the upper left corner of the screen.
    uint24_t screen_start_offset;
    // The number of newlines before the first character on screen.
    uint24_t screen_line_raw_offset;
    // The number of full lines (newlines and wrapped) before the first
    // character on screen.
    uint24_t screen_line_actual_offset;
    // The number of characters on the same line as the first character
    // on the screen that are not shown.
    uint24_t screen_line_sub_offset;
    // The character offset, in bytes, from the beginning of the file, for
    // the last character on the screen.
    uint24_t screen_end_offset;

    // The x position of the cursor, in characters.
    uint8_t cursor_x;
    // The y position of the cursor, in characters.
    uint8_t cursor_y;
    // The total number of lines in the file. Including newlines and wraps
    uint24_t num_lines;
    // The number of newlines before the left cursor
    uint24_t cursor_line_raw;
    // The number of newlines plus the number of wraps before the left cursor
    uint24_t cursor_line_actual;
    // The cursor position within the line.
    uint24_t cursor_line_sub_offset;

    // Cache for status bars. This is the third x4 buffer plus 65536 bytes.
    // It has a size of 5120 bytes, and holds the top status bar (16 pixels)
    // followed immediately by the bottom status bar (16 pixels)
    void *statusbar_cache_memory;

    // Width of the screen, in characters
    uint8_t scr_width;
    // Height of the screen, in characters
    uint8_t scr_height;

    uint8_t font_buffer[128][8][8];
    uint8_t font_buffer_highlight[128][8][8];
    uint8_t font_buffer_select[128][8][8];
    uint8_t font_buffer_statusbar[128][8][8];
};

/*
 * Main
 */
int main(int argc, char **argv);

void cedit_swapdraw(void);

#endif

/*

// Foreground color of editor body text. This is also the cursor color
    uint8_t text_color_foreground;
    // Background (highlight) color of editor body text
    uint8_t text_color_background;
    // Foreground (text) color of status bars
    uint8_t statusbar_color_foreground;
    // Background color of status bars
    uint8_t statusbar_color_background;
    // Background color to use when highlighting text
    uint8_t highlight_color_foreground;
    // The background color for the entire body.
    uint8_t editor_body_background;
    // The color for the (tasteful) shadows drawn under UI elements
    uint8_t shadow_color;
    // Color for foreground of selected UI elements
    uint8_t ui_selection_foreground_color;
    // Color for background of selected UI elements
    uint8_t ui_selection_background_color;

*/