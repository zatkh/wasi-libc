// This file is a wrapper around snmalloc.
// It sets PAL configuration and controls which symbols are exported.

#include <stddef.h>
#define WASI_ENV
#include <snmalloc.h>

/* Ensure PAL initialized */
static uint32_t initialization_magic = 0;
#define ensure_initialization() (void)(initialization_magic != 0 || init_pal())

static int init_pal() {
    // Skip first page from range to avoid NULL being a valid pointer.
    snmalloc::PALWASI::setup_initial_range(PAGESIZE, sbrk(0));
}

// Export the public names.
extern"C" {

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

}
