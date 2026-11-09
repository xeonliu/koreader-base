/* Shim for PSP/newlib: <poll.h>. poll() itself is a stub provided by the launcher. */
#ifndef KO_PSP_POLL_H
#define KO_PSP_POLL_H
#ifdef __cplusplus
extern "C" {
#endif
struct pollfd { int fd; short events; short revents; };
typedef unsigned long nfds_t;
#define POLLIN 0x001
#define POLLPRI 0x002
#define POLLOUT 0x004
#define POLLERR 0x008
#define POLLHUP 0x010
#define POLLNVAL 0x020
#define POLLRDNORM 0x040
#define POLLWRNORM 0x100
int poll(struct pollfd *, nfds_t, int);
#ifdef __cplusplus
}
#endif
#endif
