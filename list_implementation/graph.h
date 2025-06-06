#ifndef CF34E36C_803A_4D30_AC71_0842482F2317
#define CF34E36C_803A_4D30_AC71_0842482F2317

#include <stdio.h>
#include <stdlib.h>
#include "uthash.h"

typedef struct vertex_map {
    char key[43];
    size_t index;
    UT_hash_handle hh;
} VertexMap;

extern VertexMap *vertex_map ;


typedef int vertex;

// Nó da lista de adjacência
typedef struct AdjNode {
    vertex dest;
    struct AdjNode *next;
} AdjNode;

// Estrutura do grafo
typedef struct {
    vertex V;
    int E;
    AdjNode **adjList;  // vetor de ponteiros para listas encadeadas
} *Graph;

// Inicializa grafo com V vértices e listas vazias
Graph initGraph(int V) ;
// Insere aresta v->w no início da lista de v
int insertEdge(Graph G, vertex v, vertex w) ;
// Verifica se existe aresta v->w
int verifyEdge(Graph G, vertex v, vertex w);
// Remove aresta v->w se existir
int removeEdge(Graph G, vertex v, vertex w);

// Mostra o grafo imprimindo as listas de adjacência
void showGraph(Graph G);
// DFS auxiliar com detecção de ciclo usando recStack
void recursiveDFS(Graph G, int *visited, int *recStack, vertex v);
// Função pública para iniciar DFS
void depthFirstSearch(Graph G);
// Libera memória do grafo
void freeGraph(Graph G);


Graph loadGraph(FILE *file, Graph graph);
Graph hashToGraph(FILE *file, Graph G, size_t totalVertex);
void addToHash(const char *name, size_t *current_index);
size_t addAllVertexToHashmap(FILE *file);
size_t getVertexIndex(const char *name, size_t *nextIndex);
void freeVertexMap();


#endif /* CF34E36C_803A_4D30_AC71_0842482F2317 */
