#include <stdio.h>
#include "my_allocator.h"
#include "allocator_internal.h"

static char heap[HEAP_SIZE];
static size_t current = 0;

void* my_malloc(size_t size){
    size_t total = sizeof(Header) + size + sizeof(Footer);
    size_t pos = 0;
    Header* h = (Header*)&heap[pos];
    while((char*)h < &heap[current]){
        if(h->free == 1 && size <= h->size){
            size_t remaining_size = h->size - size;
            if(remaining_size >= sizeof(Footer) + sizeof(Header) + MIN_BLOCK_SIZE){
                h->size = size;
                Footer* f = (Footer*)((char*)h + sizeof(Header) + h->size);
                f->size = h->size;
                Header* h2 = (Header*)((char*)h + sizeof(Header) + size + sizeof(Footer));
                h2->free = 1;
                h2->size = remaining_size - sizeof(Header) - sizeof(Footer);
                Footer* f2 = (Footer*)((char*)h2 + sizeof(Header) + h2->size);
                f2->size = h2->size;
            }
            h->free = 0;
            return (void*)(h + 1); 
        }
        h = (Header*)((char*)h + sizeof(Header) + h->size + sizeof(Footer));
    }
    if(current + total > HEAP_SIZE)
        return NULL;
    Header* h1 = (Header*)&heap[current];
    h1->size = size;
    h1->free = 0;
    void* ptr = &heap[current + sizeof(Header)];
    Footer* f1 = (Footer*)((char*)h1 + sizeof(Header) + size);
    f1->size = size;
    current += total;
    return ptr; 
}

void my_free(void* ptr){
    if (ptr == NULL)
        return;
    Header* h = (Header*)ptr - 1;
    h->free = 1;
    Header* cur = h;
    Header* next = (Header*)((char*)cur + sizeof(Header) + cur->size + sizeof(Footer));
    if((char*)next < &heap[current] && next->free){
        size_t total = sizeof(Header) + next->size;
        cur->size += (sizeof(Footer) + total);
        Footer* f = (Footer*)((char*)cur + sizeof(Header) + cur->size);
        f->size = cur->size;
    }
    if((char*)cur > heap){
        Footer* prev_footer = (Footer*)((char*)cur - sizeof(Footer));
        Header* prev = (Header*)((char*)cur - (sizeof(Footer) + prev_footer->size + sizeof(Header)));
        if((char*)prev >= &heap[0] && prev->free){
            size_t total = sizeof(Header) + cur->size;
            prev->size += (sizeof(Footer) + total);
            cur = prev;
            Footer* f = (Footer*)((char*)cur + sizeof(Header) + cur->size);
            f->size = cur->size;
        }
    }
}

void print_block(){
    size_t pos = 0;
    while(pos < current){
        Header* h = (Header*)&heap[pos];  
        printf("%zu %d\n", h->size, h->free);
        pos += sizeof(Header) + h->size + sizeof(Footer);
    }
}
