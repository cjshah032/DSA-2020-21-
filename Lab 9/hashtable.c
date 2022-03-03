#include "hashtable.h"
#include "parsing.h"
#include "hashing.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

hashtable* createTable()
{
    hashtable* tab = (hashtable*) malloc(sizeof(hashtable));
    tab->elementCount = 0;
    tab->insertionCost = 0;
    tab->queryingCost = 0;
    for(int i=0; i<t_size; i++)
        tab->table[i] = NULL;
    return tab;
}

void insertInTable(hashtable* tab, char** str_array, int index)
{
    int h = hash(str_array[index], b_size, t_size);
    if(h <= 65)
        printf("%d %s\n", index, str_array[index]);
    if(tab->table[h] == NULL)
    {
        hashnode* n = (hashnode*) malloc(sizeof(hashnode));
        n->index = index;
        n->count = 1;
        n->next = NULL;
        tab->table[h] = n;
    }

    else {
        hashnode* curr = tab->table[h];
        while(curr -> next != NULL && strcmp(str_array[curr->index], str_array[index]))
        {
            curr = curr->next;
            tab->insertionCost ++;
        }

        if(strcmp(str_array[curr->index], str_array[index]))
        {
            hashnode* n = (hashnode*) malloc(sizeof(hashnode));
            n->index = index;
            n->count = 1;
            n->next = NULL;
            curr->next = n;
        }

        else {
            curr->count ++;
        }
        tab->insertionCost ++;
    }
    tab->elementCount ++;
}

int insertAll(hashtable* tab, char** book, int book_size)
{
    assert(tab->elementCount == 0);
    for(int i=0; i<book_size; i++)
        insertInTable(tab, book, i);
    return tab->insertionCost;
}

hashnode* lookupTable(hashtable* tab, char** str_array, char* str)
{
    int h = hash(str, b_size, t_size);
    hashnode* rnode = tab->table[h];
    while(rnode != NULL && strcmp(str_array[rnode->index], str))
    {
        rnode = rnode->next;
        tab->queryingCost ++;
    }
    tab->queryingCost ++;

    return rnode;
}

int lookupAll(hashtable* tab, char** str_array, char** lookuparray, float m, int lookup_array_size)
{
    tab->queryingCost = 0;
    int lookuptill = (int)(m*(float)lookup_array_size);
    assert(lookuptill <= lookup_array_size);
    for(int i=0; i<lookuptill; i++)
        lookupTable(tab, str_array, lookuparray[i]);
    return tab->queryingCost;
}

void cleanupTable(hashtable* tab)
{
    for(int i=0; i<t_size; i++)
    {
        // printf("%d ", i);
        hashnode* curr = tab->table[i];
        hashnode* prev;
        while(curr != NULL)
        {
            // printf("%d ", curr->count);
            prev = curr;
            curr = curr->next;
            free(prev);
        }
    }

    free(tab);
}


int main()
{
    int c = 0;
    char** s = parsing("aliceinwonderland.txt", &c);
    hashtable* tab = createTable();
    int iCost = insertAll(tab, s, c);
    printf("Insertion Cost: %d\n", iCost);
    int lCost = lookupAll(tab, s, s, 0.50f, c);
    printf("Lookup Cost: %d\n", lCost);
    cleanupTable(tab);
    return 0;
}