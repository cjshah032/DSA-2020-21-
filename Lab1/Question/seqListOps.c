/***********file:   Ops.c *********/
#include <stdio.h>

#include "storage.h"
#include "compare.h"
int nextfreeloc = 0;
Store st;

SeqList createlist()
{
 SeqList sl;
 sl.head = nextfreeloc++;
 sl.size = 0;
 st[sl.head].next = -1;
 return (sl);
}

void printJob (Job j)
{
printf ("JOB ID = %d, Priority = %d, Arr time = %d, Arrival time = %d \n",j.id,j.pri,j.et,j.at);
}


int initialize_elements (JobList list)
{
 int i; int size;

 printf("\n Enter the Number of Jobs :");
 scanf("%d", &size);

 for (i=0;i<size;i++)
 {
  printf ("\nEnter job ID");
  scanf ("%d",&list[i].id);
  printf ("Enter Priority (from 0 - 2)");
  scanf ("%d",&list[i].pri);
  printf ("Execution Time");
  scanf ("%d",&list[i].et);
  printf ("Arrival Time");
  scanf ("%d",&list[i].at);
 }
 return size;
}

SeqList insert(Job j , SeqList sl)
{
    //Implement this function//
    if(sl.size == 0)
    {
        st[sl.head].ele = j;
    }
    
    else {
        st[nextfreeloc].ele = j;
        int next = sl.head;
        int curr = -1;
        while(next != -1 && compare(st[next].ele, j) == LESSER)
        {
            curr = next;
            next = st[next].next;
        }

        if(next == -1)
        {
            st[curr].next = nextfreeloc;
            st[nextfreeloc].next = -1;
        }

        else if (curr == -1)
        {
            st[nextfreeloc].next = sl.head;
            sl.head = nextfreeloc;
        }

        else {
            st[curr].next = nextfreeloc;
            st[nextfreeloc].next = next;
        }
        nextfreeloc ++;
    }
    sl.size ++;

    return sl;
}
  
void insertelements (JobList list , int size, SeqList s[3])
{
    // Implement this function
    for(int i=0; i<size; i++)
    {
        switch(list[i].pri)
        {
            case PRI_0:
                s[0] = insert(list[i], s[0]);
                break;
            case PRI_1:
                s[1] = insert(list[i], s[1]);
                break;
            case PRI_2:
                s[2] = insert(list[i], s[2]);
        }
    }
}

void copy_sorted_ele(SeqList s[3] , JobList ele)
{
    // Implement this function
    int j = 0;
    for(int i=2; i>-1; i--)
    {
        if(s[i].size == 0)
            continue;
        int next = s[i].head;
        while(next != -1)
        {
            ele[j++] = st[next].ele;
            next = st[next].next;
        }
    }
}

void printlist(SeqList sl)
{
    // Implement this function
    if(sl.size == 0)
        return;
    int next = sl.head;
    while(next != -1)
    {
        printJob(st[next].ele);
        next = st[next].next;
    }
}

void printJobList(JobList list, int size)
{
    // Implement this function
    for(int i=0; i<size; i++)
    {
        printJob(list[i]);
    }

}

void sortJobList(JobList list, int size)
{
 SeqList seq[3];
 seq[0] = createlist();
 seq[1] = createlist();
 seq[2] = createlist();
 insertelements (list, size, seq);
 printlist(seq[0]);   
 printlist(seq[1]);
 printlist(seq[2]);
 copy_sorted_ele (seq , list); 
}
