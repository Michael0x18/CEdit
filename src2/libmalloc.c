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

#include "libmalloc.h"
void* malloc_noheap(size_t size){
	static int24_t currentsize;
	static int24_t maxsize;
	static void* mem = 0;
	if(mem==0){
		maxsize=os_MemChk(&mem);
		currentsize=0;
	}
	if(currentsize >= maxsize){
		return NULL;
	}
	void* ret = (char*)mem + currentsize;
	currentsize+=size;
	return ret;

}

void* malloc_noheap_safe(size_t size,char* handle){
    //Create file - goes into RAM
    ti_var_t var = ti_Open(handle,"w");
    ti_Resize(size,var);
    void* data = ti_GetDataPtr(var);
    ti_Close(var);
    return data;
}
