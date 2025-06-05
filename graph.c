#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"
#include "uthash.h"

struct graph
{
    vertex V;           // each node
    int E;              // amount of edges
    int **adj;          // matrix
    vertex **adjEdges;  // matrix
};

struct stack{
    int data[STACK_SIZE];  
    int top;        
};

VertexMap *vertex_map = NULL; 


Graph textToGraph(FILE *file, Graph G, size_t totalVertex)
{
    char from_ad[43], to_ad[43];
    VertexMap *v, *w;
    size_t from_index, to_index, nextIndex = 0;

    G = initGraph(totalVertex);
    for(size_t i = 0; i < totalVertex; i++){
        fscanf(file, "%s %s", from_ad, to_ad);

        from_index = getVertexIndex(from_ad, &nextIndex);
        to_index = getVertexIndex(to_ad, &nextIndex);

        insertEdge(G, from_index, to_index);
    }

    return G;
}

void addToHash(const char *name, size_t *current_index)
{
    VertexMap *v;

    HASH_FIND_STR(vertex_map, name, v);
        if (v == NULL) {
            v = malloc(sizeof(VertexMap));
            strcpy(v->key, name);
            v->index = (*current_index)++;
            HASH_ADD_STR(vertex_map, key, v);
        }
}

// fill the hashmap, and returns how many nodes the graph has
size_t addAllVertexToHashmap(FILE *file)
{
    VertexMap *v;
    char from_ad[43], to_ad[43];
    size_t index = 0;

    while(fscanf(file, "%s %s", from_ad, to_ad) == 2){
        addToHash(from_ad, &index);
        addToHash(to_ad, &index);
    }

    return index;
}

Graph loadGraph(FILE *file, Graph graph)
{
    size_t graphSize = addAllVertexToHashmap(file);

    printf(" graph size: %lu\n", graphSize);
    rewind(file);
    graph = textToGraph(file, graph, graphSize);

    return graph;
}

size_t getVertexIndex(const char *name, size_t *nextIndex) {    
    VertexMap *v;
    HASH_FIND_STR(vertex_map, name, v);
    return v->index;
}

void printVertexMap(VertexMap *vertexMap) {
    VertexMap *v;
    printf("\n/ VERTEX MAP /\n");
    for (v = vertexMap; v != NULL; v = v->hh.next) {
        printf("Key: %s -> Index: %d\n", v->key, v->index);
    }
    printf("\n");
}

static int **initAdjMatrix(int row, int column)
{
    int **m = malloc(row * sizeof(int *)); 
    for(vertex i = 0; i < row; i++)
        m[i] = malloc(column * sizeof(int));
    for(vertex i = 0; i < row; i++)
        for(vertex j = 0; j < column; j++)
            m[i][j] = -1;
    
    return m;
}

static int *initArray(int size)
{
    int *a = malloc(size * sizeof(int));
    
    for(vertex i = 0; i < size; i++)
        a[i] = -1;

    return a;
}


Graph initGraph(int V)
{
    Graph G = malloc(sizeof *G);
    G->V = V;
    G->E = 0;
    G->adj = initAdjMatrix(V, V);
    return G;
}

int insertEdge(Graph G, vertex v, vertex w)
{
    if(G->adj[v][w] == -1)
    {
        G->adj[v][w] = 1;
        G->E++;

        return 1;
    }
    else return 0;
}

int removeEdge(Graph G, vertex v, vertex w)
{
    if(G->adj[v][w] != -1)
    {
        G->adj[v][w] = -1;
        G->E--;
        return 1;
    }
    else return 0;
}

int verifyEdge(Graph G, vertex v, vertex w)
{
    return G->adj[v][w];
}

int verifyVertex(Graph G, vertex v, vertex w)
{
    return (v < G->V && w < G->V) ? 1 : 0;
}

int numberEdge(Graph G)
{
    return G->E;
}

int numberVertex(Graph G)
{
    return G->V;
}

void showGraph(Graph G)
{
    if(G == NULL) printf("No graph to display..");
    else
    {
        printf("\n/ GRAPH - MATRIX /\n");
        printf("   ");
        for(vertex v = 0; v < G->V; v++)
            printf("\033[0;36m%2d ", v);
            
        printf("\n");
        for(vertex v = 0; v < G->V; v++)
        {
            printf("\033[0;36m%2d ", v);
            for(vertex w = 0; w < G->V; w++)
            {
                if(G->adj[v][w] == -1)
                    printf("\033[0m - ");
                else
                    printf("\033[0m%2d ", G->adj[v][w]);
                    
            }
            printf("\n");
        }
    }
    printf("\033[0m");
}

void freeGraph(Graph G)
{
    for(int row = 0; row < G->V; row++) free(G->adj[row]);

    free(G->adj);
    free(G);
}

void freeVertexMap() {
    VertexMap *current, *tmp;
    HASH_ITER(hh, vertex_map, current, tmp) {
        HASH_DEL(vertex_map, current);
        free(current);
    }
}

int isFull(Stack *s) {
    return s->top == STACK_SIZE - 1;
}

void initStack(Stack *s) {
    s->top = -1;
}

void pushStack(Stack *s, int v) {
    if (isFull(s)) {
        printf("Error: Stack is full!\n");
        return;
    }
    s->data[++(s->top)] = v;
}


int isEmpty(Stack *s) {
    return s->top == -1;
}

int popStack(Stack *s) {
    if (isEmpty(s)) {
        printf("Error: Empty stack!\n");
        return -1;
    }
    return s->data[(s->top)--];
}

int peekStack(Stack *s) {
    if (isEmpty(s)) {
        printf("Error: Empty stack!\n");
        return -1;
    }
    return s->data[s->top];
}

int isInStack(Stack * s, int v) {
    for (int i = 0; i <= s->top; i++) {
        if (s->data[i] == v)
            return 1;
    }
    return 0;
}

int vertexIsMarked(int *markedV, int w, int size)
{
    for(int i = 0; i < size; i++)
    {
        if(markedV[i] == w)
            return 1;
    }

    return 0;
}

void printArray(int *array, int size)
{
    for(int i = 0; i < size; i++)
        printf("%i ", array[i]);
    printf("\n");

}

void depthFirstSearch(Graph G)
{
    int visited[G->V];
    int recStack[G->V];

    for (int i = 0; i < G->V; i++) {
        visited[i] = 0;
        recStack[i] = 0;
    }

    printf("/ DFS with cycle detection / \n");
    printf("Visited edges: \n");

    for (int i = 0; i < G->V; i++) {
        if (visited[i] == 0) {
            recursiveDFS(G, visited, recStack, i);
        }
    }

    printf("\n");
}

void recursiveDFS(Graph G, int *visited, int *recStack, int v)
{
    visited[v] = 1;
    recStack[v] = 1;

    for (int w = 0; w < G->V; w++)
    {
        if (G->adj[v][w] != -1) 
        {
            if (visited[w] == 0)
            {
                printf("(%d -> %d)\n", v, w);
                recursiveDFS(G, visited, recStack, w);
            }
            else if (recStack[w] == 1)
            {
                printf("Cycle detected involving edge (%d -> %d)\n", v, w);
            }
        }
    }

    recStack[v] = 0;
}
