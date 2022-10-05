#include "textbuffer.h"

struct textbuffer_t *mktextbuffer(int max_size, unsigned char *text)
{
	struct textbuffer_t *ret_text = (struct textbuffer_t *)malloc(sizeof(struct textbuffer_t));
	ret_text->left_cursor = 0;
}

bool insert(struct textbuffer_t *t, uint24_t index, unsigned char c)
{
	align_gap(t, index);
}

void align_gap(struct textbuffer_t *t, uint24_t index)
{
	// Check which side of the gapped array it's on
	if (index < t->left_cursor)
	{
		// If it's on the left side of the left cursor,
		// We need to shift right
		// diff is the count we need to shift
		uint24_t diff = t->left_cursor - index;
		// Do a block copy from the left to the right
		memmove(t->right_cursor - diff + 1, index, diff);
		// Move the left cursor to the index
		t->left_cursor = index;
		// Move the right cursor left by diff
		t->right_cursor -= diff;
	}
	else if (index > t->right_cursor)
	{
		// if it's on the right side of the right cursor
		// We need to shift left
		uint24_t diff = index - t->right_cursor;
		memmove(t->left_cursor, t->right_cursor + 1, diff);
		t->right_cursor = index;
		t->left_cursor += diff;
	}
}