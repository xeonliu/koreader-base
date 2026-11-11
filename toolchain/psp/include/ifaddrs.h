/* Shim for PSP/newlib: <ifaddrs.h> (getifaddrs() is an ENOSYS stub in the launcher). */
#ifndef KO_PSP_IFADDRS_H
#define KO_PSP_IFADDRS_H
#include <sys/socket.h>
#include <net/if.h>
#ifdef __cplusplus
extern "C" {
#endif
struct ifaddrs { struct ifaddrs *ifa_next; char *ifa_name; unsigned ifa_flags; struct sockaddr *ifa_addr; struct sockaddr *ifa_netmask; struct sockaddr *ifa_broadaddr; void *ifa_data; };
int getifaddrs(struct ifaddrs **);
void freeifaddrs(struct ifaddrs *);
#ifdef __cplusplus
}
#endif
#endif
