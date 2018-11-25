#include "graphs.h"

Graph* createGraph(int size, int directed) {
    Graph* graph = malloc(sizeof(Graph));
    graph->size = size;
    graph->directed = directed;
    // Initialize the graph with NULL nodes
    graph->array = malloc(size * sizeof(GraphElt*));
    for(int i = 0; i < size; i++) {
        graph->array[i] = NULL;
    }
    return graph;
}

void deleteGraph(Graph** graph, NodeSDL** nodes, EdgeSDL** edges) {
    if(*graph != NULL){
        // Delete all nodes before freeing the graph
        for(int i = 0; i < (*graph)->size; i++){
            if((*graph)->array[i] != NULL){
                deleteNode(*graph, i, nodes, edges);
            }
        }
        free((*graph)->array);
        free(*graph);
        *graph = NULL;
    }
}

// Create a graph with a given destination and weight
Edge* createEdge(int dest, int weight) {
    Edge* newEdge = malloc(sizeof(Edge));
    newEdge->dest = dest;
    newEdge->weight = weight;
    newEdge->next = NULL;
    return newEdge;
}

void addEdge(Graph* graph, int src, int dest, int weight, EdgeSDL** edges, SDL_Texture* texArrow) { 
    /* Add an edge from source to destination. A new node is 
    added to the adjacency list of source. The node is added
    at the begining */
    Edge* newEdge = createEdge(dest, weight);
    newEdge->next = graph->array[src]->node->list;
    graph->array[src]->node->list = newEdge;

    if(!graph->directed){
        /* If graph is undirected, add an edge from destination
        to source also*/
        newEdge = createEdge(src, weight); 
        newEdge->next = graph->array[dest]->node->list; 
        graph->array[dest]->node->list = newEdge;
    }

    addEdgeSDL(graph->directed, edges, graph->array[src]->nodeSDL->destRect, graph->array[dest]->nodeSDL->destRect, texArrow);
}

void deleteEdge(Graph* graph, int src, int dest, EdgeSDL** edges) {
    if(graph->array[src] != NULL){
        Edge* edge = graph->array[src]->node->list;
        Edge* prev = NULL;
        if(edge != NULL){
            if(edge->dest == dest){
                /* Delete the first edge of the adjacency list of source
                if it is the good one to remove*/
                graph->array[src]->node->list = graph->array[src]->node->list->next;
                free(edge);
            }
            else{
                // Loop to find the edge to remove
                while(edge->dest != dest && edge->next != NULL){
                    prev = edge;
                    edge = edge->next;
                }
                if(edge->dest == dest){
                    // Remove the edge if it's found
                    prev->next = edge->next;
                    free(edge);
                }
            }
        }
        removeEdgeSDL(edges, graph->array[src]->nodeSDL->destRect, graph->array[dest]->nodeSDL->destRect);
    }
}

void createNode(Graph* graph, int data, NodeSDL** nodes, SDL_Rect* destRect, SDL_Texture* tex) {
    int i = 0;
    // Search an empty place in the graph's array
    while(graph->array[i] != NULL && i < graph->size)
        i++;
    if(i == graph->size)
        printf("Maximum number of nodes reached");
    else{
        // Add a node at the first empty place if one is found
        graph->array[i] = malloc(sizeof(GraphElt*));
        graph->array[i]->node = malloc(sizeof(Node));
        graph->array[i]->node->data = data;
        graph->array[i]->node->list = NULL;

        graph->array[i]->nodeSDL = addNodeSDL(nodes, destRect, tex);
    }
}

void deleteNode(Graph* graph, int id, NodeSDL** nodes, EdgeSDL** edges) {
    Edge* tmp;
    // Delete all edges starting from the node id
    while(graph->array[id]->node->list != NULL) {
       tmp = graph->array[id]->node->list;
       graph->array[id]->node->list = graph->array[id]->node->list->next;
       tmp->next = NULL;
       free(tmp);
    }
    // Delete all edges having id as destination
    for(int i = 0; i < graph->size; i++){
        deleteEdge(graph, i, id, edges);
    }
    // Delete the node id
    free(graph->array[id]->node);
    graph->array[id]->node = NULL;
    removeNodeSDL(nodes, graph->array[id]->nodeSDL->destRect);
    graph->array[id]->nodeSDL = NULL;
    free(graph->array[id]);
    graph->array[id] = NULL;
}

// Print the adjacency list representation of graph
void printGraph(Graph* graph) {
    for(int i = 0; i < graph->size; i++) {
        if(graph->array[i] != NULL){
            Edge* edge = graph->array[i]->node->list;
            printf("\n Adjacency list of node %d\n ", i);
            // Print all edges starting at the node
            while(edge) {
                printf("-> %d", edge->dest);
                edge = edge->next;
            }
        }
        printf("\n");
    }
}

void printNodes(Graph* graph) {
    for(int i = 0; i < graph->size; i++) {
        if(graph->array[i] != NULL){
            printf("\nNode %d: ", i);
            if(graph->array[i]->node->data)
                printf("infected");
            else
                printf("not infected");
        }
    }
    printf("\n");
}

void contamination(Graph* graph, NodeSDL** nodes, EdgeSDL** edges) {
    int i = 0;
    for(i = 0; i < graph->size; i++){
        if(graph->array[i] != NULL && graph->array[i]->node->data == 1){
            Edge* edge = graph->array[i]->node->list;
            while(edge){
                if(graph->array[edge->dest]->node->data != 1)
                    // Contaminate neighboors of infected nodes
                    graph->array[edge->dest]->node->data = 2;
                edge = edge->next;
            }
        }
    }

    for(i = 0; i < graph->size; i++){
        if(graph->array[i] != NULL){
            if(graph->array[i]->node->data == 1)
                // Delete infected nodes
                deleteNode(graph, i, nodes, edges);
            else if(graph->array[i]->node->data == 2)
                // Infect contaminated nodes
                graph->array[i]->node->data = 1;
        }
    }
}

// Returns 1 if the graph is empty and 0 otherwise
int isGraphEmpty(Graph* graph) {
    int empty = 1, i = 0;
    while(empty && i < graph->size){
        if(graph->array[i] != NULL)
            empty = 0;
        i++;
    }
    return empty;
}
