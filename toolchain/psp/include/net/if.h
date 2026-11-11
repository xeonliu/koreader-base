/* Shim for PSP/newlib: <net/if.h>. */
#ifndef KO_PSP_NET_IF_H
#define KO_PSP_NET_IF_H
#include <sys/socket.h>
#define IFNAMSIZ 16
#define IF_NAMESIZE 16
#define IFF_UP 1
#define IFF_BROADCAST 2
#define IFF_LOOPBACK 8
#define IFF_RUNNING 0x40
#define IFF_POINTOPOINT 0x10
#define IFF_MULTICAST 0x1000
struct ifreq { char ifr_name[IFNAMSIZ]; union { struct sockaddr ifru_addr; int ifru_flags; int ifru_ivalue; } ifr_ifru; };
#define ifr_addr ifr_ifru.ifru_addr
#define ifr_flags ifr_ifru.ifru_flags
#endif
