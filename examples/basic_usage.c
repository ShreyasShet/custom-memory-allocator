#include "allocator.h"

int* arr = my_malloc(10 * sizeof(int));

for(int i = 0; i < 10; i++)
    arr[i] = i;

my_free(arr);
