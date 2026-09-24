#ifndef BUSCA_LARGURA_H
#define BUSCA_LARGURA_H

typedef struct No {
    int destino;
    struct No *prox;
} No;

typedef struct {
    int n;
    No **adj;
} GrafoLista;

typedef struct {
    int *dados;
    int capacidade, inicio, fim, tamanho;
} Fila;

GrafoLista *criar_grafo_lista(int n);
void inserir_aresta(GrafoLista *g, int u, int v);
void liberar_grafo(GrafoLista *g);

void fila_inicializar(Fila *f, int capacidade);
int fila_vazia(Fila *f);
void enfileirar(Fila *f, int valor);
int desenfileirar(Fila *f);
void fila_liberar(Fila *f);

void bfs(GrafoLista *g, int origem, int *dist, int *pred);
int eh_bipartido(GrafoLista *g);

#endif
