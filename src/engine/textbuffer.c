#include "textbuffer.h"

struct textbuffer_t *mktextbuffer(unsigned char *text, uint24_t max_size, unsigned char *buffer, uint24_t buffer_max_size)
{
	struct textbuffer_t *ret_text = (struct textbuffer_t *)malloc(sizeof(struct textbuffer_t));
	ret_text->left_cursor = 0;
	ret_text->right_cursor = max_size;
	ret_text->text = text;
	ret_text->buffer = buffer;
	ret_text->max_size = max_size;
	ret_text->size = 0;
	ret_text->buffer_size = 0;
	ret_text->buffer_max_size = buffer_max_size;

	return ret_text;
}

bool textbuffer_insert(struct textbuffer_t *t, uint24_t index, unsigned char c)
{
	// If there is no more room left
	if (t->size >= t->max_size)
		return 1;
	// Move the gap
	textbuffer_align_gap(t, index);
	// Write the data
	t->text[t->left_cursor++] = c;
	t->size++;
	return 0;
}

bool textbuffer_buffered_insert(struct textbuffer_t *t, unsigned char c)
{
	if (t->buffer_size == t->buffer_max_size)
	{
		textbuffer_flush(t, t->size);
		t->buffer[t->buffer_size++] = c;
		return true;
	}
	t->buffer[t->buffer_size++] = c;
	return false;
}

unsigned char textbuffer_get(struct textbuffer_t *t, uint24_t index)
{
	if (index < t->left_cursor)
	{
		// Left side, effective index remains the same
		return t->text[index];
	}
	else
	{
		return t->text[index + t->right_cursor + 1 - t->left_cursor];
	}
}

void textbuffer_align_gap(struct textbuffer_t *t, uint24_t index)
{
	// Check which side of the gapped array it's on
	if (index < t->left_cursor)
	{
		// If it's on the left side of the left cursor,
		// We need to shift right
		// diff is the count we need to shift
		uint24_t diff = t->left_cursor - index;
		// Do a block copy from the left to the right
		memmove(t->text + t->right_cursor - diff + 1, t->text + index, diff);
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
		memmove(t->text + t->left_cursor, t->text + t->right_cursor + 1, diff);
		t->right_cursor = index;
		t->left_cursor += diff;
	}
}

unsigned char textbuffer_remove(struct textbuffer_t *t, uint24_t index)
{
	align_gap(t, index);
	if (index < t->left_cursor)
	{
		// Left side, effective index remains the same
		t->size--;
		return t->text[--t->left_cursor];
	}
	else
	{
		t->size--;
		return t->text[index + t->right_cursor++ - 1];
	}
}

void textbuffer_flush(struct textbuffer_t *t, uint24_t index)
{
	for (int i = 0; i < t->buffer_size; i++)
	{
		textbuffer_insert(t, index++, t->buffer[i]);
	}
	t->buffer_size = 0;
}