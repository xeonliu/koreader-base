/* Shim for PSP/newlib: <netinet/in.h> (the PSP's own is in the SDK and not on the default include path). */
#ifndef KO_PSP_NETINET_IN_H
#define KO_PSP_NETINET_IN_H
#include <stdint.h>
#include <sys/socket.h>
typedef uint32_t in_addr_t;
typedef uint16_t in_port_t;
struct in_addr { in_addr_t s_addr; };
struct in6_addr { uint8_t s6_addr[16]; };
struct ip_mreq { struct in_addr imr_multiaddr; struct in_addr imr_interface; };
struct ipv6_mreq { struct in6_addr ipv6mr_multiaddr; unsigned ipv6mr_interface; };
struct sockaddr_in { sa_family_t sin_family; in_port_t sin_port; struct in_addr sin_addr; char sin_zero[8]; };
struct sockaddr_in6 { sa_family_t sin6_family; in_port_t sin6_port; uint32_t sin6_flowinfo; struct in6_addr sin6_addr; uint32_t sin6_scope_id; };
#define INADDR_ANY ((in_addr_t)0)
#define INADDR_NONE ((in_addr_t)0xffffffff)
#define INADDR_LOOPBACK ((in_addr_t)0x7f000001)
#define IPPROTO_IP 0
#define IPPROTO_ICMP 1
#define IPPROTO_TCP 6
#define IPPROTO_UDP 17
#define IPPROTO_IPV6 41
#define IP_TOS 1
#define IP_TTL 2
#define IP_MULTICAST_TTL 33
#define IP_ADD_MEMBERSHIP 35
#define IPV6_V6ONLY 26
#define IPV6_JOIN_GROUP 20
#define IN6ADDR_ANY_INIT {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}}
#define IN6ADDR_LOOPBACK_INIT {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}}
#define IPV6_UNICAST_HOPS 16
#define IPV6_MULTICAST_HOPS 18
#define IPV6_MULTICAST_IF 17
#define IPV6_MULTICAST_LOOP 19
#define IPV6_ADD_MEMBERSHIP 20
#define IPV6_DROP_MEMBERSHIP 21
#define IP_MULTICAST_IF 32
#define IP_MULTICAST_LOOP 34
#define IP_DROP_MEMBERSHIP 36
#define INET_ADDRSTRLEN 16
#define INET6_ADDRSTRLEN 46
#define IN_CLASSD(a) (((uint32_t)(a) & 0xf0000000) == 0xe0000000)
#define IN_MULTICAST(a) IN_CLASSD(a)
#define IN6_IS_ADDR_MULTICAST(a) ((a)->s6_addr[0] == 0xff)
#ifdef __cplusplus
extern "C" {
#endif
extern const struct in6_addr in6addr_any;
extern const struct in6_addr in6addr_loopback;
#ifdef __cplusplus
}
#endif
#ifdef __cplusplus
extern "C" {
#endif
unsigned long htonl(unsigned long); unsigned short htons(unsigned short);
unsigned long ntohl(unsigned long); unsigned short ntohs(unsigned short);
#ifdef __cplusplus
}
#endif
#endif
