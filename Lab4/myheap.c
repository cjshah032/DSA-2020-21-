#include "myheap.h"
#include<stdlib.h>
#include<assert.h>

long long int heapMemory = 0;

void* myalloc(int size)
{
    void* ptr = malloc(size);
    heapMemory += size;
    return ptr;
}

void myfree(void* ptr, int size)
{
    assert(ptr != NULL);
    free(ptr);
    heapMemory -= size;
}