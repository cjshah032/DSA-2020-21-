#pragma once
#include<stdio.h>
#include<stdlib.h>


typedef struct {
    int empID;
    char name[10];
} record;

record* readRecords(char* filename, int n);
void printRecords(record list[], int n);
void printRecordsinFile(record list[], int n, char* filename);