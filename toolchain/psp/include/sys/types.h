/* Shim for PSP/newlib: newlib's BSD-visible <sys/types.h> defines `quad` and `physadr` as macros, which breaks code
 * using them as identifiers (e.g. MuPDF's `fz_quad quad;`). Include the real header, then drop the macros. */
#ifndef KO_PSP_SYS_TYPES_H
#define KO_PSP_SYS_TYPES_H
#include_next <sys/types.h>
#undef quad
#undef physadr
#endif
