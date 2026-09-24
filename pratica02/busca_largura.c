#include <stdio.h>
#include <stdlib.h>
#include "busca_largura.h"

static int vertice_valido(GrafoLista *g, int v) {
    return g != NULL && v >= 0 && v < g->n;
}

static int sao_adjacentes(GrafoLista *g, int u, int v) {
    No *p;
    if (!vertice_valido(g, u) || !vertice_valido(g, v)) return 0;
    for (p = g->adj[u]; p != NULL; p = p->prox)
        if (p->destino == v) return 1;
    return 0;
}

GrafoLista *criar_grafo_lista(int n) {
    GrafoLista *g;
    int i;
    if (n <= 0) return NULL;

    g = (GrafoLista *)malloc(sizeof(GrafoLista));
    if (!g) return NULL;

    g->n = n;
    g->adj = (No **)malloc((size_t)n * sizeof(No *));
    if (!g->adj) {
        free(g);
        return NULL;
    }

    for (i = 0; i < n; i++) g->adj[i] = NULL;
    return g;
}

void inserir_aresta(GrafoLista *g, int u, int v) {
    No *novo;
    if (!vertice_valido(g, u) || !vertice_valido(g, v) || u == v) return;
    if (sao_adjacentes(g, u, v)) return;

    novo = (No *)malloc(sizeof(No));
    if (!novo) return;
    novo->destino = v;
    novo->prox = g->adj[u];
    g->adj[u] = novo;

    novo = (No *)malloc(sizeof(No));
    if (!novo) return;
    novo->destino = u;
    novo->prox = g->adj[v];
    g->adj[v] = novo;
}

void liberar_grafo(GrafoLista *g) {
    int i;
    if (!g) return;
    for (i = 0; i < g->n; i++) {
        No *p = g->adj[i];
        while (p) {
            No *tmp = p;
            p = p->prox;
            free(tmp);
        }
    }
    free(g->adj);
    free(g);
}

void fila_inicializar(Fila *f, int capacidade) {
    f->dados = (int *)malloc((size_t)capacidade * sizeof(int));
    f->capacidade = capacidade;
    f->inicio = 0;
    f->fim = 0;
    f->tamanho = 0;
}

int fila_vazia(Fila *f) {
    return f->tamanho == 0;
}

void enfileirar(Fila *f, int valor) {
    if (f->tamanho == f->capacidade) return;
    f->dados[f->fim] = valor;
    f->fim = (f->fim + 1) % f->capacidade;
    f->tamanho++;
}

int desenfileirar(Fila *f) {
    int valor;
    if (fila_vazia(f)) return -1;
    valor = f->dados[f->inicio];
    f->inicio = (f->inicio + 1) % f->capacidade;
    f->tamanho--;
    return valor;
}

void fila_liberar(Fila *f) {
    free(f->dados);
    f->dados = NULL;
    f->capacidade = f->inicio = f->fim = f->tamanho = 0;
}

void bfs(GrafoLista *g, int origem, int *dist, int *pred) {
    Fila f;
    int i;
    if (!g || !dist || !pred || !vertice_valido(g, origem)) return;

    for (i = 0; i < g->n; i++) {
        dist[i] = -1;
        pred[i] = -1;
    }

    fila_inicializar(&f, g->n);
    dist[origem] = 0;
    enfileirar(&f, origem);

    while (!fila_vazia(&f)) {
        int u = desenfileirar(&f);
        No *p;
        for (p = g->adj[u]; p != NULL; p = p->prox) {
            int v = p->destino;
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                pred[v] = u;
                enfileirar(&f, v);
            }
        }
    }

    fila_liberar(&f);
}

int eh_bipartido(GrafoLista *g) {
    int *cor, inicio;
    Fila f;
    if (!g) return 0;

    cor = (int *)malloc((size_t)g->n * sizeof(int));
    if (!cor) return 0;
    for (inicio = 0; inicio < g->n; inicio++) cor[inicio] = -1;

    fila_inicializar(&f, g->n);

    for (inicio = 0; inicio < g->n; inicio++) {
        if (cor[inicio] != -1) continue;
        cor[inicio] = 0;
        enfileirar(&f, inicio);

        while (!fila_vazia(&f)) {
            int u = desenfileirar(&f);
            No *p;
            for (p = g->adj[u]; p != NULL; p = p->prox) {
                int v = p->destino;
                if (cor[v] == -1) {
                    cor[v] = 1 - cor[u];
                    enfileirar(&f, v);
                } else if (cor[v] == cor[u]) {
                    fila_liberar(&f);
                    free(cor);
                    return 0;
                }
            }
        }
    }

    fila_liberar(&f);
    free(cor);
    return 1;
}
