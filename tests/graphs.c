// A matrix is symetric if the graph is not directed
// Adjacency list representation of graphs 
#include <stdio.h> 
#include <stdlib.h> 

// Adjacency list node 
struct AdjListNode 
{ 
    int dest; 
    struct AdjListNode* next; 
}; 

// Adjacency list 
struct AdjList 
{ 
    struct AdjListNode *head; 
}; 

// A graph is an array of adjacency lists. 
// Size of array will be V (number of vertices 
// in graph) 
struct Graph 
{ 
    int V; 
    struct AdjList* array; 
}; 

// Create a new adjacency list node 
struct AdjListNode* newAdjListNode(int dest) 
{ 
    struct AdjListNode* newNode = 
    (struct AdjListNode*) malloc(sizeof(struct AdjListNode)); 
    newNode->dest = dest; 
    newNode->next = NULL; 
    return newNode; 
} 

// Creates a graph of V vertices 
struct Graph* createGraph(int V) 
{ 
    struct Graph* graph = 
        (struct Graph*) malloc(sizeof(struct Graph)); 
    graph->V = V; 

    // Create an array of adjacency lists. Size of 
    // array will be V 
    graph->array = 
    (struct AdjList*) malloc(V * sizeof(struct AdjList)); 

    // Initialize each adjacency list as empty by 
    // making head as NULL 
    int i; 
    for (i = 0; i < V; ++i) 
        graph->array[i].head = NULL; 

    return graph; 
} 

// Adds an edge to an undirected graph 
void addEdge(struct Graph* graph, int src, int dest) 
{ 
    // Add an edge from src to dest. A new node is 
    // added to the adjacency list of src. The node 
    // is added at the begining 
    struct AdjListNode* newNode = newAdjListNode(dest); 
    newNode->next = graph->array[src].head; 
    graph->array[src].head = newNode; 

    // Since graph is undirected, add an edge from 
    // dest to src also 
    newNode = newAdjListNode(src); 
    newNode->next = graph->array[dest].head; 
    graph->array[dest].head = newNode; 
} 

// Print the adjacency list, representation of graph
void printGraph(struct Graph* graph) 
{ 
    for (int i = 0; i < graph->V; ++i) 
    { 
        struct AdjListNode* pCrawl = graph->array[i].head; 
        printf("\n Adjacency list of vertex %d\n head ", i); 
        while (pCrawl) 
        { 
            printf("-> %d", pCrawl->dest); 
            pCrawl = pCrawl->next; 
        } 
        printf("\n"); 
    } 
} 

int main() {
    struct Graph* graph = createGraph(5); 
    addEdge(graph, 0, 1); 
    addEdge(graph, 0, 4); 
    addEdge(graph, 1, 2); 
    addEdge(graph, 1, 3); 
    addEdge(graph, 1, 4); 
    addEdge(graph, 2, 3); 
    addEdge(graph, 3, 4); 

    // print the adjacency list representation of the above graph 
    printGraph(graph); 

    return 0; 
} 
