/* Shim for PSP/newlib: <netdb.h>. Declarations only; the resolver functions are ENOSYS stubs in the launcher. */
#ifndef KO_PSP_NETDB_H
#define KO_PSP_NETDB_H
#include <sys/socket.h>
#ifdef __cplusplus
extern "C" {
#endif
struct addrinfo { int ai_flags, ai_family, ai_socktype, ai_protocol; socklen_t ai_addrlen; struct sockaddr *ai_addr; char *ai_canonname; struct addrinfo *ai_next; };
struct hostent { char *h_name; char **h_aliases; int h_addrtype; int h_length; char **h_addr_list; };
#define h_addr h_addr_list[0]
#define AI_PASSIVE 1
int getaddrinfo(const char *, const char *, const struct addrinfo *, struct addrinfo **);
void freeaddrinfo(struct addrinfo *);
const char *gai_strerror(int);
struct hostent *gethostbyname(const char *);
#ifdef __cplusplus
}
#endif
#endif
