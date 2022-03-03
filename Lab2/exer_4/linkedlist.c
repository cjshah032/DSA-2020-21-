#include "linkedlist.h"
#include <stdlib.h>

void insertFirst (struct linkedList * head, int ele)
{
    struct node *link = (struct node*) malloc (sizeof(struct node));
    if(link == NULL)
    {
        printf("\nPointer allocation not possible.");
        exit(1);
    }

    link->element = ele;
    if(head->count == 0)
        link->next = NULL;
    else link->next = head->first;
    head->first = link;
    head->count++;
}

int deleteFirst(struct linkedList *head)
{
    if(head->count == 0)
    {
        printf("\nList is empty");
        exit(1);
    }

    struct node* curr = head->first;
    head->first = head->first->next;
    int r = curr->element;
    free(curr);
    head->count --;
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

int search (struct linkedList * head, int ele)
{
    if(head->count == 0)
        return 0;
    struct node* curr = head->first;
    while(curr != NULL)
    {
        if(curr->element == ele)
            return 1;
        curr = curr->next;
    }

    return 0;
}

int delete (struct linkedList * head, int ele)
{
    struct node* curr = head->first;
    struct node* prev;
    while(curr != NULL && curr->element != ele)
    {   
        prev = curr;
        curr = curr->next;
    }

    if(curr == NULL)
    {
        printf("\nElement not found");
        exit(1);
    }

    int rval = curr->element;
    prev->next = curr->next;
    free(curr);
    head->count --;

    return rval;
}

