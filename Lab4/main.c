#include "cycle.h"
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <sys/time.h>

extern long long int heapMemory;

struct linkedList* createList(int N)
{
    assert(N > 0);
    struct linkedList* list = (struct linkedList*) myalloc(sizeof(struct linkedList));
    assert(list != NULL);
    list->first = NULL;
    for(int i=0; i<N; i++)
    {
        int d = rand();
        insertFirst(list, d);
    }

    return list;
}

void createCycle(struct linkedList* list)
{
    int n = 0; //size of list
    struct node* curr = list->first;
    struct node* last = curr;
    while(curr != NULL)
    {
        last = curr;
        curr = curr->next;
        n++;
    }

    if(n < 2)
        return; //can't create cycle with 1 node

    int decision = rand()%2;
    if(decision == 1)
    {
        int r = rand()%n + 1;
        while(r == n)
            r = rand()%n + 1; //cannot point last node to itself

        curr = list->first;
        for(int i = 0; i<r; i++)
            curr = curr->next;
        last->next = curr;
    }
}

// ///// exercise 3 /////
// int main()
// {
//     srand(time(0));
//     int n = 1e5;
//     struct linkedList* l = createList(n);
//     createCycle(l);
//     int cyc = testCycle(l);
//     if(cyc == 1)
//         printf("Cycle found\n");
//     else printf("Cycle not found\n");

//     return 0;
// }

//// exercise 4 (assignment) ////
int main()
{
    srand(time(0));
    int n;  //changed with every run
    scanf("%d", &n);
    struct timeval t1, t2;
    gettimeofday(&t1, NULL);
    struct linkedList* l = createList(n);
    createCycle(l);
    int cycDetected = testCycle(l);
    if(cycDetected == 1)
        printf("Cycle found.\n");
    else printf("Cycle not found.\n");
    printf("Memory used: %d\n", heapMemory);
    gettimeofday(&t2, NULL);
    double ti = (t2.tv_sec - t1.tv_sec)*1000;
    ti += ((t2.tv_usec - t1.tv_usec)/1000); 

    printf("Time to run computation: %.2fms\n", ti);
}