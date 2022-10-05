#ifndef config_h
#define config_h

#include "cedit.h"

// Contains initialization routines

/**
 * Initializes the passed estate variable
 * Sets up the defaults, then parses CEDITRC
 */
bool cedit_init(struct estate *state);

/**
 * Initializes cedit's default options
 */
bool cedit_defaults(struct estate *state);

/**
 * Parses cedit's config file and sets options
 */
bool parse_rc(struct estate *state);

#endif