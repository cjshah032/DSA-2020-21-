#include "records.h"

record* readRecords(char* filename, int n)
{
    record* list = (record*) malloc(n*sizeof(record));
    FILE* fp = fopen(filename, "r");
    for(int i=0; i<n && !feof(fp); i++)
    {
        fscanf(fp, "%s %d", &list[i].name, &list[i].empID);
    }

    fclose(fp);
    return list;
}

void printRecords(record list[], int n)
{
    for(int i=0; i<n; i++)
        printf("%s %d\n", list[i].name, list[i].empID);
}

void printRecordsinFile(record list[], int n, char* filename)
{
    FILE* fp = fopen(filename, "w");
    for(int i=0; i<n; i++)
        fprintf(fp, "%s %d\n", list[i].name, list[i].empID);
    fclose(fp);
}