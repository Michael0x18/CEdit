/*
 * tigcclib.c
 *
 *  Created on: Jul 25, 2021
 *      Author: michael
 */

#include "tigcclib.h"

/*
 * Bindings for no modifier keys held
 */
short kmain[] = { KEY_NO_EXIST, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_UP,
		KEY_NO_EXIST, KEY_NO_EXIST, KEY_NO_EXIST, KEY_NO_EXIST, '\n', '+', '-',
		'*', '/', '^', KEY_TAB, KEY_NO_EXIST, '-', '3', '6', '9', ')',
		KEY_UNBOUND, KEY_UNBOUND, KEY_NO_EXIST, '.', '2', '5', '8', '(',
		KEY_UNBOUND, KEY_UNBOUND, KEY_SAVE, '0', '1', '4', '7', ',',
		KEY_UNBOUND, KEY_UNBOUND, KEY_NO_EXIST, KEY_RESERVED, KEY_SAVE, '\\',
		'|', '=', KEY_UNBOUND, KEY_UNBOUND, KEY_NO_EXIST, KEY_F5, KEY_F4,
		KEY_F3, KEY_F2, KEY_F1, KEY_NO_EXIST, KEY_NO_EXIST, KEY_BS };
/*
 * Bindings for holding the 2nd key
 */
short ksec[] = { KEY_NO_EXIST, KEY_WDOWN, KEY_WLEFT, KEY_WRIGHT, KEY_WUP,
		KEY_NO_EXIST, KEY_NO_EXIST, KEY_NO_EXIST, KEY_NO_EXIST, KEY_UNBOUND,
		'\'', ']', '[', KEY_UNBOUND, KEY_UNBOUND, KEY_CLEAR, KEY_NO_EXIST,
		KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, '}', KEY_UNBOUND,
		KEY_UNBOUND, KEY_NO_EXIST, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND,
		KEY_UNBOUND, '{', KEY_UNBOUND, KEY_UNBOUND, KEY_SAVE_AS, KEY_UNBOUND,
		KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND,
		KEY_UNBOUND, KEY_NO_EXIST, KEY_RESERVED, KEY_SAVE_AS, KEY_UNBOUND,
		KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_NO_EXIST,
		KEY_F10, KEY_F9, KEY_F8, KEY_F7, KEY_F6, KEY_NO_EXIST, KEY_NO_EXIST,
		KEY_DEL };
/*
 * Bindings for holding the alpha key
 */
short kalpha[] = { KEY_NO_EXIST, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_UP,
		KEY_NO_EXIST, KEY_NO_EXIST, KEY_NO_EXIST, KEY_NO_EXIST, '\n', '"', 'w',
		'r', 'm', 'h', KEY_TAB, KEY_NO_EXIST, '?', '_', 'v', 'q', 'l', 'g',
		KEY_UNBOUND, KEY_NO_EXIST, ':', 'z', 'u', 'p', 'k', 'f', 'c',
		KEY_NO_EXIST, ' ', 'y', 't', 'o', 'j', 'e', 'b', KEY_NO_EXIST,
		KEY_RESERVED, 'x', 's', 'n', 'i', 'd', 'a', KEY_NO_EXIST, KEY_F5,
		KEY_F4, KEY_F3, KEY_F2, KEY_F1, KEY_NO_EXIST, KEY_NO_EXIST, KEY_BS };
/*
 * Bindings for holding the shift (Xt0n) key
 */
short kshift[] = { KEY_NO_EXIST, KEY_SDOWN, KEY_SLEFT, KEY_SRIGHT, KEY_SUP,
		KEY_NO_EXIST, KEY_NO_EXIST, KEY_NO_EXIST, KEY_NO_EXIST, '\n', '\'', 'W',
		'R', 'M', 'H', KEY_UNBOUND, KEY_NO_EXIST, '<', '>', 'V', 'Q', 'L', 'G',
		KEY_UNBOUND, KEY_NO_EXIST, ';', 'Z', 'U', 'P', 'K', 'F', 'C', KEY_SAVE,
		' ', 'Y', 'T', 'O', 'J', 'E', 'B', KEY_NO_EXIST, KEY_RESERVED, 'X', 'S',
		'N', 'I', 'D', 'A', KEY_NO_EXIST, KEY_F5, KEY_F4, KEY_F3, KEY_F2,
		KEY_F1, KEY_NO_EXIST, KEY_NO_EXIST, KEY_BREAK };
/*
 * Bindings for holding the meta (Mode) key
 */
short kmeta[] = { KEY_NO_EXIST, KEY_LDOWN, KEY_LLEFT, KEY_LRIGHT, KEY_LUP,
		KEY_NO_EXIST, KEY_NO_EXIST, KEY_NO_EXIST, KEY_NO_EXIST, KEY_UNBOUND,
		'!', '@', '#', '$', '%', '&', KEY_NO_EXIST, KEY_UNBOUND, KEY_UNBOUND,
		KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND,
		KEY_NO_EXIST, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND,
		KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_OPEN, KEY_UNBOUND,
		KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND,
		KEY_UNBOUND, KEY_UNBOUND, KEY_RESERVED, KEY_OPEN, KEY_UNBOUND,
		KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND,
		KEY_REDO, KEY_UNDO, KEY_PASTE, KEY_COPY, KEY_CUT, KEY_UNBOUND,
		KEY_UNBOUND, KEY_QUIT };
/*
 * Bindings for holding both 2nd and shift
 */
short ksecshift[] = { KEY_NO_EXIST, KEY_WSDOWN, KEY_WSLEFT, KEY_WSRIGHT,
		KEY_WSUP, KEY_NO_EXIST, KEY_NO_EXIST, KEY_NO_EXIST, KEY_NO_EXIST,
		KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND,
		KEY_UNBOUND, KEY_UNBOUND, KEY_NO_EXIST, KEY_UNBOUND, KEY_UNBOUND,
		KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND,
		KEY_NO_EXIST, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND,
		KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_SAVE, KEY_UNBOUND,
		KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND,
		KEY_UNBOUND, KEY_UNBOUND, KEY_RESERVED, KEY_SAVE, KEY_UNBOUND,
		KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND,
		KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND,
		KEY_UNBOUND, KEY_UNBOUND, KEY_QUIT };
/*
 * Bindings for holding both meta and shift
 */
short kmetashift[] = { KEY_NO_EXIST, KEY_LSDOWN, KEY_LSLEFT, KEY_LSRIGHT,
		KEY_LSUP, KEY_NO_EXIST, KEY_NO_EXIST, KEY_NO_EXIST, KEY_NO_EXIST,
		KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND,
		KEY_UNBOUND, KEY_UNBOUND, KEY_NO_EXIST, KEY_UNBOUND, KEY_UNBOUND,
		KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND,
		KEY_NO_EXIST, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND,
		KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_SAVE, KEY_UNBOUND,
		KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND,
		KEY_UNBOUND, KEY_UNBOUND, KEY_RESERVED, KEY_SAVE, KEY_UNBOUND,
		KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND,
		KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND,
		KEY_UNBOUND, KEY_UNBOUND, KEY_QUIT };


uint8_t ngetchx_backend(void) {
	static uint8_t last_key;
	uint8_t only_key = 0;
	kb_Scan();
	for (uint8_t key = 1, group = 7; group; --group) {
		for (uint8_t mask = 1; mask; mask <<= 1, ++key) {
			if (kb_Data[group] & mask) {
				if (key == 40 || key == 48 || key == 54 || key == 55)
					continue;
				if (only_key) {
					last_key = 0;
					return 0;
				} else {
					only_key = key;
				}
			}
		}
	}
	if (only_key == last_key) {
		return 0;
	}
	last_key = only_key;
	return only_key;
}

short ngetchx(void) {
	uint8_t k = 0;
	while (!(k = ngetchx_backend())) {
		continue;
	}
	if (kb_IsDown(kb_Key2nd) && kb_IsDown(kb_KeyGraphVar)) {
		return ksecshift[k];
	} else if (kb_IsDown(kb_KeyMode) && kb_IsDown(kb_KeyAlpha)) {
		return kmetashift[k];
	} else if (kb_IsDown(kb_KeyMode)) { //mode=meta
		return kmeta[k];
	} else if (kb_IsDown(kb_Key2nd)) {
		return ksec[k];
	} else if (kb_IsDown(kb_KeyGraphVar)) {
		return kshift[k];
	} else if (kb_IsDown(kb_KeyAlpha)) {
		return kalpha[k];
	} else {
		return kmain[k];
	}
}

short ngetchx_xy(struct estate *state,int cx, int cy) {
	uint8_t k = 0;
	int frame = 0;
	bool on = true;
	gfx_SetDrawScreen();
	gfx_SetColor(state->text_color);
	gfx_VertLine_NoClip(cx,cy,12);
	while (!(k = ngetchx_backend())) {
		frame++;
		if(frame>400){
			frame=0;
			if(on){
				gfx_SetColor(state->background_color);
				gfx_VertLine_NoClip(cx,cy,12);
				on=false;
			}else{
				gfx_SetColor(state->text_color);
				gfx_VertLine_NoClip(cx,cy,12);
				on=true;
			}
		}
	}
	gfx_SetDrawBuffer();
	if (kb_IsDown(kb_Key2nd) && kb_IsDown(kb_KeyGraphVar)) {
		return ksecshift[k];
	} else if (kb_IsDown(kb_KeyMode) && kb_IsDown(kb_KeyAlpha)) {
		return kmetashift[k];
	} else if (kb_IsDown(kb_KeyMode)) { //mode=meta
		return kmeta[k];
	} else if (kb_IsDown(kb_Key2nd)) {
		return ksec[k];
	} else if (kb_IsDown(kb_KeyGraphVar)) {
		return kshift[k];
	} else if (kb_IsDown(kb_KeyAlpha)) {
		return kalpha[k];
	} else {
		return kmain[k];
	}
}

