/* Shim for PSP/newlib: <netinet/in.h> (the PSP's own is in the SDK and not on the default include path). */
#ifndef KO_PSP_NETINET_IN_H
#define KO_PSP_NETINET_IN_H
#include <stdint.h>
#include <sys/socket.h>
typedef uint32_t in_addr_t;
typedef uint16_t in_port_t;
struct in_addr { in_addr_t s_addr; };
struct sockaddr_in { sa_family_t sin_family; in_port_t sin_port; struct in_addr sin_addr; char sin_zero[8]; };
#define INADDR_ANY ((in_addr_t)0)
#define INADDR_LOOPBACK ((in_addr_t)0x7f000001)
#define IPPROTO_TCP 6
#define TCP_NODELAY 1
#endif
