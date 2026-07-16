#ifndef MY_ALLOCATOR_H
#define MY_ALLOCATOR_H

#include <stddef.h>

#define HEAP_SIZE 1024
#define MIN_PAYLOAD_SIZE 16

typedef struct header{
    size_t size_and_flags;
} Header;

typedef struct footer{
    size_t size;
} Footer;

typedef struct freenode{
    struct freenode* prev;
    struct freenode* next;
} Node;

extern char heap[HEAP_SIZE];
#endif