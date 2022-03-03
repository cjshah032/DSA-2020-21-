#pragma once

#define b_size 5303
#define t_size 5000

typedef struct node {
    int index;
    int count;
    struct node* next;
} hashnode;

typedef struct hashtable {
    int elementCount;
    int insertionCost;
    int queryingCost;
    hashnode* table[t_size];
} hashtable;

hashtable* createTable();

void insertInTable(hashtable* tab, char** str_array, int index);

int insertAll(hashtable* tab, char** book_array, int book_size);

hashnode* lookupTable(hashtable* tab, char** str_array, char* str);

int lookupAll(hashtable* tab, char** str_array, char** lookuparray, float m, int lookup_array_size);

void cleanupTable(hashtable* tab);
