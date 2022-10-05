#ifndef scroll_h
#define scroll_h
#include "cedit.h"

/*
 * scroll.h contains routines needed for screen scrolling,
 * computation of scrolling status, and other miscellaneous
 * things relating to both of the above.
 */

/**
 * Checks to see if a scroll is needed (cursor has passed the bounds of the screen)
 * If so, scrolls and returns 1. Otherwise returns 0
 */
bool check_scroll_and_execute();

/**
 * Scrolls up one line
 */
void scroll_up(void);

#endif