#include <stdlib.h>
#include "conectividade.h"

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
    if (!g->adj) { free(g); return NULL; }
    for (i = 0; i < n; i++) g->adj[i] = NULL;
    return g;
}

void inserir_aresta(GrafoLista *g, int u, int v) {
    No *novo;
    if (!vertice_valido(g, u) || !vertice_valido(g, v) || u == v) return;
    if (sao_adjacentes(g, u, v)) return;

    novo = (No *)malloc(sizeof(No));
    if (!novo) return;
    novo->destino = v; novo->prox = g->adj[u]; g->adj[u] = novo;

    novo = (No *)malloc(sizeof(No));
    if (!novo) return;
    novo->destino = u; novo->prox = g->adj[v]; g->adj[v] = novo;
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

int numero_arestas(GrafoLista *g) {
    int soma = 0, i;
    if (!g) return 0;
    for (i = 0; i < g->n; i++) {
        No *p;
        for (p = g->adj[i]; p != NULL; p = p->prox) soma++;
    }
    return soma / 2;
}

void dfs_articulacoes(GrafoLista *g, int u, int *visitado,
                      int *descoberta, int *low, int *pai,
                      int *articulacao, int *tempo) {
    int filhos = 0;
    No *p;

    visitado[u] = 1;
    descoberta[u] = low[u] = ++(*tempo);

    for (p = g->adj[u]; p != NULL; p = p->prox) {
        int v = p->destino;
        if (!visitado[v]) {
            filhos++;
            pai[v] = u;
            dfs_articulacoes(g, v, visitado, descoberta, low, pai, articulacao, tempo);
            if (low[v] < low[u]) low[u] = low[v];

            if (pai[u] == -1 && filhos > 1) articulacao[u] = 1;
            if (pai[u] != -1 && low[v] >= descoberta[u]) articulacao[u] = 1;
        } else if (v != pai[u] && descoberta[v] < low[u]) {
            low[u] = descoberta[v];
        }
    }
}

int encontrar_articulacoes(GrafoLista *g, int *articulacao) {
    int *visitado, *descoberta, *low, *pai;
    int i, tempo = 0, total = 0;
    if (!g || !articulacao) return 0;

    visitado = (int *)calloc((size_t)g->n, sizeof(int));
    descoberta = (int *)calloc((size_t)g->n, sizeof(int));
    low = (int *)calloc((size_t)g->n, sizeof(int));
    pai = (int *)malloc((size_t)g->n * sizeof(int));
    if (!visitado || !descoberta || !low || !pai) {
        free(visitado); free(descoberta); free(low); free(pai);
        return 0;
    }

    for (i = 0; i < g->n; i++) {
        pai[i] = -1;
        articulacao[i] = 0;
    }

    for (i = 0; i < g->n; i++)
        if (!visitado[i])
            dfs_articulacoes(g, i, visitado, descoberta, low, pai, articulacao, &tempo);

    for (i = 0; i < g->n; i++) total += articulacao[i] != 0;
    free(visitado); free(descoberta); free(low); free(pai);
    return total;
}

static void dfs_pontes(GrafoLista *g, int u, int *visitado,
                       int *descoberta, int *low, int *pai, int *tempo,
                       Aresta *pontes, int capacidade, int *total) {
    No *p;
    visitado[u] = 1;
    descoberta[u] = low[u] = ++(*tempo);

    for (p = g->adj[u]; p != NULL; p = p->prox) {
        int v = p->destino;
        if (!visitado[v]) {
            pai[v] = u;
            dfs_pontes(g, v, visitado, descoberta, low, pai, tempo,
                       pontes, capacidade, total);
            if (low[v] < low[u]) low[u] = low[v];

            if (low[v] > descoberta[u]) {
                if (*total < capacidade) {
                    pontes[*total].u = u;
                    pontes[*total].v = v;
                }
                (*total)++;
            }
        } else if (v != pai[u] && descoberta[v] < low[u]) {
            low[u] = descoberta[v];
        }
    }
}

int detectar_pontes(GrafoLista *g, Aresta *pontes, int capacidade) {
    int *visitado, *descoberta, *low, *pai;
    int i, tempo = 0, total = 0;
    if (!g || capacidade < 0) return 0;

    visitado = (int *)calloc((size_t)g->n, sizeof(int));
    descoberta = (int *)calloc((size_t)g->n, sizeof(int));
    low = (int *)calloc((size_t)g->n, sizeof(int));
    pai = (int *)malloc((size_t)g->n * sizeof(int));
    if (!visitado || !descoberta || !low || !pai) {
        free(visitado); free(descoberta); free(low); free(pai);
        return 0;
    }

    for (i = 0; i < g->n; i++) pai[i] = -1;
    for (i = 0; i < g->n; i++)
        if (!visitado[i])
            dfs_pontes(g, i, visitado, descoberta, low, pai, &tempo,
                       pontes, capacidade, &total);

    free(visitado); free(descoberta); free(low); free(pai);
    return total;
}
