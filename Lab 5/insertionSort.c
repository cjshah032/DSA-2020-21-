#include "insertionSort.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

static int* p1; 
static int* p2;  //used for measuring stack space


void insertInOrder(record* arr, record rec, int r)
{
    int i = r;
    while(arr[i-1].card_number >= rec.card_number)
    {
        arr[i] = arr[i-1];
        i--;
        if(i == 0)
            break;
    }

    arr[i] = rec;
}

void insertionSort(record* arr, int l, int r)
{
    int b;
    if(&b < p2)  // used for measuring stack space
        p2 = &b;
    if(l == r)  //when l == r, array is sorted
        return;
    if(l == 0)
        insertionSort(arr, l+1, r);
    else {
        insertInOrder(arr, arr[l], l);
        insertionSort(arr, l+1, r);
    }
}

int main(int argc, char** argv)
{
    char* filename = argv[1];
    int num = atoi(argv[1]);
    int b;
    p1 = &b;    //stack space base
    p2 = p1;    

    record* rs = readFileForRecords(filename);
    struct timeval t1, t2;
    gettimeofday(&t1, NULL); 
    
    insertionSort(rs, 0, num);  //calling insertionSort

    // for(int i=0; i<num; i++)
    //      printf("%llu\n", rs[i].card_number);     //printing data (for debugging purposes)

    gettimeofday(&t2, NULL);
    double ti = (t2.tv_sec - t1.tv_sec)*1000;
    ti += ((t2.tv_usec - t1.tv_usec)/1000); 
    printf("%lld\n",(long long) (p1-p2));   //stack space
    printf("%.10f", ti);    //runtime
    return 0;
}