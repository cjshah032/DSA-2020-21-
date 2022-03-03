#include "linkedlist.h"
#include <stdlib.h>

void insertFirst (struct linkedList * head, int ele)
{
    struct node *link = (struct node*) myalloc (sizeof(struct node));
    if(link == NULL)
    {
        printf("\nPointer allocation not possible.");
        exit(1);
    }

    link->element = ele;
    if(head->first == NULL)
        link->next = NULL;
    else link->next = head->first;
    head->first = link;
}

int deleteFirst(struct linkedList *head)
{
    if(head->first == NULL)
    {
        printf("\nList is empty");
        exit(1);
    }

    struct node* curr = head->first;
    head->first = head->first->next;
    int r = curr->element;
    myfree(curr, sizeof(struct node));
    return r;
}

void printList (struct linkedList * head)
{
    struct node* curr = head->first;
    printf("\n[");
    while(curr != NULL)
    {
        printf("%d, ", curr->element);
        curr = curr->next;
    }
    printf("]");
}