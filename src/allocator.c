#include <stdio.h>
#include "../include/allocator.h"
#include "allocator_internal.h"
#include "../include/helper.h"

static char heap[HEAP_SIZE];
static size_t current = 0;

void* my_malloc(size_t size){
    size_t total = sizeof(Header) + size + sizeof(Footer);
    size_t pos = 0;
    Header* h = (Header*)&heap[pos];
    while((char*)h < &heap[current]){
        if(!(is_allocated(h)) && size <= get_size(h)){
            size_t remaining_size = get_size(h) - size;
            if(remaining_size >= sizeof(Footer) + sizeof(Header) + MIN_BLOCK_SIZE){
                set_size(h, size);
                Footer* f = (Footer*)((char*)h + sizeof(Header) + get_size(h));
                f->size = get_size(h);
                Header* h2 = (Header*)((char*)h + sizeof(Header) + size + sizeof(Footer));
                set_size(h2, (remaining_size - sizeof(Header) - sizeof(Footer)));
                Footer* f2 = (Footer*)((char*)h2 + sizeof(Header) + get_size(h2));
                f2->size = get_size(h2);
            }
            mark_allocated(h);
            return (void*)(h + 1); 
        }
        h = (Header*)((char*)h + sizeof(Header) + get_size(h) + sizeof(Footer));
    }
    if(current + total > HEAP_SIZE)
        return NULL;
    Header* h1 = (Header*)&heap[current];
    mark_allocated(h1);
    set_size(h1, size);
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
    mark_free(h);
    Header* cur = h;
    Header* next = (Header*)((char*)cur + sizeof(Header) + get_size(cur) + sizeof(Footer));
    if((char*)next < &heap[current] && !(is_allocated(next))){
        size_t total = sizeof(Header) + get_size(next);
        set_size(cur, get_size(cur) + sizeof(Footer) + total);
        mark_free(cur);
        Footer* f = (Footer*)((char*)cur + sizeof(Header) + get_size(cur));
        f->size = get_size(cur);
    }
    if((char*)cur > heap){
        Footer* prev_footer = (Footer*)((char*)cur - sizeof(Footer));
        Header* prev = (Header*)((char*)cur - (sizeof(Footer) + prev_footer->size + sizeof(Header)));
        if((char*)prev >= &heap[0] && !(is_allocated(prev))){
            size_t total = sizeof(Header) + get_size(cur);
            set_size(prev, get_size(prev) + sizeof(Footer) + total);
            cur = prev;
            mark_free(cur);
            Footer* f = (Footer*)((char*)cur + sizeof(Header) + get_size(cur));
            f->size = get_size(cur);
        }
    }
}

void print_block(){
    size_t pos = 0;
    while(pos < current){
        Header* h = (Header*)&heap[pos];  
        printf("%d %d\n", get_size(h), is_allocated(h));
        pos += sizeof(Header) + get_size(h) + sizeof(Footer);
    }
}