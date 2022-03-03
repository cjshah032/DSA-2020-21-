#include "que.h"
#include<stdio.h>
#include<stdlib.h>

Queue* newQ()
{
    Queue* q = (Queue*) malloc(sizeof(Queue));
    if(q == NULL)
    {
        printf("\nMemory allocation not successful. Aborting.");
        exit(1);
    }

    q->list = (struct linkedList*) malloc(sizeof(struct linkedList));
    if(q->list == NULL)
    {
        printf("\nMemory allocation not successful. Aborting.");
        exit(1);
    }

    q->list->first = NULL;
    q->list->count = 0;
    q->list->last = NULL;

    return q;
}

int isEmpty(Queue* q)
{
    if(q->list->count == 0)
        return 1;
    return 0;
}

Queue* delQ(Queue* q)
{
    deleteFirst(q->list);
    return q;
}

Queue* addQ(Queue* q, Element e)
{
    insertLast(q->list, e);
    return q;
}

Element front(Queue* q)
{
    return q->list->first->element;
}   

int lengthQ(Queue* q)
{
    return q->list->count;
}