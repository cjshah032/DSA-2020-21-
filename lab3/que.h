#include "linkedlist.h"

typedef struct {
    struct linkedList* list;
} Queue;

Queue* newQ(); //initializes and returns new queue

int isEmpty(Queue* q); //returns 1 if q is empty, or 0 if not

Queue* delQ(Queue* q); //deletes the front element and returns the modified queue

Element front(Queue* q); //returns first element

Queue* addQ(Queue* q, Element e); //adds element to front and returns modified queue

int lengthQ(Queue* q); // returns length
