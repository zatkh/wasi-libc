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

void *malloc(size_t size) {
    return sn_malloc(size);
}

void free(void *ptr) {
    sn_free(ptr);
}

void *calloc(size_t nmemb, size_t size) {
    return sn_calloc(nmemb, size);
}

void *realloc(void *ptr, size_t size) {
    return sn_realloc(ptr, size);
}

int posix_memalign(void **memptr, size_t alignment, size_t size) {
    return sn_posix_memalign(memptr, alignment, size);
}

void* aligned_alloc(size_t alignment, size_t bytes) {
    return sn_aligned_alloc(alignment, bytes);
}

size_t malloc_usable_size(void *ptr) {
    return sn_malloc_usable_size(ptr);
}
