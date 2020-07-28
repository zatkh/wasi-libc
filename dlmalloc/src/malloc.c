// This file is a wrapper around snmalloc.
// It sets PAL configuration and controls which symbols are exported.

#include <stddef.h>
#include <unistd.h>

extern void *sn_malloc(size_t size);
extern void sn_free(void *ptr);
extern void *sn_calloc(size_t nmemb, size_t size);
extern void *sn_realloc(void *ptr, size_t size);
extern int sn_posix_memalign(void **memptr, size_t alignment, size_t size);
extern void* sn_aligned_alloc(size_t alignment, size_t bytes);
extern size_t sn_malloc_usable_size(void *ptr);
extern void* _ZN8snmalloc7PALWASI9heap_baseE;
extern size_t _ZN8snmalloc7PALWASI9heap_sizeE;

/* Ensure PAL initialized */
static size_t initialization_magic = 0;
#define ensure_initialization() (void)(initialization_magic != 0 || init_pal())

static int init_pal() {
    // Skip first page from range to avoid NULL being a valid pointer.
    _ZN8snmalloc7PALWASI9heap_baseE = (void*)PAGESIZE;
    _ZN8snmalloc7PALWASI9heap_sizeE = (size_t)sbrk(0);
    return 1;
}

#include <stdio.h>

void *malloc(size_t size) {
    ensure_initialization();
    return sn_malloc(size);
}

void free(void *ptr) {
    ensure_initialization();
    sn_free(ptr);
}

void *calloc(size_t nmemb, size_t size) {
    ensure_initialization();
    return sn_calloc(nmemb, size);
}

void *realloc(void *ptr, size_t size) {
    ensure_initialization();
    return sn_realloc(ptr, size);
}

int posix_memalign(void **memptr, size_t alignment, size_t size) {
    ensure_initialization();
    return sn_posix_memalign(memptr, alignment, size);
}

void* aligned_alloc(size_t alignment, size_t bytes) {
    ensure_initialization();
    return sn_aligned_alloc(alignment, bytes);
}

size_t malloc_usable_size(void *ptr) {
    ensure_initialization();
    return sn_malloc_usable_size(ptr);
}
