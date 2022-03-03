#include "linkedlist.h"
#include <stdlib.h>
#include <assert.h>

void insertFirst (struct linkedList * head, Element ele)
{
    struct node *link = (struct node*) malloc (sizeof(struct node));
    if(link == NULL)
    {
        printf("\nPointer allocation not possible.");
        exit(1);
    }

    link->element = ele;
    if(head->count == 0)
    {
        link->next = NULL;
        head->last = link;
    }    
    else link->next = head->first;
    head->first = link;
    head->count++;
}

Element deleteFirst(struct linkedList *head)
{
    if(head->count == 0)
    {
        printf("\nList is empty");
        exit(1);
    }

    struct node* curr = head->first;
    head->first = head->first->next;
    Element r = curr->element;
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

int search (struct linkedList * head, Element ele)
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

Element delete (struct linkedList * head, Element ele)
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

    Element rval = curr->element;
    prev->next = curr->next;
    if(curr == head->last)
        head->last = prev;
    free(curr);
    head->count --;

    return rval;
}

void insertLast(struct linkedList* head, Element ele)
{
    struct node *link = (struct node*) malloc (sizeof(struct node));
    if(link == NULL)
    {
        printf("\nPointer allocation not possible.");
        exit(1);
    }

    link->element = ele;
    link->next = NULL;

    if(head->last != NULL)
        head->last->next = link;

    head->last = link;
    if(head->count == 0)
        head->first = link;
    head->count ++;
}

