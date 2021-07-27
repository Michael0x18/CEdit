/*
 * clipboard.c
 *
 *  Created on: Jul 26, 2021
 *      Author: michael
 */

#include "clipboard.h"

void cb_copy(struct estate *state) {
	int24_t start;
	int24_t len;
	//gfx_SetDrawScreen();
	//fontlib_DrawInt(state->selection_anchor, 5);
	//ngetchx();
	if (state->c2 < state->selection_anchor) {
		start = state->c2+1;
		len = state->selection_anchor - state->c2;
		//left selection
	} else if (state->c1 > state->selection_anchor) {
		start = state->selection_anchor;
		len = state->c1 - state->selection_anchor;
		//right selection
	} else {
		return; //no selection
	}
	memcpy(state->clipboard_data, state->text + start, len);
	state->clipboard_size = len;
}

void cb_cut(struct estate *state) {
	cb_copy(state);
	bs(state);
}

void cb_paste(struct estate *state) {
	for (int i = 0; i < state->clipboard_size; i++) {
		insert_char(state, state->clipboard_data[i]);
	}
}

