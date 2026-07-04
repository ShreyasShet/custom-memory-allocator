#include "allocator.h"
void* a = my_malloc(128);

my_free(a);

my_malloc(16);
my_malloc(16);
my_malloc(16);

print_blocks();
