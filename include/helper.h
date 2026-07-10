#ifndef HELPER_H
#define HELPER_H

#include "../src/allocator_internal.h"
#include <stddef.h>

#define ALIGNMENT 16
#define ALIGN(size) ((size + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1))
#define FLAG_MASK (ALIGNMENT - 1)
#define SIZE_MASK (~FLAG_MASK)

static inline int is_allocated(Header* h){
    return h->size_and_flags & 1;
}

static inline int get_size(Header* h){
    return h->size_and_flags & SIZE_MASK;
}

static inline void set_size(Header* h, size_t size){
    h->size_and_flags = size | (h->size_and_flags & FLAG_MASK);
}

static inline void mark_free(Header* h){
    h->size_and_flags &= ~((size_t)1);
}

static inline void mark_allocated(Header* h){
    h->size_and_flags |= 1;
}

#endif