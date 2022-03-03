#include <stdio.h>
// structure definitions
// structure of a linked list node. It contains an element
typedef int Element;

struct node {
    Element element;
    struct node * next;
};

/* structure of a linked list / head. It stores the count of number of elements
in the list and also a pointer link to the first node of the list. */
struct linkedList {
    int count;
    struct node * first;
    struct node * last;
};


// function declarations
void insertFirst (struct linkedList * head, Element ele);
/* inserts a given element at the beginning of the list */

Element deleteFirst(struct linkedList *head);
/* deletes the first element of the list and returns pointer to the deleted
node. */

void printList (struct linkedList * head);
/* prints all the elements in the list */

int search (struct linkedList * head, Element ele);
/* searches for a given element in the linked list. Returns 1 if found, 0
otherwise. */

Element delete (struct linkedList * head, Element ele);
/* deletes the first node in the list that contains the element = ele and
retuns it. If the element is not found it returns an error message saying
element not found. */

void insertLast(struct linkedList* head, Element ele);
//inserts at the last. imlemented for queue structure