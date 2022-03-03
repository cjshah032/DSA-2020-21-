#include "hashing.h"
#include <stdlib.h>
#include <string.h>

int hash(char* str, int baseNumber, int tableSize)
{
    int sum = 0;
    for(int i=0; i<strlen(str); i++)
    {
        sum += (int)str[i];
        // printf("%d\n", sum);
    }    
    return ((sum%baseNumber)%tableSize);
}

int count_collisions(char** str_array, int array_size, int baseNumber, int tableSize)
{
    int* count = (int*) malloc(tableSize*sizeof(int));
    for(int i=0; i<tableSize; i++)
        count[i] = 0;
    
    for(int i=0; i<array_size; i++)    
        count[hash(str_array[i], baseNumber, tableSize)] ++;
    
    int collisions = 0;
    for(int i=0; i<tableSize; i++)
    {
        collisions += (count[i] > 1 ? count[i]-1 : 0);
        printf("%d ", count[i]);
    }
        
    free(count);
    return collisions;
}