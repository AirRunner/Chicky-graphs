#ifndef GRAPHS_H
#define GRAPHS_H

#include "../rendering/renderingSLL.h"

typedef struct edge {
    int dest;
    int weight;
    struct edge* next;
} Edge;

typedef struct node {
    int data; // 0 for basic and 1 for infected
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
void createNode(Graph* graph, int data, NodeSDL** nodes, SDL_Rect* destRect, SDL_Texture* tex);
Edge* createEdge(int dest, int weight);

void addEdge(Graph* graph, int src, int dest, int weight, EdgeSDL** edges, SDL_Texture* texArrow);

void deleteEdge(Graph* graph, int src, int dest, EdgeSDL** edges);
void deleteNode(Graph* graph, int id, NodeSDL** nodes, EdgeSDL** edges);
void deleteGraph(Graph** graph, NodeSDL** nodes, EdgeSDL** edges);

int checkEdge(Graph* graph, int src, int dest);
int searchNode(Graph* graph, SDL_Rect* Rect);

void printID(Game* game);
void printGraph(Graph* graph);

void contamination(Graph* graph, NodeSDL** nodes, EdgeSDL** edges, NodeTree* texTree);
int isGraphEmpty(Graph* graph);

#endif
