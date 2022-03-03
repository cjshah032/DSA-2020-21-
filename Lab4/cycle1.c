#include "cycle.h"
#include <assert.h>

int testCycle(struct linkedList* list)
{
    assert(list != NULL);
    struct node * tort = list->first;
    struct node * hare = list->first->next;
    assert(hare != tort && hare != NULL);  //node cannot loop itself

    while(hare->next != tort && hare != tort)
    {
        tort = tort->next;
        if(tort == NULL)
            return 0;
        hare = hare->next;
        if(hare == NULL)
            return 0;
        hare = hare->next;
        if(hare == NULL)
            return 0;
    }
    return 1;
}