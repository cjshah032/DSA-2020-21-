/** Lab Assignment  **/

#include "stack.h"

stack* createStack()
{
    stack* top = (stack*) malloc(sizeof(stack));
    if(top)
    {
        top->head = (struct linkedList*) malloc(sizeof(struct linkedList));
        top->head->first = NULL;
        top->head->count = 0;
        return top;
    }

    printf("\nStack could not be initialized");
    exit(1);
}

int peek(stack* top)
{
    if(top->head->count == 0)
    {
        printf("\nStack is empty!");
        exit(1);
    }

    return top->head->first->element;
}

void push(stack* top, int ele)
{
    insertFirst(top->head, ele);
}

int pop(stack* top)
{
    return deleteFirst(top->head);
}

int isEmpty(stack* top)
{
    if(top->head->count == 0)
        return 1;
    return 0;
}