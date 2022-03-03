
#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

struct _node
{
    unsigned int id;
    struct _node *next;
};

typedef struct _node* node;

struct _Graph
{
    node list;
    int *wt;
    bool *visited;
    int vcount;
    int ecount;
};

typedef struct _Graph* Graph;

Graph initGraph(int N);
void printAdjacencyList(Graph g);
void insertEdge(Graph g, unsigned int u, unsigned int v);
void bestFirstTraverse(Graph g);
#endif // GRAPH_H_INCLUDED
