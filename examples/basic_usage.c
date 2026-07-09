#include "../include/allocator.h"
#include <stdio.h>

int main(){
    int* arr = my_malloc(10 * sizeof(int));

    for(int i = 0; i < 10; i++)
        arr[i] = i;

    for(int i = 0; i < 10; i++)
        printf("%d", arr[i]);

    my_free(arr);
}