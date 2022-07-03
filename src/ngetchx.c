#include "ngetchx.h"

static const int8_t MOD_CLEAR = 0;
static const int8_t MOD_PRESS = 1;
static const int8_t MOD_HELD = 2;

void process_modifiers(struct estate *state)
{
	static kb_lkey_t modcodes[4] = {kb_Key2nd,
									kb_KeyAlpha,
									kb_KeyMode,
									kb_KeyGraphVar};
	for (int i = 0; i < 4; i++)
	{
		if (kb_IsDown(modcodes[i]))
		{
			if (state->modifiers[i] == MOD_CLEAR)
			{
				state->modifiers[i] = MOD_PRESS;
			}
		}
		else
		{
			if (state->modifiers[i] == MOD_HELD)
			{
				state->modifiers[i] = MOD_CLEAR;
			}
		}
	}
}

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
	kb_Scan();
	process_modifiers(state);

	static uint8_t last_key;
	uint8_t only_key = 0;
	kb_Scan();
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
	last_key = only_key;
	return only_key;
}

char ngetchx(struct estate *state)
{
	return key_list[generate_mod_mask(state)][getkey(state)];
}