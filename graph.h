#ifndef GRAPH_H
#define GRAPH_H

#include "uthash.h"
#include <stdio.h>

#define NILL -1 
#define vertex int
#define STACK_SIZE 100

typedef struct graph *Graph;
typedef struct stack Stack;

typedef struct vertex_map {
    char key[43];
    size_t index;
    UT_hash_handle hh;
} VertexMap;

//global
extern VertexMap *vertex_map ;

// Funções
size_t getVertexIndex(const char *name, size_t *nextIndex);
VertexMap *findVertexByName(VertexMap *vertexMap, const char *name);
void printVertexMap(VertexMap *vertexMap);
void freeVertexMap();

Graph insertTextGraph(FILE *file, Graph G);

Graph initGraph(int V);
static int **initAdjMatrix(int row, int column);
static int *initArray(int size);

int insertEdge(Graph G, vertex v, vertex w);
int removeEdge(Graph G, vertex v, vertex w);
int verifyEdge(Graph G, vertex v, vertex w);
int verifyVertex(Graph G, vertex v, vertex w);
int numberEdge(Graph G);
int numberVertex(Graph G);
void showGraph(Graph G);
void freeGraph(Graph G);
void freeVertexMap();

void depthFirstSearch(Graph G);
void recursiveDFS(Graph G, int *visited, int *recStack, int v);

Graph loadGraph(FILE *file, Graph graph);
Graph textToGraph(FILE *file, Graph G, size_t totalVertex);
void addToHash(const char *name, size_t *current_index);
size_t addAllVertexToHashmap(FILE *file);

#endif