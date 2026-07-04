#ifndef MY_ALLOCATOR_H
#define MY_ALLOCATOR_H

#include <stddef.h>

#define HEAP_SIZE 1024
#define MIN_BLOCK_SIZE 8

typedef struct header{
    size_t size;
    int free;
}Header;

typedef struct footer{
    size_t size;
} Footer;

#endif
