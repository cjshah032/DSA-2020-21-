#include "readFile.h"
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>

record* readFileForRecords(char* filename)
{
    int ar_size = 10;
    record* arr = (record*) malloc(ar_size*(sizeof(record)));
    if(arr == NULL)
    {
        printf("Could not reallocate more space\n");
        exit(1);
    }

    FILE* fptr = fopen(filename, "r");
    if(fptr == NULL)
    {
        printf("Could not open file %s\n", filename);
        exit(1);
    }

    int itr = 0;
    char line[200]; 
    while (fgets(line, 200, fptr) != NULL)  //getting whole line at input and then parsing and storing accordingly
    {
        int i = 1;
        char c_num[17];
        for(; i<17; i++)
            c_num[i-1] = line[i];
        c_num[i-1] = '\0';
        i++;
        arr[itr].card_number = atoll(c_num);
        for(; i<23; i++)
            arr[itr].bank_code[i-18] = line[i];
        i++;
        char m[3], y[5];
        for(; i<26; i++)
            m[i-24] = line[i];
        m[i-24] = '\0';
        i++;
        for(; i<31; i++)
            y[i-27] = line[i];
        y[i-27] = '\0';
        i++;
        arr[itr].expiry_month = atoi(m);
        arr[itr].expiry_year = atoi(y);
        while(line[i] != ',')
        {
            arr[itr].first_name[i-32] = line[i];
            i++;
        }
        i++; int j = i;
        while(line[i] != '"')
        {
            arr[itr].last_name[i-j] = line[i];
            i++;
        }
        itr++;
        if(feof(fptr))
            break;
        if(itr == ar_size)  //when array becomes full we reallocate some more space to store more elements
        {
            ar_size *= 2;
            arr = (record*) realloc(arr, ar_size*(sizeof(record)));
            if(arr == NULL)
            {
                printf("Could not reallocate more space\n");
                exit(1);
            }
        }
    }
    fclose(fptr);
    return arr;
}

//// Testing for Exercise 1 ////
// int main(int argc, char** argv)
// {
//     // printf("%d\n", sizeof(long long int));
//     char* filename = argv[1];
//     struct timeval t1, t2;
//     gettimeofday(&t1, NULL);
//     for(int i=0; i<100; i++) //concatenating files to test for larger inputs
//     {
//         record* rs = readFileForRecords(filename);
//     }    
    
//     gettimeofday(&t2, NULL);
//     double ti = (t2.tv_sec - t1.tv_sec)*1000;
//     ti += ((t2.tv_usec - t1.tv_usec)/1000); 

//     printf("%.10f", ti);

//     // printf("%d", sizeof(rs)/sizeof(record));
//     return 0;
// }