#include "parsing.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#define string_size 60  // assume a maximum length 50 of valid strings.

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


///for debugging purposes
// int main()
// {
//     int c = 0;
//     char** s = parsing("aliceinwonderland.txt", &c);
//     FILE* f = fopen("new.txt", "w");
//     assert(f != NULL);
//     printf("%d", c);
//     for(int i=0; i<c; i++)
//     {
//         fprintf(f, "%s\n", s[i]);
//         free(s[i]);
//     }

//     free(s);
//     fclose(f);
// }