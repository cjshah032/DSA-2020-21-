// #pragma once
#include "InsertionSort.h"

void InsertionSort(record list[], int l, int h)
{
    for(int i=l+1; i<=h; i++)
    {
        int j = i;
        record r = list[i];
        while(j > l && list[j-1].empID > r.empID)
        {
            list[j] = list[j-1];
            j--;
        }
        list[j] = r;
    }    
}