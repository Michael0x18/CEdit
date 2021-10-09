#ifndef config_h
#define config_h
//FILE config.h
//Contains configuration routines
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

//Sets up the default editor configuration
void load_default_config(struct estate *state);

//Loads the editor configuration from ceditrc
void load_config(struct estate *state);

#endif