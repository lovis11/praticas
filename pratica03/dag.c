#include <stdlib.h>
#include "dag.h"

static int vertice_valido(GrafoLista *g, int v) {
    return g != NULL && v >= 0 && v < g->n;
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

void inserir_aresta_direcionada(GrafoLista *g, int origem, int destino) {
    No *p, *novo;
    if (!vertice_valido(g, origem) || !vertice_valido(g, destino)) return;
    for (p = g->adj[origem]; p != NULL; p = p->prox)
        if (p->destino == destino) return;
    novo = (No *)malloc(sizeof(No));
    if (!novo) return;
    novo->destino = destino;
    novo->prox = g->adj[origem];
    g->adj[origem] = novo;
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

int *ordenacao_topologica_kahn(GrafoLista *g, int *tamanho) {
    int *grau_entrada, *fila, *ordem;
    int inicio = 0, fim = 0, k = 0, i;
    if (!g || !tamanho) return NULL;

    *tamanho = 0;
    grau_entrada = (int *)calloc((size_t)g->n, sizeof(int));
    fila = (int *)malloc((size_t)g->n * sizeof(int));
    ordem = (int *)malloc((size_t)g->n * sizeof(int));
    if (!grau_entrada || !fila || !ordem) {
        free(grau_entrada); free(fila); free(ordem);
        return NULL;
    }

    for (i = 0; i < g->n; i++) {
        No *p;
        for (p = g->adj[i]; p != NULL; p = p->prox)
            grau_entrada[p->destino]++;
    }

    for (i = 0; i < g->n; i++)
        if (grau_entrada[i] == 0) fila[fim++] = i;

    while (inicio < fim) {
        int u = fila[inicio++];
        No *p;
        ordem[k++] = u;
        for (p = g->adj[u]; p != NULL; p = p->prox) {
            int v = p->destino;
            grau_entrada[v]--;
            if (grau_entrada[v] == 0) fila[fim++] = v;
        }
    }

    free(grau_entrada);
    free(fila);

    if (k != g->n) {
        free(ordem);
        return NULL;
    }

    *tamanho = k;
    return ordem;
}

static int dfs_topologica(GrafoLista *g, int u, int *cor, int *ordem, int *pos) {
    No *p;
    cor[u] = 1;
    for (p = g->adj[u]; p != NULL; p = p->prox) {
        int v = p->destino;
        if (cor[v] == 1) return 0;
        if (cor[v] == 0 && !dfs_topologica(g, v, cor, ordem, pos)) return 0;
    }
    cor[u] = 2;
    ordem[(*pos)--] = u;
    return 1;
}

int *ordenacao_topologica_dfs(GrafoLista *g, int *tamanho) {
    int *cor, *ordem, pos, i;
    if (!g || !tamanho) return NULL;
    *tamanho = 0;

    cor = (int *)calloc((size_t)g->n, sizeof(int));
    ordem = (int *)malloc((size_t)g->n * sizeof(int));
    if (!cor || !ordem) {
        free(cor); free(ordem);
        return NULL;
    }

    pos = g->n - 1;
    for (i = 0; i < g->n; i++) {
        if (cor[i] == 0 && !dfs_topologica(g, i, cor, ordem, &pos)) {
            free(cor);
            free(ordem);
            return NULL;
        }
    }

    free(cor);
    *tamanho = g->n;
    return ordem;
}

int eh_dag(GrafoLista *g) {
    int tamanho;
    int *ordem = ordenacao_topologica_kahn(g, &tamanho);
    if (!ordem) return 0;
    free(ordem);
    return tamanho == g->n;
}
