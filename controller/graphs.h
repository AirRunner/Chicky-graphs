#ifndef GRAPHS_H
#define GRAPHS_H

typedef struct edge {
    int dest;
    int weight;
    struct edge* next;
} Edge;

typedef struct node {
    int data;
    struct edge* list;
} Node;

typedef struct graph { 
    int size;
    Node** array;
} Graph;

Graph* createGraph(int size);
void createNode(Graph* graph, int data);
Edge* createEdge(int dest, int weight);

void addEdge(Graph* graph, int src, int dest, int weight);

void deleteEdge(Graph* graph, int src, int dest);
void deleteNode(Graph* graph, int id);

void printGraph(Graph* graph);
void printNodes(Graph* graph);

void contamination(Graph* graph);
int isEmpty(Graph* graph);

#endif