/** Lab Assignment  **/

#include<stdio.h>
#include<stdlib.h>
#include "linkedlist.h"

typedef struct {
    struct linkedList *head;
} stack;

stack* createStack();
//creates and returns pointer to stack

int peek(stack* top);
//returns the top element in the stack

void push(stack* top, int ele);
//pushes the element in the stack

int pop(stack* top);
//pops from stack and returns the number

int isEmpty(stack* top);
//returns 1 if empty, 0 if not empty