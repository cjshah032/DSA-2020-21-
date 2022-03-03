// #pragma once
#include "QuickSort.h"
#include "stack.h"
#include<stdlib.h>

void swap(record* a, record* b)
{
    record temp = *a;
    *a = *b;
    *b = temp;
}

int partition(record list[], int l, int h)
{
    int x = list[h].empID;
    int i = l-1;
    int j = h+1;

    for(; ;)
    {
        while(list[++i].empID <= x && i < h){}        
        while(list[--j].empID >= x && j >= l){}
        if(i<j)
            swap(&list[i], &list[j]);
        else break;
    }
    swap(&list[i], &list[h]);
    return i;
}

void QuickSort(record list[], int l, int h, int S)
{
    stack* s = createStack();
    push(s, l);
    push(s, h);

    while(!isEmpty(s))
    {
        int hi = pop(s);
        int li = pop(s);

        if(hi-li+1 > S)
        {
            int p = partition(list, li, hi);

            if(p - 1 > li)
            {
                push(s, li);
                push(s, p-1);
            }

            if(p + 1 < hi)
            {
                push(s, p+1);
                push(s, hi);
            }
        }
    }
    free(s);
}