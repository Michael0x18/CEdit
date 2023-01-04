#ifndef macros_h
#define macros_h

/**
 * Packs a 4 bit integer into 8 bits, repeating
 * it once. x is assumed to have empty upper 4
 * bits
 */
#define X4_PACK_4_TO_8(x) ((x << 4) & x)

#endif /*macros_h*/