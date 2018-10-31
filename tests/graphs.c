#include <stdio.h>
#include <stdlib.h>

typedef struct edge {
    int dest;
    int weight;
    struct edge* next;
} Edge;

typedef struct node {
    int infected;
    struct edge* list;
} Node;

typedef struct graph { 
    int size;
    Node* array;
} Graph;

Edge* createEdge(int dest, int weight) {
    Edge* newEdge = malloc(sizeof(Edge));
    newEdge->dest = dest;
    newEdge->weight = weight;
    newEdge->next = NULL;
    return newEdge;
}

Graph* createGraph(int size) { 
    Graph* graph = malloc(sizeof(Graph)); 
    graph->size = size; 

    graph->array = malloc(size * sizeof(Node)); 
    for(int i = 0; i < size; i++) {
        graph->array[i].infected = -1;
        graph->array[i].list = NULL;
    }
    return graph;
} 

// Adds an edge to an undirected graph 
void addEdge(Graph* graph, int src, int dest, int weight) { 
    // Add an edge from src to dest. A new node is 
    // added to the adjacency list of src. The node 
    // is added at the begining 
    Edge* newEdge = createEdge(dest, weight);
    newEdge->next = graph->array[src].list;
    graph->array[src].list = newEdge;

    // Since graph is undirected, add an edge from
    // dest to src also
    newEdge = createEdge(src, weight); 
    newEdge->next = graph->array[dest].list; 
    graph->array[dest].list = newEdge;
}

void deleteEdge(Graph* graph, int src, int dest) {
    Edge* edge = graph->array[src].list;
    Edge* prev = NULL;
    if(edge != NULL){
        if(edge->dest == dest){
            graph->array[src].list = graph->array[src].list->next;
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

int createNode(Graph* graph, int infected) {
    int i = 0;
    while(graph->array[i].infected != -1 && i < graph->size)
        i++;
    if(i == graph->size)
        printf("Maximum number of nodes reached");
    else
        graph->array[i].infected = infected;
    return i;
}

void deleteNode(Graph* graph, int id) {
    graph->array[id].infected = -1;
    Edge* tmp;
    while(graph->array[id].list != NULL) {
       tmp = graph->array[id].list;
       graph->array[id].list = graph->array[id].list->next;
       tmp->next = NULL;
       free(tmp);
    }

    for(int i = 0; i < graph->size; i++){
        deleteEdge(graph, i, id);
    }
}

// Print the adjacency list, representation of graph
void printGraph(Graph* graph) {
    for(int i = 0; i < graph->size; i++) {
        if(graph->array[i].infected != -1){
            Edge* pCrawl = graph->array[i].list;
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
        if(graph->array[i].infected != -1){
            printf("\nNode %d: ", i);
            if(graph->array[i].infected)
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
        if(graph->array[i].infected == 1){
            Edge* edge = graph->array[i].list;
            while(edge){
                if(graph->array[edge->dest].infected != 1)
                    graph->array[edge->dest].infected = 2;
                edge = edge->next;
            }
        }
    }

    for(i = 0; i < graph->size; i++){
        if(graph->array[i].infected == 1)
            deleteNode(graph, i);
        else if(graph->array[i].infected == 2)
            graph->array[i].infected = 1;
    }
}

int isEmpty(Graph* graph) {
    int empty = 1;
    for(int i = 0; i < graph->size; i++){
        if(graph->array[i].infected != -1)
            empty = 0;
    }
    return empty;
}

int main() {
    Graph* graph = createGraph(5);

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