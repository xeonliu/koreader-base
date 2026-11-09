/* Shim for PSP/newlib: <sys/socket.h> declarations (the functions are ENOSYS stubs in the launcher). */
#ifndef KO_PSP_SYS_SOCKET_H
#define KO_PSP_SYS_SOCKET_H
#include <stddef.h>
#include <sys/types.h>
#ifdef __cplusplus
extern "C" {
#endif
typedef unsigned socklen_t;
typedef unsigned short sa_family_t;
struct sockaddr { sa_family_t sa_family; char sa_data[14]; };
#ifndef AF_INET
#define AF_INET 2
#define AF_UNIX 1
#define AF_INET6 10
#endif
#define PF_INET AF_INET
#define SOCK_STREAM 1
#define SOCK_DGRAM 2
#define SOL_SOCKET 0xffff
#define SO_REUSEADDR 4
#define SO_RCVTIMEO 0x1006
#define SO_SNDTIMEO 0x1005
#define SHUT_RDWR 2
int socket(int, int, int);
int connect(int, const struct sockaddr *, socklen_t);
int bind(int, const struct sockaddr *, socklen_t);
int listen(int, int);
int accept(int, struct sockaddr *, socklen_t *);
ssize_t send(int, const void *, size_t, int);
ssize_t recv(int, void *, size_t, int);
int setsockopt(int, int, int, const void *, socklen_t);
int getsockopt(int, int, int, void *, socklen_t *);
int shutdown(int, int);
#ifdef __cplusplus
}
#endif
#endif
