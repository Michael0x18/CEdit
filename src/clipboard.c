/*
 * clipboard.c
 *
 *  Created on: Jul 26, 2021
 *      Author: michael
 */

#include "clipboard.h"

void cb_copy(struct estate *state){
	int24_t start;
	int24_t len;
	if(state->c2 + 1 < state->selection_anchor){
		start=state->c2+1;
		len=state->selection_anchor-state->c2-1;
		gfx_SetDrawScreen();
		fontlib_DrawString()
		//left selection
	}else if(state->c1 - 1 > state->selection_anchor){
		start=state->selection_anchor;
		len=state->selection_anchor-state->c1+1;
		//right selection
	}else{
		return;//no selection
	}
	memcpy(state->clipboard_data,state->text+start,len);
	state->clipboard_size=len;
}

void cb_cut(struct estate *state){
	cb_copy(state);
	bs(state);
}

void cb_paste(struct estate *state){
	for(int i = 0; i < state->clipboard_size; i++){
		insert_char(state,state->clipboard_data[i]);
	}
}

