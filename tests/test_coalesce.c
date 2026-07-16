#include "../include/allocator.h"

int main(){
    void* a = my_malloc(64);
    void* b = my_malloc(64);
    void* c = my_malloc(64);

    my_free(b);
    my_free(c);
    my_free(a);
    heap_check();
}