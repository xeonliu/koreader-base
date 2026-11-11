-- POSIX declarations for the PSP (pspdev newlib): 64-bit time_t, newlib's constants, libkopsp's statvfs.
local ffi = require("ffi")

ffi.cdef[[
typedef unsigned int size_t;
typedef long int off_t;
struct timeval {
  int64_t tv_sec;
  long int tv_usec;
};
struct timespec {
  int64_t tv_sec;
  long int tv_nsec;
};
int clock_gettime(int, struct timespec *);
struct statvfs {
  long unsigned int f_bsize;
  long unsigned int f_frsize;
  uint64_t f_blocks;
  uint64_t f_bfree;
  uint64_t f_bavail;
  uint64_t f_files;
  uint64_t f_ffree;
  uint64_t f_favail;
  long unsigned int f_fsid;
  long unsigned int f_flag;
  long unsigned int f_namemax;
};
int pipe(int *) __attribute__((__nothrow__, __leaf__));
int fork(void) __attribute__((nothrow));
int dup(int) __attribute__((__nothrow__, __leaf__));
int dup2(int, int) __attribute__((__nothrow__, __leaf__));
static const int O_RDWR = 2;
static const int O_RDONLY = 0;
static const int O_NONBLOCK = 16384;
int open(const char *, int, ...);
int close(int);
int fcntl(int, int, ...);
int execl(const char *, const char *, ...) __attribute__((__nothrow__, __leaf__));
int execlp(const char *, const char *, ...) __attribute__((__nothrow__, __leaf__));
int execv(const char *, char *const *) __attribute__((__nothrow__, __leaf__));
int execvp(const char *, char *const *) __attribute__((__nothrow__, __leaf__));
int write(int, const void *, size_t);
int read(int, void *, size_t);
int kill(int, int) __attribute__((__nothrow__, __leaf__));
int waitpid(int, int *, int);
int getpid(void) __attribute__((__nothrow__, __leaf__));
int setpgid(int, int) __attribute__((__nothrow__, __leaf__));
struct pollfd {
  int fd;
  short int events;
  short int revents;
};
static const int POLLIN = 1;
static const int POLLOUT = 4;
static const int POLLERR = 8;
static const int POLLHUP = 16;
int poll(struct pollfd *, long unsigned int, int);
static const int PROT_READ = 1;
static const int PROT_WRITE = 2;
static const int MAP_SHARED = 1;
static const int MAP_FAILED = 4294967295;
static const int PATH_MAX = 1024;
int memcmp(const void *, const void *, size_t) __attribute__((pure, leaf, nothrow));
void *mmap(void *, size_t, int, int, int, long int) __attribute__((__nothrow__, __leaf__));
int munmap(void *, size_t) __attribute__((__nothrow__, __leaf__));
int ioctl(int, long unsigned int, ...) __attribute__((__nothrow__, __leaf__));
void Sleep(int ms);
unsigned int sleep(unsigned int);
int usleep(unsigned int);
int statvfs(const char *restrict, struct statvfs *restrict) __attribute__((__nothrow__, __leaf__));
int gettimeofday(struct timeval *restrict, struct timezone *restrict) __attribute__((__nothrow__, __leaf__));
char *realpath(const char *restrict, char *restrict) __attribute__((__nothrow__, __leaf__));
char *basename(char *);
char *dirname(char *) __attribute__((__nothrow__, __leaf__));
void *malloc(size_t) __attribute__((malloc, leaf, nothrow));
void free(void *) __attribute__((leaf, nothrow));
char *strdup(const char *) __attribute__((malloc, leaf, nothrow));
char *strndup(const char *, size_t) __attribute__((malloc, leaf, nothrow));
struct _IO_FILE *fopen(const char *restrict, const char *restrict);
int fclose(struct _IO_FILE *);
int printf(const char *, ...);
int sprintf(char *, const char *, ...) __attribute__((nothrow));
int fprintf(struct _IO_FILE *restrict, const char *restrict, ...);
int fputc(int, struct _IO_FILE *);
static const int FIONREAD = 21531;
int fileno(struct _IO_FILE *) __attribute__((__nothrow__, __leaf__));
char *strerror(int) __attribute__((__nothrow__, __leaf__));
]]
