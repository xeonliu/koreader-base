/* Shim for PSP/newlib: <sys/resource.h> additions (getrusage is provided by the launcher). */
#ifndef KO_PSP_SYS_RESOURCE_H
#define KO_PSP_SYS_RESOURCE_H
#include_next <sys/resource.h>
#ifndef RLIMIT_CORE
typedef unsigned long long rlim_t;
struct rlimit { rlim_t rlim_cur; rlim_t rlim_max; };
#define RLIM_INFINITY ((rlim_t)-1)
#define RLIMIT_CPU 0
#define RLIMIT_FSIZE 1
#define RLIMIT_DATA 2
#define RLIMIT_STACK 3
#define RLIMIT_CORE 4
#define RLIMIT_NOFILE 7
#ifdef __cplusplus
extern "C" {
#endif
int getrlimit(int, struct rlimit *);
int setrlimit(int, const struct rlimit *);
#ifdef __cplusplus
}
#endif
#endif
#ifndef PRIO_PROCESS
#define PRIO_PROCESS 0
#define PRIO_PGRP 1
#define PRIO_USER 2
#endif
#endif
