#include"que.h"

typedef int Priority;

typedef struct 
{
    Element id;
    Priority p;
} Task;

typedef struct {
    Queue** arr;
    int num;
} MultiQ;

MultiQ* createMQ(int num); //creates and returns a multiQ with num no. of queues in an array

MultiQ* addMQ(MultiQ* mq, Task t); //adds task to the MQ and returns the modified MQ

Task nextMQ(MultiQ* mq); // returns the front of the non-empty Queue in mq with the highest priority.

MultiQ* delNextMQ(MultiQ* mq); // deletes the front of the non-empty Queue in mq with the highest priority; returns the modified MultiQ

int isEmptyMQ(MultiQ* mq); // tests whether all the Queues in mq are empty (1 = empty, 0 = not-empty)

int sizeMQ(MultiQ* mq); // returns the total number of items in the MultiQ

int sizeMQbyPriority(MultiQ* mq, Priority p); //returns the number of items in mq with the priority p.

Queue* getQueueFromMQ(MultiQ* mq, Priority p); // returns the Queue with priority p