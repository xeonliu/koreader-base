/* Compatibility glue for the PSP's TLS stack (pspdev's wolfSSL used through its OpenSSL layer), plus a few network /
 * user-management functions the PSP lacks.  Features pspdev's wolfSSL was built without (ALPN, PSK, SNI callbacks, ...)
 * are stubbed: they report "unsupported". */
#include <errno.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

/* wolfSSL entry points missing from pspdev's libwolfssl: signatures vary, all stubs return 0/NULL. */
#define STUB(name) long name() { return 0; }
STUB(wolfSSL_CIPHER_get_bits)
STUB(wolfSSL_CTX_get_verify_mode)
STUB(wolfSSL_CTX_set_alpn_select_cb)
STUB(wolfSSL_CTX_set_cert_verify_callback)
STUB(wolfSSL_CTX_set_psk_client_callback)
STUB(wolfSSL_CTX_set_psk_server_callback)
STUB(wolfSSL_CTX_set_tlsext_servername_callback)
STUB(wolfSSL_CTX_use_psk_identity_hint)
STUB(wolfSSL_PEM_write_bio_X509)
STUB(wolfSSL_export_keying_material)
STUB(wolfSSL_get0_alpn_selected)
STUB(wolfSSL_get0_chain_certs)
STUB(wolfSSL_get_certificate)
STUB(wolfSSL_get_finished)
STUB(wolfSSL_get_peer_cert_chain)
STUB(wolfSSL_get_peer_finished)
STUB(wolfSSL_get_servername)
STUB(wolfSSL_select_next_proto)
STUB(wolfSSL_set_SSL_CTX)
STUB(wolfSSL_set_tlsext_host_name)

/* OpenSSL names LuaSec calls as functions but that wolfSSL only offers as macros / not at all. */
/* pspdev's wolfSSL has no per-connection mode flags: accept and ignore them. */
long SSL_set_mode(void *ssl, long mode) { (void)ssl; return mode; }

#define APPDATA_SLOTS 32
static struct { void *ctx; void *data; } appdata[APPDATA_SLOTS];
void *SSL_CTX_get_app_data(void *ctx) { for (int i = 0; i < APPDATA_SLOTS; i++) if (appdata[i].ctx == ctx) return appdata[i].data; return NULL; }
int SSL_CTX_set_app_data(void *ctx, void *data) {
    int free_slot = -1;
    for (int i = 0; i < APPDATA_SLOTS; i++) {
        if (appdata[i].ctx == ctx) { appdata[i].data = data; return 1; }
        if (!appdata[i].ctx && free_slot < 0) free_slot = i;
    }
    if (free_slot < 0) return 0;
    appdata[free_slot].ctx = ctx; appdata[free_slot].data = data;
    return 1;
}
long SSL_up_ref(void *ssl) { (void)ssl; return 1; }
STUB(PEM_write_bio_PUBKEY)
STUB(SSL_COMP_get_name)
STUB(SSL_get_current_compression)
STUB(SSL_set_hostflags)
STUB(X509_STORE_CTX_get0_param)
STUB(X509_VERIFY_PARAM_set_purpose)
STUB(X509_VERIFY_PARAM_set_trust)

/* Name resolution and user management: not available on the PSP. */
struct ko_addrinfo;
int getaddrinfo(const char *n, const char *s, const void *h, struct ko_addrinfo **r) { (void)n; (void)s; (void)h; if (r) *r = NULL; return -4 /* EAI_FAIL */; }
void freeaddrinfo(struct ko_addrinfo *a) { (void)a; }
const char *hstrerror(int e) { (void)e; return "name resolution is not supported"; }
char *if_indextoname(unsigned i, char *n) { (void)i; (void)n; errno = ENXIO; return NULL; }
void *getgrnam(const char *n) { (void)n; return NULL; }
int setuid(unsigned u) { (void)u; errno = EPERM; return -1; }
int seteuid(unsigned u) { (void)u; errno = EPERM; return -1; }
int setgid(unsigned g) { (void)g; errno = EPERM; return -1; }
int socketpair(int d, int t, int p, int sv[2]) { (void)d; (void)t; (void)p; (void)sv; errno = ENOSYS; return -1; }
