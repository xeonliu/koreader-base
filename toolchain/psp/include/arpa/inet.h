/* Shim for PSP/newlib: <arpa/inet.h>. The PSP has no BSD socket API in newlib (only pspnet): enough for things to compile. */
#ifndef KO_PSP_ARPA_INET_H
#define KO_PSP_ARPA_INET_H
#include <netinet/in.h>
#ifdef __cplusplus
extern "C" {
#endif
unsigned long htonl(unsigned long); unsigned short htons(unsigned short);
unsigned long ntohl(unsigned long); unsigned short ntohs(unsigned short);
char *inet_ntoa(struct in_addr);
in_addr_t inet_addr(const char *);
int inet_aton(const char *, struct in_addr *);
int inet_pton(int, const char *, void *);
const char *inet_ntop(int, const void *, char *, socklen_t);
#ifdef __cplusplus
}
#endif
#endif
