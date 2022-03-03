#include "readFile.h"

void insertInOrder(record *arr, record rec, int r); 
//takes in the array and inserts the record in sorted order in the subarray from index 0 to r-1
//after insertion, the array expands till rth index

void insertionSort(record *arr, int l, int r); 
// sorts the array using insertion sort.
// 0-l is the subarray which is sorted part

