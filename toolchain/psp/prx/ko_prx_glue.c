/* Module-side glue: compiled into every KOReader PRX module (with -DKO_MODULE_NAME="name"). See ko_prx.h. */
#include <pspkernel.h>
#include "ko_prx.h"

PSP_MODULE_INFO(KO_MODULE_NAME, PSP_MODULE_USER, 1, 0);
PSP_NO_CREATE_MAIN_THREAD();

extern const struct ko_import ko_imports[];   /* NULL-name terminated */
extern const struct ko_sym ko_exports[];
extern const int ko_nexports;

/* newlib's stdio/errno state lives in the main program: share its reentrancy structure. */
struct _reent;
struct _reent *_impure_ptr;

/* Static constructors (C++ modules). */
typedef void (*ko_ctor)(void);
extern ko_ctor __init_array_start[], __init_array_end[];   /* provided by pspsdk's linkfile.prx */
extern ko_ctor ko_ctors_start[], ko_ctors_end[];           /* ko_prx_start.S / ko_prx_end.S */
extern const char ko_eh_frame_start[];
extern void __register_frame_info(const void *, void *) __attribute__((weak));   /* libgcc, when the module unwinds */
void *__dso_handle = &__dso_handle;

int module_start(SceSize args, void *argp) {
    struct ko_module_link *link = (args >= sizeof(void *) && argp) ? *(struct ko_module_link **)argp : 0;
    if (!link || link->magic != KO_PRX_MAGIC) return 1;
    for (const struct ko_import *imp = ko_imports; imp->name; imp++) {
        void *addr = link->resolve(imp->name);
        if (!addr) { link->error = imp->name; return 1; }
        *imp->slot = addr;
    }
    struct _reent **main_impure = (struct _reent **)link->resolve("_impure_ptr");
    if (main_impure) _impure_ptr = *main_impure;
    if (__register_frame_info) { static long eh_object[8]; __register_frame_info(ko_eh_frame_start, eh_object); }
    for (ko_ctor *c = ko_ctors_end; c > ko_ctors_start; ) { --c; if (*c && *c != (ko_ctor)-1) (*c)(); }
    for (ko_ctor *c = __init_array_start; c < __init_array_end; c++) if (*c && *c != (ko_ctor)-1) (*c)();
    link->exports = ko_exports;
    link->nexports = ko_nexports;
    return 0;
}

int module_stop(SceSize args, void *argp) { (void)args; (void)argp; return 0; }
