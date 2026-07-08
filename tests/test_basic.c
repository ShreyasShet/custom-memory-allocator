#include "allocator.h"

void* a = my_malloc(32);
my_free(a);
void* b = my_malloc(16);

print_block();
