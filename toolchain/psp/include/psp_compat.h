/* Force-included (C++ only) on the PSP target: smooths over missing POSIX bits that Linux-assuming code expects. */
#ifndef KO_PSP_COMPAT_H
#define KO_PSP_COMPAT_H
#include <signal.h>
#ifndef SA_RESETHAND
#define SA_RESETHAND 0
#endif
#ifndef SA_SIGINFO
#define SA_SIGINFO 0
#endif
#ifndef NSIG
#define NSIG 32
#endif
#ifndef SIGBUS
#define SIGBUS SIGSEGV
#endif
#ifndef SIGPIPE
#define SIGPIPE 13
#endif
#define sa_sigaction sa_handler
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#ifdef __cplusplus
#ifndef SIG_BLOCK
#define SIG_BLOCK 0
#define SIG_UNBLOCK 1
#define SIG_SETMASK 2
#endif
#endif
#endif
