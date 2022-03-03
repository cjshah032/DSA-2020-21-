#include<stdio.h>
#include<stdlib.h>

int main()  //FILE I/O PROGRAM
{
    FILE* fr = fopen("input.txt", "r");
    FILE* fw = fopen("output.txt", "w");

    if(fr == NULL)
    {
        printf("Input file could not be opened! Aborting...\n");
        exit(1);
    }

    if(fw == NULL)
    {
        printf("Output file could not be opened! Aborting...\n");
        exit(1);
    }

    char c;
    while ((c = fgetc(fr)) != EOF)
    {
        fprintf(fw, "%c", c);
    }
    
    fclose(fr);
    fclose(fw);

    return 0;
}