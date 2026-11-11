/* Shim for PSP/newlib: add the POSIX limits newlib omits. */
#ifndef KO_PSP_LIMITS_H
#define KO_PSP_LIMITS_H
#include_next <limits.h>
#ifndef _POSIX_HOST_NAME_MAX
#define _POSIX_HOST_NAME_MAX 255
#endif
#ifndef HOST_NAME_MAX
#define HOST_NAME_MAX 255
#endif
#ifndef SSIZE_MAX
#define SSIZE_MAX 2147483647
#endif
#endif
