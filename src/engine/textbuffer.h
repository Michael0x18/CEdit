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
// |>| | | |H|e|l|l|o| |H|e|l|l|o| | | | | |H|e|l|l|o|w|o|r| |
// +-+-+-+-+-+-+-+-+-+ +-+-+-+-+-+-+-+-+-+ +-+-+-+-+-+-+-+-+-+
//    ^   ^                       ^     ^                   ^^
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
	// Left gapped array cursor
	uint24_t left_cursor;
	// Right gapped aray cursor
	uint24_t right_cursor;
	// current size, in bytes, of the array
	uint24_t size;
	// Maximum size, in bytes, of the array
	uint24_t max_size;
	// pointer
	unsigned char *text;
	unsigned char *buffer;
	uint24_t buffer_size;
	uint24_t buffer_max_size;
};

/**
 * Creates and returns a heap allocated instance of a textbuffer.
 * text must be size max_size+1.
 * Arguments:
 * unsigned char *text -> pointer to the buffer to use as a textbuffer (to store the gapped array)
 * uint24_t max_size -> maximum size of the textbuffer; one less than the size of ^
 * unsigned char *buffer -> storage for buffered data, used in burst mode
 * uint24_t buffer_size -> maximum storage size for buffered data, used in burst mode
 */
struct textbuffer_t *mktextbuffer(unsigned char *text, uint24_t max_size, unsigned char *buffer, uint24_t buffer_size);

/**
 * Inserts a value into the textbuffer at the specified index
 */
bool textbuffer_insert(struct textbuffer_t *t, uint24_t index, unsigned char c);

/**
 * Stash a character into the textbuffer's low latency buffer.
 * Extremely fast.
 */
bool textbuffer_buffered_insert(struct textbuffer_t *t, unsigned char c);

/**
 * Removes and returns the value at the specified index
 */
unsigned char textbuffer_remove(struct textbuffer_t *t, uint24_t index);

/**
 * Returns the value at the specified index.
 * Does not change the internal structure of the gap
 * O(1)
 */
unsigned char textbuffer_get(struct textbuffer_t *t, uint24_t index);

/**
 * Aligns the textbuffer's internal gap to the specified index
 * This makes it immediately ready for an insert or removal
 * operation
 * O(N)
 */
void textbuffer_align_gap(struct textbuffer_t *t, uint24_t index);

void textbuffer_flush(struct textbuffer_t *t, uint24_t index);

#endif