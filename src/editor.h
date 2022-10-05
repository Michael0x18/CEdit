#ifndef editor_h
#define editor_h

#include "cedit.h"
#include "ngetchx.h"
#include "gfx.h"

// Contains common editor routines

bool editor_handle_keypress(struct estate *state, unsigned char k);

bool editor_handle_keypress_fast(struct estate *state, unsigned char k);

void handle_control(struct estate *state, unsigned char k);

bool is_control(unsigned char k);

/**
 * Mainloop.
 * Cycles through multiple phases:
 * 1) Redraw phase - redraws editor in full, double buffered
 * 2) Polling phase - partial redraw for modifier keys.
 * 2A) Burst mode phase - no redraw. Nothing but buffering keystrokes
 * 2B) Burst flush phase - flush keystroke buffer
 * 3) Handle phase - handle special keystrokes
 */
void editor_mainloop(struct estate *state);

#endif