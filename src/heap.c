#include "../src/allocator_internal.h"
#include "../include/helper.h"
#include "../src/heap.h"
#include "../include/free_list.h"

void* heap_init(){
    char* base = heap;
    Header* prologue_header = (Header*)(base + sizeof(Header));
    mark_allocated(prologue_header);
    set_size(prologue_header, 0);
    Footer* prologue_footer = (Footer*)((char*)prologue_header + sizeof(Header));
    prologue_footer->size = 0;
    Header* epilogue = (Header*)((char*)prologue_footer + sizeof(Footer));
    mark_allocated(epilogue);
    set_size(epilogue, 0);
    return epilogue;
}