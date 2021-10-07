/*
 * clipboard.c
 *
 *  Created on: Jul 26, 2021
 *      Author: michael
 */

#include "clipboard.h"
#include "state.h"

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
    #ifdef USE_PERSISTENT_CLIPBOARD
        state->clipboard_file=ti_Open("CLIPDATA","w");
        ti_Write(state->text+start,len,1,state->clipboard_file);
        ti_Close(state->clipboard_file);
    #else
	memcpy(state->clipboard_data, state->text + start, len);
    #endif
	state->clipboard_size = len;
}

void cb_cut(struct estate *state) {
	cb_copy(state);
	bs(state);
}

void cb_paste(struct estate *state) {
    #ifdef USE_PERSISTENT_CLIPBOARD
    state->clipboard_file=ti_Open("CLIPDATA","r");
    if(state->clipboard_file==0){
        return;
    }
    char c;
	while ((c = ti_GetC(state->clipboard_file)) != EOF) {
		insert_char(state, c);
	}
    ti_Close(state->clipboard_file);
    #else
	for (int i = 0; i < state->clipboard_size; i++) {
		insert_char(state, state->clipboard_data[i]);
	}
    #endif
}

// size_t os_MemChk(void **free) --> more ram needed?