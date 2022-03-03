#include<stdio.h>

typedef struct record {
    unsigned long long int card_number;
    char bank_code[5];
    int expiry_month;
    int expiry_year;
    char first_name[10];
    char last_name[10];
} record;

record* readFileForRecords(char* filename);