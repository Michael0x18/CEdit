#include "ngetchx.h"

static const int8_t MOD_CLEAR = 0;
static const int8_t MOD_PRESS_NEW = 1;
static const int8_t MOD_PRESS = 2;
static const int8_t MOD_HELD = 3;

void draw_mod_status(struct estate *state)
{
	char tmp[5] = "0000";
	for (int8_t i = 0; i < 4; ++i)
	{
		tmp[i] = state->modifiers[i] + '1';
	}
	void *tmp_buf = x4_GetDrawLocation();
	x4_SetDrawLocation(x4_GetScreenLocation());
	x4_PutStr(state->font_buffer_statusbar, 230, 0, tmp);
	x4_SetDrawLocation(tmp_buf);
}

static kb_lkey_t modcodes[4] = {kb_Key2nd,
								kb_KeyAlpha,
								kb_KeyMode,
								kb_KeyGraphVar};

void process_modifiers(struct estate *state)
{
	static kb_lkey_t modcodes[4] = {kb_Key2nd,
									kb_KeyAlpha,
									kb_KeyMode,
									kb_KeyGraphVar};
	for (int i = 0; i < 4; i++)
	{
		if (kb_IsDown(modcodes[i]))
		{ // If the key is pressed
			if (state->modifiers[i] == MOD_CLEAR)
			{										 // If it was not pressed previously
				state->modifiers[i] = MOD_PRESS_NEW; // Make it a new press
			}
			else if (state->modifiers[i] == MOD_PRESS)
			{									// If it was previously pressed and released
				state->modifiers[i] = MOD_HELD; // Clear it, the user toggled it off
												// Additionally, make it a new clear
												// So it doesn't get toggled on again right after
			}
		}
		else
		{ // Key is not pressed
			if (state->modifiers[i] == MOD_HELD)
			{									 // Did the user hold it and type?
				state->modifiers[i] = MOD_CLEAR; // If so, clear it; it's done
			}
			else if (state->modifiers[i] == MOD_PRESS_NEW)
			{									 // Did the user press it just now, and now it's released?
				state->modifiers[i] = MOD_PRESS; // if so, lock it
			}
		}
	}
}

/*
 * Generates a nibble sized mask corresponding to the set of modifiers currently pressed.
 *
 */
uint8_t generate_mod_mask(struct estate *state)
{
	uint8_t ref = 0;
	for (int i = 0; i < 4; i++)
	{
		if (state->modifiers[i])
		{
			ref |= 1 << i;
		}
	}
	return ref;
}

uint8_t getkey(struct estate *state)
{

	static uint8_t last_key;
	uint8_t only_key = 0;
	for (uint8_t key = 1, group = 7; group; --group)
	{
		for (uint8_t mask = 1; mask; mask <<= 1, ++key)
		{
			if (kb_Data[group] & mask)
			{
				if (key == 40 || key == 48 || key == 54 || key == 55)
					continue;
				if (only_key)
				{
					last_key = 0;
					return 0;
				}
				else
				{
					only_key = key;
				}
			}
		}
	}
	if (only_key == last_key)
	{
		return 0;
	}

	if (only_key)
	{
		for (int i = 0; i < 4; i++)
		{
			if (state->modifiers[i] == MOD_PRESS || state->modifiers[i] == MOD_PRESS_NEW)
			{
				if (kb_IsDown(modcodes[i]))
				{
					state->modifiers[i] = MOD_HELD;
				}
				else
				{
					state->modifiers[i] = MOD_CLEAR;
				}
			}
		}
	}

	last_key = only_key;
	return only_key;
}

unsigned char ngetchx(struct estate *state)
{
	kb_Scan();
	process_modifiers(state);
	draw_mod_status(state);
	return key_list[generate_mod_mask(state)][getkey(state)];
}