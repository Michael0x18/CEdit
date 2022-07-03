#ifndef ngetchx_h
#define ngetchx_h

#include <stdio.h>
#include <stdlib.h>
#include <tice.h>
#include <intce.h>
#include <keypadc.h>
#include <graphx.h>
#include <string.h>

#include "cedit.h"

extern char key_list[8][54];

uint8_t getkey(struct estate *state);

/*
 * Processes leading and trailing edge detectors for modifier keys
 * State machine is as follows:
 * Leading edge means go from not pressed to pressed, if applicable
 * Trailing edge means to from held to not pressed, if applicable
 *
 */
void process_modifiers(struct estate *state);

uint8_t generate_mod_mask(struct estate *state);

char ngetchx(struct estate *state);

#endif