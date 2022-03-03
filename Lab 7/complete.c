#include "records.h"
#include "stack.h"
#include "QuickSort.h"
#include "InsertionSort.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

///////////Structures from records.h
/*
    typedef struct {
        int empID;
        char name[10];
    } record;
*/
//////////////////////////////////////////////


///////////Functions from record.c:
record* readRecords(char* filename, int n)
{
    record* list = (record*) malloc(n*sizeof(record));
    FILE* fp = fopen(filename, "r");
    for(int i=0; i<n && !feof(fp); i++)
    {
        fscanf(fp, "%s %d", &list[i].name, &list[i].empID);
    }

    fclose(fp);
    return list;
}

void printRecords(record list[], int n)
{
    for(int i=0; i<n; i++)
        printf("%s %d\n", list[i].name, list[i].empID);
}

void printRecordsinFile(record list[], int n, char* filename)
{
    FILE* fp = fopen(filename, "w");
    for(int i=0; i<n; i++)
        fprintf(fp, "%s %d\n", list[i].name, list[i].empID);
    fclose(fp);
}
///////////////////////////////////////////////////////////////


//////Structures from stack.h:
/*
    typedef struct node{
        int val;
        struct node* next;
    } node;

    typedef struct stack{
        node* top;
    } stack;

*/
///////////////////////////////////////////////////////////

//////Functions from stack.c:
stack* createStack()
{
    stack* s = (stack*) malloc(sizeof(stack));
    s->top = NULL;
    return s;
}

void push(stack* s, int val)
{
    assert(s != NULL);
    node* newnode = (node*) malloc(sizeof(node));
    assert(newnode != NULL);
    newnode->val = val;
    newnode->next = s->top;
    s->top = newnode;
}

int pop(stack* s)
{   
    assert(s != NULL);
    assert(s->top != NULL);
    node* temp = s->top;
    s->top = s->top->next;
    int tval = temp->val;
    free(temp);
    return tval;
}

int isEmpty(stack* s)
{
    if(s->top == NULL)
        return 1;
    return 0;
}
//////////////////////////////////////////////////////////////


////Functions from IterativeQuickSort.c:
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
///////////////////////////////////////////////////


/////Functions from IterativeInsertionSort.c:
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
///////////////////////////////////////////////////



/////Driver function for exercise 1: (commented out because there can't be two main functions)
/*
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
*/
//////////////////////////////////////////////////



/////Structs used in exercise 2:
typedef struct {
    long long istime, qstime;
} iqstt;


////// Functions in exercise 2a and 2b:
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
////////////////////////////////////////////////////


////// Driver function used in exercise 2b and 3:
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
/////////////////////////////////////////////////////////
/////////////////END OF ALL FUNCTIONS////////////////////
/////////////////////////////////////////////////////////