#ifndef textbuffer_h
#define textbuffer_h

#include <stdio.h>
#include <stdlib.h>
#include <tice.h>
#include <intce.h>
#include <keypadc.h>
#include <graphx.h>
#include <string.h>
#include <debug.h>

// functions and structs involving a textbuffer, which is a highly abstracted way of storing text.
// Internal structure of a gapped textbuffer
// +-+-+-+-+-+-+-+-+-+ +-+-+-+-+-+-+-+-+-+ +-+-+-+-+-+-+-+-+-+
// |H|e| | | | |l|l|o| |H|e|l|l|o| | | | | |H|e|l|l|o|w|o|r| |
// +-+-+-+-+-+-+-+-+-+ +-+-+-+-+-+-+-+-+-+ +-+-+-+-+-+-+-+-+-+
//      ^     ^                   ^     ^                   ^^
//
//   Text being edited  Cursor at end        Full textbuffer
//

/**
 * A structure containing a buffer full of text data.
 * The structure consists of a gapped array, of size max_size+1,
 * which can contain up to max_size characters.
 * The internal structure uses two pointers to control the size
 * and position of the gap, allowing for O(1) insertion and removal
 * near the gap and O(N) insertion and removal elsewhere.
 *
 * There are several functions provided along with this data structure
 * to make usage easy, and to "paper over" the somewhat complicated
 * set of operations needed to access, shift, or otherwise interact
 * with a gapped array.
 */
struct textbuffer_t
{
	uint24_t left_cursor;
	uint24_t right_cursor;
	uint24_t size;
	uint24_t max_size;
	unsigned char *text;
};

/**
 * Creates and returns a heap allocated instance of a textbuffer.
 * text must be size max_size+1.
 */
struct textbuffer_t *mktextbuffer(int max_size, unsigned char *text);

/**
 * Inserts a value into the textbuffer at the specified index
 */
bool insert(struct textbuffer_t *t, uint24_t index, unsigned char c);

/**
 * Aligns the textbuffer's internal gap to the specified index
 * This makes it immediately ready for an insert or removal
 * operation
 * O(N)
 */
void align_gap(struct textbuffer_t *t, uint24_t index);