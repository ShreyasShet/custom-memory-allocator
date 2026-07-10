#include <stdio.h>
#include "../include/allocator.h"
#include "allocator_internal.h"
#include "../include/helper.h"
#include "heap.h"

char heap[HEAP_SIZE];
Header* heap_start = NULL;
Header* heap_end;

void* my_malloc(size_t size){
    if(heap_start == NULL){
        heap_start = heap_init();
        heap_end = heap_start;
    }
    size = ALIGN(size);
    size_t total = sizeof(Header) + size + sizeof(Footer);
    size_t pos = sizeof(Header) + sizeof(Header) + sizeof(Footer);
    Header* h = (Header*)&heap[pos];
    while(h != heap_end){
        if(!(is_allocated(h)) && size <= get_size(h)){
            size_t remaining_size = get_size(h) - size;
            if(remaining_size >= sizeof(Footer) + sizeof(Header) + MIN_PAYLOAD_SIZE){
                set_size(h, size);
                Footer* f = (Footer*)((char*)h + sizeof(Header) + get_size(h));
                f->size = get_size(h);
                Header* h2 = (Header*)((char*)f + sizeof(Footer));
                set_size(h2, (remaining_size - sizeof(Header) - sizeof(Footer)));
                mark_free(h2);
                Footer* f2 = (Footer*)((char*)h2 + sizeof(Header) + get_size(h2));
                f2->size = get_size(h2);
            }
            mark_allocated(h);
            return (void*)(h + 1); 
        }
        h = (Header*)((char*)h + sizeof(Header) + get_size(h) + sizeof(Footer));
    }
    if((char*)heap_end + total > &heap[HEAP_SIZE - sizeof(Header)])
        return NULL;
    Header* h1 = heap_end;
    mark_allocated(h1);
    set_size(h1, size);
    void* ptr = (char*)h1 + sizeof(Header);
    Footer* f1 = (Footer*)((char*)h1 + sizeof(Header) + size);
    f1->size = size;
    Header *epilogue = (Header *)((char *)f1 + sizeof(Footer));
    mark_allocated(epilogue);
    set_size(epilogue, 0);
    heap_end = epilogue;
    return ptr; 
}

void my_free(void* ptr){
    if (ptr == NULL)
        return;
    Header* h = (Header*)ptr - 1;
    mark_free(h);
    Header* cur = h;
    Header* next = (Header*)((char*)cur + sizeof(Header) + get_size(cur) + sizeof(Footer));
    if(next != heap_end && !(is_allocated(next))){
        size_t total = sizeof(Header) + get_size(next);
        set_size(cur, get_size(cur) + sizeof(Footer) + total);
        mark_free(cur);
        Footer* f = (Footer*)((char*)cur + sizeof(Header) + get_size(cur));
        f->size = get_size(cur);
    }
    if(cur != heap_start){
        Footer* prev_footer = (Footer*)((char*)cur - sizeof(Footer));
        Header* prev = (Header*)((char*)cur - (sizeof(Footer) + prev_footer->size + sizeof(Header)));
        if(prev >= heap_start && !(is_allocated(prev))){
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
    Header* h = heap_start;
    while(h != heap_end){  
        printf("%d %d\n", get_size(h), is_allocated(h));
        h = (Header*)((char*)h + sizeof(Header) + get_size(h) + sizeof(Footer));
    }
}