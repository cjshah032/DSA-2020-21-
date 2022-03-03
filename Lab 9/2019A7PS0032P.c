#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <string.h>

/////// #defines used in the exercise:
#define b_size 5303         // optimal base size
#define t_size 5000         // optimal table size
#define string_size 60  // assume a maximum length 60 of valid strings to be stored
/////////////////////////////////////////////////////




////// structs, typedef and global variabes used:
const int base[3][6] = {{5303, 6997, 8779, 5047411, 5047747, 5047921}, {89431, 90011, 99991, 67883117, 67893841, 67897157}, {792983, 811259, 825203, 512928517, 512929789, 512942281}};
const int table[3] = {5000, 50000, 500000}; // used for profiling function

typedef struct node {   
    int index;      // index in "book" array with the first instance of that string
    int count;      // total count of the string inserted in the hash table
    struct node* next;
} hashnode;         // node used for separate chaining in hashtable

typedef struct hashtable {
    int elementCount;   // total elements inserted in the hash table
    int insertionCost;  // total cost of inserting all elements present in the table
    int queryingCost;   // total cost of querying till now
    hashnode* table[t_size];    // hardcoded optimal value after running profiling function
} hashtable;        // struct of hashtable
//////////////////////////////////////////////////////




//////  functions used: 
int valid_string(char* s)   //checks if a sequence of characters is valid string
{
    int len = strlen(s);
    for(int i=0; i<len; i++)
    {
        if(s[i] < 'A' || (s[i] > 'Z' && s[i] < 'a') || s[i] > 'z')  // checking if any character is not in the english letter.
            return 0;                                               // direct checking with ascii values is possible, because 
    }                                                               // the binary code for english letters is same in UTF-8
    return 1;
}


char** parsing(char* filename, int* count_words)    // taking count_words as a paramter so it can be easily used in main
{
    assert(*count_words == 0);
    FILE* fptr = fopen(filename, "r");
    while(!feof(fptr))
    {
        char s[string_size];
        fscanf(fptr, "%s", s);
        if(valid_string(s) == 1)
            (*count_words) ++;
    }
    fclose(fptr);
    printf("The number of valid strings is %d\n", (*count_words));
    
    char** book = (char**) malloc((*count_words) * sizeof(char*));
    int i=0;

    // we are making two traversals - one for counting strings and another for 
    // storing them as repeated realloc would be costly. 
    // also the technique to realloc to twice the size will also result in wastage
    // of memory, so best method would be to know size beforehand and 
    // traverse the array on it.
    fptr = fopen(filename, "r");
    while(!feof(fptr))
    {
        char s[string_size];
        fscanf(fptr, "%s", s);
        if(valid_string(s) == 1)
        {
            char* sv = (char*) malloc(strlen(s) * sizeof(char));
            strcpy(sv, s);
            book[i++] = sv;
        }
    }

    fclose(fptr);
    return book;
}


int hash(char* str, int baseNumber, int tableSize)  // hashing function
{
    int sum = 0;
    for(int i=0; i<strlen(str); i++)
        sum += (int)str[i];

    return ((sum%baseNumber)%tableSize);
}

int count_collisions(char** str_array, int array_size, int baseNumber, int tableSize)   // function to count collisions
{
    int* count = (int*) malloc(tableSize*sizeof(int));                              // maintain a table of count to find
    for(int i=0; i<tableSize; i++)                                                  // number of strings with same hash value
        count[i] = 0;                                                               // for each distinct hash value possible
    
    for(int i=0; i<array_size; i++)     
        count[hash(str_array[i], baseNumber, tableSize)] ++;
    
    int collisions = 0;
    for(int i=0; i<tableSize; i++)                                                  // collision occurs when string with hash which 
    {                                                                               // is already present is added to the table
        collisions += (count[i] > 1 ? count[i]-1 : 0);                              // thus if n strings have same hash value, n-1
        printf("%d ", count[i]);                                                    // strings will collide with the first string added.
    }                                                                               // Hence collisions for that hash value = n-1
        
    free(count);
    return collisions;
}

void profiling(char** book, int book_size, int* b_index, int* t_index)      // function used to find optimal baseNumber and tableSize 
{   // index variables are taken as input variables and modified, so they can be used conveniently in main
    *t_index = 0;
    *b_index = 0;
    int bestColCount = INT_MAX;
 
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<6; j++)
        {
            int colCount = count_collisions(book, book_size, base[i][j], table[i]);
            if(colCount < bestColCount)
            {
                *t_index = i;
                *b_index = j;
                bestColCount = colCount;
            }
            printf("Collision Count for baseNumber = %d and tableSize = %d is %d\n", base[i][j], table[i], colCount);
        }
    }

    printf("Indexes for best collision count in base array = %d & table array = %d\n", *b_index, *t_index);
}

hashtable* createTable()                // creates and initializes a new table
{
    hashtable* tab = (hashtable*) malloc(sizeof(hashtable));
    tab->elementCount = 0;
    tab->insertionCost = 0;
    tab->queryingCost = 0;
    for(int i=0; i<t_size; i++)
        tab->table[i] = NULL;           
    return tab;
}

void insertInTable(hashtable* tab, char** str_array, int index)     // insert string at str_array[index] into the hashtable
{
    int h = hash(str_array[index], b_size, t_size);                 // in effect, only the index of the first occurence of 
                                                                    // string in the str_array is stored, along with the
                                                                    // count of how many times the same string has been inserted 
    if(tab->table[h] == NULL)                                       // in the hash table
    {
        hashnode* n = (hashnode*) malloc(sizeof(hashnode));         // stored using separate chaining. 
        n->index = index;
        n->count = 1;                                               
        n->next = NULL;
        tab->table[h] = n;
    }

    else {
        hashnode* curr = tab->table[h];
        while(curr -> next != NULL && strcmp(str_array[curr->index], str_array[index]))
        {                                                           // traverse till the last node is encountered or the string matches 
            curr = curr->next;                                      // with already stored string
            tab->insertionCost ++;                                  // insertion cost = number of traversals
        }

        if(strcmp(str_array[curr->index], str_array[index]))        // case where the last node is reached and we need to 
        {                                                           // add to the end of the list
            hashnode* n = (hashnode*) malloc(sizeof(hashnode));
            n->index = index;
            n->count = 1;
            n->next = NULL;
            curr->next = n;
        }

        else {                                                      // an already stored string is found matching
            curr->count ++;
        }
        tab->insertionCost ++;                                      // incrementing because the last traversal is not recorded 
    }                                                               // inside the loop
    tab->elementCount ++;
}

int insertAll(hashtable* tab, char** book, int book_size)           // inserts all strings from "book" array into empty hash table
{
    assert(tab->elementCount == 0);
    for(int i=0; i<book_size; i++)
        insertInTable(tab, book, i);
    return tab->insertionCost;
}

hashnode* lookupTable(hashtable* tab, char** str_array, char* str)   // looks up a string and returns its records
{
    int h = hash(str, b_size, t_size);
    hashnode* rnode = tab->table[h];
    while(rnode != NULL && strcmp(str_array[rnode->index], str))     // if found, the hashnode containing information is returned
    {                                                                // else null is returned
        rnode = rnode->next;
        tab->queryingCost ++;
    }
    tab->queryingCost ++;

    return rnode;
}

int lookupAll(hashtable* tab, char** str_array, char** lookuparray, float m, int lookup_array_size) // looks up first m fraction 
{                                                                                                   // of total strings in the lookuparray
    tab->queryingCost = 0;                                                                          // from the hash table 
    int lookuptill = (int)(m*(float)lookup_array_size);                                             // and returns total cost of querying
    assert(lookuptill <= lookup_array_size);
    for(int i=0; i<lookuptill; i++)
        lookupTable(tab, str_array, lookuparray[i]);
    return tab->queryingCost;
}

void cleanupTable(hashtable* tab)                           // cleans up the table and frees allocated memory
{
    for(int i=0; i<t_size; i++)
    {
        hashnode* curr = tab->table[i];
        hashnode* prev;
        while(curr != NULL)
        {
            prev = curr;
            curr = curr->next;
            free(prev);
        }
    }

    free(tab);
}


/////// driver function:    
int main()
{
    int c = 0;
    char** s = parsing("aliceinwonderland.txt", &c);

    /* 
        int t, b;
        profiling(s, c, &t, &b);    
    */  // dummy used for calcuating optimal values

    hashtable* tab = createTable();
    int iCost = insertAll(tab, s, c);
    printf("Insertion Cost: %d\n", iCost);
    int lCost = lookupAll(tab, s, s, 0.50f, c);
    printf("Lookup Cost: %d\n", lCost);
    cleanupTable(tab);
    return 0;
}