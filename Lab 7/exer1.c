#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "InsertionSort.h"
#include "QuickSort.h"

int main(int argc, char ** argv)
{
    if(argc < 3)    //expecting command line arguments: filename, cutoff size. 
        return -1;
    char* filename = argv[1];
    int s = atoi(argv[2]);
    int n = atoi(filename);
    record* list = readRecords(filename, n);
    QuickSort(list, 0, n-1, s);               
    InsertionSort(list, 0, n-1);
    printRecordsinFile(list, n, "res1.txt");
    free(list);
    return 0;
}