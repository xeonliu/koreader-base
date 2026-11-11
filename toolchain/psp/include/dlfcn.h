/* PSP: no dynamic loader. Declarations only, for sources that include <dlfcn.h> without really needing it. */
#ifndef KO_PSP_DLFCN_H
#define KO_PSP_DLFCN_H
#define RTLD_LAZY 1
#define RTLD_NOW 2
#define RTLD_GLOBAL 0x100
#define RTLD_LOCAL 0
#ifdef __cplusplus
extern "C" {
#endif
void *dlopen(const char *, int);
void *dlsym(void *, const char *);
int dlclose(void *);
char *dlerror(void);
#ifdef __cplusplus
}
#endif
#endif
