/* Force-included when building LuaSec against wolfSSL's OpenSSL compatibility layer (PSP). */
#ifndef KO_PSP_LUASEC_COMPAT_H
#define KO_PSP_LUASEC_COMPAT_H
#include <wolfssl/options.h>
#ifndef X509_TRUST_SSL_SERVER
#define X509_TRUST_SSL_SERVER 3
#endif
#ifndef SSL_X509_LOOKUP
#define SSL_X509_LOOKUP 4
#endif
#ifndef X509_CHECK_FLAG_MULTI_LABEL_WILDCARDS
#define X509_CHECK_FLAG_MULTI_LABEL_WILDCARDS 0x8
#endif
#ifndef X509_CHECK_FLAG_SINGLE_LABEL_SUBDOMAINS
#define X509_CHECK_FLAG_SINGLE_LABEL_SUBDOMAINS 0x10
#endif
/* wolfSSL's SSL/X509 are opaque: use the OpenSSL 1.1 reference-counting API rather than poking at structs. */
#define LSEC_API_OPENSSL_1_1_0
#endif
