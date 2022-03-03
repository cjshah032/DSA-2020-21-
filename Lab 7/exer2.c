#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include"QuickSort.h"
#include"InsertionSort.h"
#include<windows.h>

typedef struct {
    long long istime, qstime;
} iqstt;

iqstt testRun(record* list, int size)
{
    record* ls1 = (record*) malloc(size*sizeof(record));
    record* ls2 = (record*) malloc(size*sizeof(record));
    for(int i=0; i<size; i++)
    {
        ls1[i] = list[i];
        ls2[i] = list[i];
    }
    iqstt tt;
    LARGE_INTEGER t1, t2;
    QueryPerformanceCounter(&t1);
    InsertionSort(ls1, 0, size-1);
    QueryPerformanceCounter(&t2);
    tt.istime = (t2.QuadPart-t1.QuadPart);
    QueryPerformanceCounter(&t1);
    QuickSort(ls2, 0, size-1, 1);
    QueryPerformanceCounter(&t2);
    tt.qstime = (t2.QuadPart-t1.QuadPart);
    free(ls1);
    free(ls2);
    return tt;
}

int estimateCutoff(record list[], int maxSize)
{
    iqstt tt1 = testRun(list, 50);
    assert(tt1.istime <= tt1.qstime);
    iqstt tt2 = testRun(list, maxSize);
    assert(tt2.istime > tt2.qstime);
    int min = 2, max = maxSize, mid=0;
    while(min < max)
    {
        mid = (min+max)/2;
        iqstt tt = testRun(list, mid);
        if(tt.istime > tt.qstime)
            max = mid;
        else min = mid+1;
    }

    return mid;
}

int main(int argc, char** argv)
{
    if(argc < 3)
        return -1;

    int n = atoi(argv[1]);
    const int maxsize = n > 10000 ? 10000 : n;  //using a smaller maxsize because higher inputs don't work with complete insertion sort.
    LARGE_INTEGER t1, t2;
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    for(int i=10000; i<100000000; i*=10)
    {
        record* list = readRecords(argv[1], n);
        int cut = estimateCutoff(list, maxsize);
        QueryPerformanceCounter(&t1);
        QuickSort(list, 0, i-1, cut);
        InsertionSort(list, 0, i-1);
        QueryPerformanceCounter(&t2);
        printf("N: %d Time: %lf ms\n", i, (double)((t2.QuadPart-t1.QuadPart)*1000.0)/(freq.QuadPart));
        printRecordsinFile(list, i, argv[2]);
        free(list);
    }
}