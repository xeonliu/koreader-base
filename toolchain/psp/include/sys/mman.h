/* Shim for PSP/newlib: no mmap. mmap() always fails, so callers must fall back to read(). */
#ifndef KO_PSP_MMAN_H
#define KO_PSP_MMAN_H
#include <stddef.h>
#include <sys/types.h>
#include <errno.h>
#define PROT_NONE 0
#define PROT_READ 1
#define PROT_WRITE 2
#define PROT_EXEC 4
#define MAP_SHARED 1
#define MAP_PRIVATE 2
#define MAP_FIXED 0x10
#define MAP_ANONYMOUS 0x20
#define MAP_ANON MAP_ANONYMOUS
#define MAP_FAILED ((void *)-1)
#define MS_SYNC 4
static inline void *mmap(void *a, size_t l, int p, int f, int fd, off_t o) { (void)a; (void)l; (void)p; (void)f; (void)fd; (void)o; errno = ENOSYS; return MAP_FAILED; }
static inline int munmap(void *a, size_t l) { (void)a; (void)l; return 0; }
static inline int msync(void *a, size_t l, int f) { (void)a; (void)l; (void)f; return 0; }
#endif
