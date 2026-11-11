/* Force-included (C++) for libzmq and sdcv on the PSP: newlib hides some POSIX declarations they use.
 * There are no real signals or thread names on the PSP, so these become no-ops. */
#ifndef KO_PSP_ZMQ_COMPAT_H
#define KO_PSP_ZMQ_COMPAT_H
#include <signal.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
extern "C" {
int mkstemp(char *);
int usleep(unsigned);
FILE *popen(const char *, const char *);
int pclose(FILE *);
FILE *fdopen(int, const char *);
int fileno(FILE *);
}
static inline int ko_isascii(int c) { return (unsigned)c < 128u; }
#define isascii ko_isascii
#ifndef SIG_BLOCK
#define SIG_BLOCK 0
#define SIG_UNBLOCK 1
#define SIG_SETMASK 2
#endif
#define sigfillset(s) ((void)(s), 0)
#define sigemptyset(s) ((void)(s), 0)
#define sigaddset(s, n) ((void)(s), (void)(n), 0)
#define pthread_sigmask(h, s, o) ((void)(h), (void)(s), (void)(o), 0)
#endif
