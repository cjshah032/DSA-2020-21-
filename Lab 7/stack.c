#include"stack.h"

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