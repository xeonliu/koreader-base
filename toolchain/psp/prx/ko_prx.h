/* KOReader PSP modules: document engines live in separate PRX files that the main program loads on demand.
 *
 * A module is linked without a C library of its own. Every function it needs from the main program (libc, the
 * allocator, LuaJIT, FreeType, zlib, ...) is reached through a generated stub that jumps via a slot; the slots are
 * filled by name when the module starts (see ko_prx_glue.c / gen-prx-imports.py). In the other direction, the module
 * hands back a sorted table of the symbols it exports, which the main program uses for ffi.load()/require().
 * All user modules share one address space, so plain pointers can be passed both ways.
 */
#ifndef KO_PRX_H
#define KO_PRX_H

#define KO_PRX_MAGIC 0x4b4f5058u /* "KOPX" */

struct ko_sym { const char *name; void *addr; };

/* Passed (by pointer) to a module's module_start(). */
struct ko_module_link {
    unsigned magic;
    void *(*resolve)(const char *name);   /* in: look a symbol up in the main program and in loaded modules */
    const struct ko_sym *exports;         /* out: the module's exported symbols, sorted by name (strcmp order) */
    int nexports;                         /* out */
    const char *error;                    /* out: name of the first import that could not be resolved */
};

/* Generated per module (gen-prx-imports.py). */
struct ko_import { const char *name; void **slot; };

#endif
