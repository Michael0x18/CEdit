#include "general.h"

/**
 * general.c contains routines that are prototyped in
 * general.h that have not yet been rewritten in
 * assembly. They are provided as a means to have a complete
 * api, while being relatively unoptimized.
 */

void x4_SlideBuffer_FromRight(void *dest, void *src)
{
	for (int i = 0; i < 320 / X4_slide_horizontal_step_size; i++)
	{
		memmove(dest, dest + 120 * X4_slide_horizontal_step_size, 38400 - 120 * X4_slide_horizontal_step_size);
		memcpy(dest + 38400 - 120 * X4_slide_horizontal_step_size, src + 120 * X4_slide_horizontal_step_size * i, 120 * X4_slide_horizontal_step_size);
	}
}

void x4_SlideBuffer_FromLeft(void *dest, void *src)
{
	for (int24_t i = 0; i < X4_SCREEN_WIDTH / X4_slide_horizontal_step_size; i++)
	{
		memmove(dest + X4_HALF_SCREEN_HEIGHT * X4_slide_horizontal_step_size,
				dest, X4_SCREEN_SIZE - X4_HALF_SCREEN_HEIGHT * X4_slide_horizontal_step_size);
		memcpy(dest + X4_HALF_SCREEN_HEIGHT * X4_slide_horizontal_step_size * i,
			   src + X4_SCREEN_SIZE - X4_HALF_SCREEN_HEIGHT * X4_slide_horizontal_step_size,
			   X4_HALF_SCREEN_HEIGHT * X4_slide_horizontal_step_size);
	}
}

void x4_SlideBuffer_FromTop(void *dest, void *src)
{
	for (uint24_t j = 0; j < X4_HALF_SCREEN_HEIGHT / X4_slide_vertical_step_size; j++)
	{
		uint24_t half_height_i = X4_HALF_SCREEN_HEIGHT * i;
		for (uint24_t i = 0; i < X4_SCREEN_WIDTH; i++)
		{
			memmove(dest + X4_HALF_SCREEN_HEIGHT * i + X4_slide_vertical_step_size,
					dest + X4_HALF_SCREEN_HEIGHT * i, X4_HALF_SCREEN_HEIGHT - X4_slide_vertical_step_size);
			memcpy(dest + X4_HALF_SCREEN_HEIGHT * i,
				   src + X4_HALF_SCREEN_HEIGHT * i + X4_HALF_SCREEN_HEIGHT - X4_slide_vertical_step_size * (j + 1),
				   X4_slide_vertical_step_size);
		}
	}
}

void x4_SlideBuffer_FromBottom(void *dest, void *src)
{
	for (int24_t j = 0; j < 120 / X4_slide_vertical_step_size; j++)
	{
		for (int24_t i = 0; i < 320; i++)
		{
			memmove(dest + 120 * i, dest + 120 * i + X4_slide_vertical_step_size, 120 - X4_slide_vertical_step_size);
			memcpy(dest + 120 * i + 120 - X4_slide_vertical_step_size * j, src + 120 * i, X4_slide_vertical_step_size);
		}
	}
}
//////////////
void x4_SlideBuffer_FromRight_sync(void *dest, void *scratch, void *src)
{
	x4_BlitBuffer(scratch, dest);
	for (int i = 0; i < 320 / X4_slide_horizontal_step_size; i++)
	{
		memmove(scratch, scratch + 120 * X4_slide_horizontal_step_size, 38400 - 120 * X4_slide_horizontal_step_size);
		memcpy(scratch + 38400 - 120 * X4_slide_horizontal_step_size, src + 120 * X4_slide_horizontal_step_size * i, 120 * X4_slide_horizontal_step_size);
		x4_BlitBuffer(dest, scratch);
	}
}

void x4_SlideBuffer_FromLeft_sync(void *dest, void *scratch, void *src)
{
	x4_BlitBuffer(scratch, dest);

	for (int24_t i = 0; i < 320 / X4_slide_horizontal_step_size; i++)
	{
		memmove(scratch + 120 * X4_slide_horizontal_step_size, scratch, 38400 - 120 * X4_slide_horizontal_step_size);
		memcpy(scratch + 120 * X4_slide_horizontal_step_size * i, src + 38400 - 120 * X4_slide_horizontal_step_size, 120 * X4_slide_horizontal_step_size);
		x4_BlitBuffer(dest, scratch);
	}
}

void x4_SlideBuffer_FromTop_sync(void *dest, void *scratch, void *src)
{
	x4_BlitBuffer(scratch, dest);

	for (int24_t j = 0; j < 120 / X4_slide_vertical_step_size; j++)
	{
		for (int24_t i = 0; i < 320; i++)
		{
			memmove(scratch + 120 * i + X4_slide_vertical_step_size, scratch + 120 * i, 120 - X4_slide_vertical_step_size);
			memcpy(scratch + 120 * i, src + 120 * i + 120 - X4_slide_vertical_step_size * j, X4_slide_vertical_step_size);
		}
		x4_BlitBuffer(dest, scratch);
	}
}