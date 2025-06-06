#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

VertexMap *vertex_map = NULL; 

void freeVertexMap() {
    VertexMap *current, *tmp;
    HASH_ITER(hh, vertex_map, current, tmp) {
        HASH_DEL(vertex_map, current);
        free(current);
    }
}

Graph hashToGraph(FILE *file, Graph G, size_t totalVertex)
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
    graph = hashToGraph(file, graph, graphSize);

    return graph;
}

size_t getVertexIndex(const char *name, size_t *nextIndex) {    
    VertexMap *v;
    HASH_FIND_STR(vertex_map, name, v);
    return v->index;
}


// Inicializa grafo com V vértices e listas vazias
Graph initGraph(int V) {
    Graph G = malloc(sizeof(*G));
    if (!G) {
        fprintf(stderr, "Erro ao alocar grafo\n");
        exit(1);
    }
    G->V = V;
    G->E = 0;
    G->adjList = malloc(V * sizeof(AdjNode *));
    if (!G->adjList) {
        fprintf(stderr, "Erro ao alocar lista de adjacência\n");
        free(G);
        exit(1);
    }
    for (vertex i = 0; i < V; i++)
        G->adjList[i] = NULL;
    return G;
}

// Insere aresta v->w no início da lista de v
int insertEdge(Graph G, vertex v, vertex w) {
    if (v < 0 || v >= G->V || w < 0 || w >= G->V) return 0;

    AdjNode *newNode = malloc(sizeof(AdjNode));
    if (!newNode) {
        fprintf(stderr, "Erro ao alocar nó da lista\n");
        return 0;
    }

    newNode->dest = w;
    newNode->next = G->adjList[v];
    G->adjList[v] = newNode;

    G->E++;
    return 1;
}

// Verifica se existe aresta v->w
int verifyEdge(Graph G, vertex v, vertex w) {
    if (v < 0 || v >= G->V) return 0;

    AdjNode *curr = G->adjList[v];
    while (curr) {
        if (curr->dest == w)
            return 1;
        curr = curr->next;
    }
    return 0;
}

// Remove aresta v->w se existir
int removeEdge(Graph G, vertex v, vertex w) {
    if (v < 0 || v >= G->V) return 0;

    AdjNode **curr = &G->adjList[v];
    while (*curr) {
        if ((*curr)->dest == w) {
            AdjNode *toDelete = *curr;
            *curr = (*curr)->next;
            free(toDelete);
            G->E--;
            return 1;
        }
        curr = &(*curr)->next;
    }
    return 0;
}

// Mostra o grafo imprimindo as listas de adjacência
void showGraph(Graph G) {
    printf("\n/ GRAFO - LISTA DE ADJACÊNCIA /\n");
    for (vertex v = 0; v < G->V; v++) {
        printf("%d: ", v);
        AdjNode *curr = G->adjList[v];
        while (curr) {
            printf("%d -> ", curr->dest);
            curr = curr->next;
        }
        printf("NULL\n");
    }
}

// DFS auxiliar com detecção de ciclo usando recStack
void recursiveDFS(Graph G, int *visited, int *recStack, vertex v) {
    visited[v] = 1;
    recStack[v] = 1;

    AdjNode *curr = G->adjList[v];
    while (curr) {
        vertex w = curr->dest;
        if (!visited[w]) {
            printf("(%d -> %d)\n", v, w);
            recursiveDFS(G, visited, recStack, w);
        }
        else if (recStack[w]) {
            printf("Ciclo detectado envolvendo aresta (%d -> %d)\n", v, w);
        }
        curr = curr->next;
    }
    recStack[v] = 0;
}

// Função pública para iniciar DFS
void depthFirstSearch(Graph G) {
    int *visited = calloc(G->V, sizeof(int));
    int *recStack = calloc(G->V, sizeof(int));
    if (!visited || !recStack) {
        fprintf(stderr, "Erro ao alocar vetores DFS\n");
        free(visited);
        free(recStack);
        return;
    }
    for (vertex v = 0; v < G->V; v++) {
        if (!visited[v])
            recursiveDFS(G, visited, recStack, v);
    }
    free(visited);
    free(recStack);
}

// Libera memória do grafo
void freeGraph(Graph G) {
    for (vertex i = 0; i < G->V; i++) {
        AdjNode *curr = G->adjList[i];
        while (curr) {
            AdjNode *temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    free(G->adjList);
    free(G);
}

