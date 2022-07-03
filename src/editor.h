#ifndef editor_h
#define editor_h

#include <intce.h>

#include "cedit.h"
#include "ngetchx.h"
#include "keys.h"

void redraw_editor(struct estate *state);
void insert_char(struct estate *state, char c);
bool is_control(char k);

#endif