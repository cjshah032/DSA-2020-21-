#pragma once
#include<stdio.h>
#include<assert.h>
#include<stdlib.h>

typedef struct node{
    int val;
    struct node* next;
} node;

typedef struct stack{
    node* top;
} stack;

stack* createStack();

void push(stack* s, int val);

int pop(stack* s);

int isEmpty(stack* s);
