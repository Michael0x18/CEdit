#ifndef state_h
#define state_h

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

#ifdef BOS_BUILD
#define BUFFER_SIZE 65536
#else
#define BUFFER_SIZE 16384
#endif
#define LINE_BUFFER_SIZE 10000;

//   Example
//   ABCDE------------FGHIJK
//        |c1        |c2

struct estate
{
#ifdef BOS_BUILD
    //The text buffer (BOS VERSION)
    char text[65536];
#else
    //The text buffer (TIOS VERSION)
    char text[16384];
#endif
    //Array of the lengths of the lines
    char line_lengths[10000];
    //Points to the spot where the cursor is at, on the left side
    int24_t c1;
    //Points to the spot where the cursor is at, on the right side
    int24_t c2;
    //The line the cursor is ON
    int24_t lc1;
    //The line the cursor is just before (right side)
    int24_t lc2;
    //The x position of the cursor, on the screen
    int24_t cursor_x;
    //The y position of the cursor, on the screen
    int24_t cursor_y;
};

#endif