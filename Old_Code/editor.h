#ifndef editor_h
#define editor_h

#include <intce.h>

#include "cedit.h"
#include "ngetchx.h"
#include "keys.h"
#include "scroll.h"

void redraw_editor(struct estate *state);
void insert_char(struct estate *state, char c);
void backspace(struct estate *state);
void delete (struct estate *state);
bool is_control(unsigned char k);
void editor_mainloop(struct estate *state);
void move_left(struct estate *state);
void move_right(struct estate *state);
void handle_control(struct estate *state, unsigned char k);

#endif