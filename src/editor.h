#ifndef editor_h
#define editor_h

#include <intce.h>

#include "cedit.h"
#include "ngetchx.h"
#include "keys.h"

void redraw_editor(struct estate *state);
void insert_char(struct estate *state, char c);
void backspace(struct estate *state);
void delete (struct estate *state);
bool is_control(unsigned char k);
void editor_mainloop(struct estate *state);

#endif