#include <stdio.h>
#include <stdlib.h>

typedef struct edge {
    int dest;
    int weight;
    struct edge* next;
} Edge;

typedef struct node {
    char infected;
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
        graph->array[i].infected = 0;
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

// Print the adjacency list, representation of graph
void printGraph(Graph* graph) {
    for(int i = 0; i < graph->size; i++) {
        Edge* pCrawl = graph->array[i].list;
        printf("\n Adjacency list of vertex %d\n ", i);
        while(pCrawl) {
            printf("-> %d", pCrawl->dest);
            pCrawl = pCrawl->next;
        }
        printf("\n");
    }
}

void printNodes(Graph* graph) {
    for(int i = 0; i < graph->size; i++) {
        printf("\nNode %d: ", i);
        if(graph->array[i].infected)
            printf("infected");
        else
            printf("not infected");
    }
    printf("\n");
}

int main() {
    Graph* graph = createGraph(5);
    addEdge(graph, 0, 1, 1);
    addEdge(graph, 0, 4, 1);
    addEdge(graph, 1, 2, 1);
    addEdge(graph, 1, 3, 1);
    addEdge(graph, 1, 4, 1);
    addEdge(graph, 2, 3, 1);
    addEdge(graph, 3, 4, 1);

    // print the adjacency list representation of the graph
    printGraph(graph);
    printNodes(graph);
    system("pause");
    return 0;
}