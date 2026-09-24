#ifndef CONECTIVIDADE_H
#define CONECTIVIDADE_H

typedef struct No {
    int destino;
    struct No *prox;
} No;

typedef struct {
    int n;
    No **adj;
} GrafoLista;

typedef struct {
    int u, v;
} Aresta;

GrafoLista *criar_grafo_lista(int n);
void inserir_aresta(GrafoLista *g, int u, int v);
void liberar_grafo(GrafoLista *g);
int numero_arestas(GrafoLista *g);

void dfs_articulacoes(GrafoLista *g, int u, int *visitado,
                      int *descoberta, int *low, int *pai,
                      int *articulacao, int *tempo);
int encontrar_articulacoes(GrafoLista *g, int *articulacao);
int detectar_pontes(GrafoLista *g, Aresta *pontes, int capacidade);

#endif
