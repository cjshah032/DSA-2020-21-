#include "profiling.h"
#include "parsing.h"
#include <stdlib.h>
#include <limits.h>

const int base[3][6] = {{5303, 6997, 8779, 5047411, 5047747, 5047921}, {89431, 90011, 99991, 67883117, 67893841, 67897157}, {792983, 811259, 825203, 512928517, 512929789, 512942281}};
const int table[3] = {5000, 50000, 500000};

void profiling(char** book, int book_size, int* b_index, int* t_index)
{
    *t_index = 0;
    *b_index = 0;
    int bestColCount = INT_MAX;
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<6; j++)
        {
            int colCount = count_collisions(book, book_size, base[i][j], table[i]);
            if(colCount < bestColCount)
            {
                *t_index = i;
                *b_index = j;
                bestColCount = colCount;
            }
            printf("Collision Count for baseNumber = %d and tableSize = %d is %d\n", base[i][j], table[i], colCount);
        }
    }

    printf("Indexes for best collision count in base array = %d & table array = %d\n", *b_index, *t_index);
    printf("%d\n", count_collisions(book, book_size, base[*t_index][*b_index], table[*t_index]));
}

int main()
{
    int c = 0;
    char** s = parsing("aliceinwonderland.txt", &c);
    int t, b;
    printf("%d\n", hash("aliceioerland", 89431, 50000));
    // profiling(s, c, &b, &t);
    count_collisions(s, c, 5303, 5000);
    for(int i=0; i<c; i++)
        free(s[i]);
    free(s);
}