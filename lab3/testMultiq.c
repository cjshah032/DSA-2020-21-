#include "multiq.h"

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/time.h>

MultiQ* loadData(FILE* f)
{
    if(f == NULL)
    {
        printf("\nUnable to open file");
        exit(1);
    }

    MultiQ* mq = createMQ(10);

    while (!feof(f))
    {
        char line[20];
        fgets(line, sizeof(line), f);
        char idc[20];
        int i = 0;
        while(line[i] != ',')
        {
            // printf("%c", line[i]);
            idc[i] = line[i];
            i++;
        }
        idc[++i] = '\0';
        // printf("\n%c", line[i]);
        char priorc[3] = {line[i], line[i+1], '\0'};
        int id = atoi(idc);
        int p = atoi(priorc);

        Task t; t.id = id; t.p = p;
        addMQ(mq, t);
    }

    return mq;
}

MultiQ* testDel(int num, MultiQ* mq)
{
    for(int i=0; i<num; i++)
    {
        /* Uncomment for testing */ 
        // Task t = nextMQ(mq);
        // printf("%d %d\n", t.id, t.p);   
        mq = delNextMQ(mq);
    }

    return mq;
}

int main(int argc, char** argv)
{
    FILE * f = fopen(argv[1], "r");

    /* Uncomment for speed test */
    // struct timeval t1, t2;
    // gettimeofday(&t1, NULL);
    MultiQ* mq = loadData(f);
    fclose(f);

    const int num = 10000; //change according to file being used for testing
    mq = testDel(num, mq);

    // gettimeofday(&t2, NULL);
    // double ti = (t2.tv_sec - t1.tv_sec)*1000;
    // ti += ((t2.tv_usec - t1.tv_usec)/1000); 

    // printf("%.10f", ti);

    //average time for input10000.txt file is 3 ms.
    return 0;
}