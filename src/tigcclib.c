#ifndef tigcclib_c
#define tigcclib_c

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>
#include <fileioc.h>
#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <graphx.h>
#include <keypadc.h>
#include <fontlibc.h>

#include "tigcclib.h"

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

#endif
