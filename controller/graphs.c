#include <stdio.h>
#include <stdlib.h>
#include "graphs.h"

Edge* createEdge(int dest, int weight) {
    Edge* newEdge = malloc(sizeof(Edge));
    newEdge->dest = dest;
    newEdge->weight = weight;
    newEdge->next = NULL;
    return newEdge;
}

Graph* createGraph(int size, char directed) { 
    Graph* graph = malloc(sizeof(Graph)); 
    graph->size = size;
    graph->directed = directed;

    graph->array = malloc(size * sizeof(Node*)); 
    for(int i = 0; i < size; i++) {
        graph->array[i] = NULL;
    }
    return graph;
}

void addEdge(Graph* graph, int src, int dest, int weight) { 
    /* Add an edge from src to dest. A new node is 
    added to the adjacency list of src. The node 
    is added at the begining */
    Edge* newEdge = createEdge(dest, weight);
    newEdge->next = graph->array[src]->list;
    graph->array[src]->list = newEdge;

    if(!graph->directed){
        // If graph is undirected, add an edge from dest to src also
        newEdge = createEdge(src, weight); 
        newEdge->next = graph->array[dest]->list; 
        graph->array[dest]->list = newEdge;
    }
}

void deleteEdge(Graph* graph, int src, int dest) {
    if(graph->array[src] != NULL){
        Edge* edge = graph->array[src]->list;
        Edge* prev = NULL;
        if(edge != NULL){
            if(edge->dest == dest){
                graph->array[src]->list = graph->array[src]->list->next;
                free(edge);
            }
            else{
                while(edge->dest != dest && edge->next != NULL){
                    prev = edge;
                    edge = edge->next;
                }
                if(edge->dest == dest){
                    prev->next = edge->next;
                    free(edge);
                }
            }
        }
    }
}

void createNode(Graph* graph, int data) {
    int i = 0;
    while(graph->array[i] != NULL && i < graph->size)
        i++;
    if(i == graph->size)
        printf("Maximum number of nodes reached");
    else{
        graph->array[i] = malloc(sizeof(Node*));
        graph->array[i]->data = data;
        graph->array[i]->list = NULL;
    }
}

void deleteNode(Graph* graph, int id) {
    Edge* tmp;
    while(graph->array[id]->list != NULL) {
       tmp = graph->array[id]->list;
       graph->array[id]->list = graph->array[id]->list->next;
       tmp->next = NULL;
       free(tmp);
    }

    free(graph->array[id]);
    graph->array[id] = NULL;

    for(int i = 0; i < graph->size; i++){
        deleteEdge(graph, i, id);
    }
}

// Print the adjacency list, representation of graph
void printGraph(Graph* graph) {
    for(int i = 0; i < graph->size; i++) {
        if(graph->array[i] != NULL){
            Edge* pCrawl = graph->array[i]->list;
            printf("\n Adjacency list of vertex %d\n ", i);
            while(pCrawl) {
                printf("-> %d", pCrawl->dest);
                pCrawl = pCrawl->next;
            }
        }
        printf("\n");
    }
}

void printNodes(Graph* graph) {
    for(int i = 0; i < graph->size; i++) {
        if(graph->array[i] != NULL){
            printf("\nNode %d: ", i);
            if(graph->array[i]->data)
                printf("infected");
            else
                printf("not infected");
        }
    }
    printf("\n");
}

void contamination(Graph* graph) {
    int i = 0;
    for(i = 0; i < graph->size; i++){
        if(graph->array[i] != NULL && graph->array[i]->data == 1){
            Edge* edge = graph->array[i]->list;
            while(edge){
                if(graph->array[edge->dest]->data != 1)
                    graph->array[edge->dest]->data = 2;
                edge = edge->next;
            }
        }
    }

    for(i = 0; i < graph->size; i++){
        if(graph->array[i] != NULL){
            if(graph->array[i]->data == 1)
                deleteNode(graph, i);
            else if(graph->array[i]->data == 2)
                graph->array[i]->data = 1;
        }
    }
}

int isEmpty(Graph* graph) {
    int empty = 1;
    for(int i = 0; i < graph->size; i++){
        if(graph->array[i] != NULL)
            empty = 0;
    }
    return empty;
}

int main() {
    Graph* graph = createGraph(5, 0);

    createNode(graph, 1);
    createNode(graph, 0);
    createNode(graph, 0);
    createNode(graph, 0);
    createNode(graph, 0);
    createNode(graph, 0);

    addEdge(graph, 0, 1, 1);
    addEdge(graph, 0, 4, 1);
    addEdge(graph, 1, 2, 1);
    addEdge(graph, 1, 3, 1);
    addEdge(graph, 1, 4, 1);
    addEdge(graph, 2, 3, 1);
    addEdge(graph, 3, 4, 1);

    // Contamination
    while(!isEmpty(graph)){
        printGraph(graph);
        printNodes(graph);
    
        contamination(graph);
    
        printNodes(graph);
    }
    
    system("pause");
    return 0;
}