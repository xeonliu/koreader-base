/* Force-included when building libk2pdfopt for the PSP: newlib already declares strlwr()/strupr() (returning char *),
 * and willuslib defines its own void versions. Include <string.h> first, then rename willuslib's. */
#ifndef KO_PSP_K2PDFOPT_COMPAT_H
#define KO_PSP_K2PDFOPT_COMPAT_H
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#define strlwr willus_strlwr
#define strupr willus_strupr
#endif
