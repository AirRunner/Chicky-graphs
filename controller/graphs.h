#ifndef GRAPHS_H
#define GRAPHS_H

#include "../rendering/renderingSLL.h"

typedef struct edge {
    int dest;
    int weight;
    struct edge* next;
} Edge;

typedef struct node {
    int data;
    struct edge* list;
} Node;

typedef struct graphElt {
    Node* node; // Node for the controller
    NodeSDL* nodeSDL; // Node for the rendering
} GraphElt;

typedef struct graph { 
    int size;
    int directed; // 0 for undirected and 1 for directed
    GraphElt** array;
} Graph;

Graph* createGraph(int size, int directed);
void createNode(Graph* graph, int data, NodeSDL** nodes, SDL_Texture* tex);
Edge* createEdge(int dest, int weight);

void addEdge(Graph* graph, int src, int dest, int weight, EdgeSDL** edges, SDL_Texture* texArrow);

void deleteEdge(Graph* graph, int src, int dest, EdgeSDL** edges);
void deleteNode(Graph* graph, int id, NodeSDL** nodes, EdgeSDL** edges);

void printGraph(Graph* graph);
void printNodes(Graph* graph);

void contamination(Graph* graph, NodeSDL** nodes, EdgeSDL** edges);
int isGraphEmpty(Graph* graph);

#endif