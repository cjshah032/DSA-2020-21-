#include "multiq.h" 

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

MultiQ* createMQ(int num)
{
    MultiQ* mq = (MultiQ *) malloc(sizeof(MultiQ));
    mq->arr = (Queue**) malloc(num* sizeof(Queue*));
    mq->num = num;
    for(int i=0; i<num; i++)
        mq->arr[i] = newQ();
    return mq;
}

MultiQ* addMQ(MultiQ* mq, Task t)
{
    int prior = t.p;
    assert(prior > 0 && prior <= mq->num);

    mq->arr[prior-1] = addQ(mq->arr[prior-1], t.id);
    return mq;
}


//assumption: Numerically greater has higher priority. In this case, 10 is highest.
Task nextMQ(MultiQ* mq)
{
    for(int i=mq->num-1; i>=0; i--)
    {
        if(isEmpty(mq->arr[i]) == 0)
        {
            Task t;
            t.id = front(mq->arr[i]);
            t.p = i+1;

            return t;
        }
    }

    printf("\nAll lists are empty!");
    exit(1);
}

MultiQ* delNextMQ(MultiQ* mq)
{
    for(int i=mq->num-1; i>=0; i--)
    {
        if(!isEmpty(mq->arr[i]))
        {
            mq->arr[i] = delQ(mq->arr[i]);
            return mq;
        }
    }

    printf("\nMultiQ is empty!");
}

int isEmptyMQ(MultiQ* mq)
{
    for(int i=0; i<mq->num; i++)
    {
        if(isEmpty(mq->arr[i]) == 0)
            return 0;
    }

    return 1;
}

int sizeMQ(MultiQ* mq)
{
    int size = 0;
    for(int i=0; i<mq->num; i++)
    {
        if(isEmpty(mq->arr[i]) == 0)
            size += lengthQ(mq->arr[i]);
    }

    return size;
}

int sizeMQbyPriority(MultiQ* mq, Priority p)
{
    int prior = p;
    assert(prior > 0 && prior <= mq->num);

    if(isEmpty(mq->arr[p-1]) == 1)
        return 0;
    return lengthQ(mq->arr[p-1]);
}

Queue* getQueueFromMQ(MultiQ* mq, Priority p)
{
    int prior = p;
    assert(prior > 0 && prior <= mq->num);

    return mq->arr[p-1];
}