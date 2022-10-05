#ifndef config_h
#define config_h

/*
 * Config.h:
 * Contains routines related to the user provided
 * configuration file, CEDIT2RC.
 * This configuration file is named CEDIT2RC to
 * avoid conflicts with the previous CEDITRC file.
 * This program will, optionally, allow the user to
 * automatically update the CEDITRC file to CEDIT2RC
 * if CEDITRC is present.
 */

/*
 * Parse the CEDIT2RC file and load configuration from
 * there into the editor state.
 *
 * TODO
 */
void load_rc(struct estate *state);

/*
 * Fills state with the default values.
 */
void initialize_default_state(struct estate *state);

/*
 * Performs basic engine setup.
 */
void initialize_x4(void);

/*
 * Releases resources held by the engine.
 */
void release_x4(void);

#endif