#include <stdlib.h>
#include "busca_profundidade.h"

void pilha_inicializar(Pilha *p, int capacidade) {
    p->dados = (int *)malloc((size_t)capacidade * sizeof(int));
    p->topo = -1;
    p->capacidade = capacidade;
}

int pilha_vazia(Pilha *p) {
    return p->topo < 0;
}

void empilhar(Pilha *p, int valor) {
    if (p->topo + 1 >= p->capacidade) return;
    p->dados[++p->topo] = valor;
}

int desempilhar(Pilha *p) {
    if (pilha_vazia(p)) return -1;
    return p->dados[p->topo--];
}

void pilha_liberar(Pilha *p) {
    free(p->dados);
    p->dados = NULL;
    p->topo = -1;
    p->capacidade = 0;
}

void dfs_recursiva(GrafoLista *g, int u, int *visitado,
                   int *tempo_entrada, int *tempo_saida,
                   int *pred, int *tempo) {
    No *p;
    visitado[u] = 1;
    tempo_entrada[u] = ++(*tempo);

    for (p = g->adj[u]; p != NULL; p = p->prox) {
        int v = p->destino;
        if (!visitado[v]) {
            pred[v] = u;
            dfs_recursiva(g, v, visitado, tempo_entrada, tempo_saida, pred, tempo);
        }
    }

    tempo_saida[u] = ++(*tempo);
}

void dfs_iterativa(GrafoLista *g, int origem, int *visitado) {
    Pilha p;
    int i;
    if (!g || !visitado || origem < 0 || origem >= g->n) return;

    for (i = 0; i < g->n; i++) visitado[i] = 0;
    pilha_inicializar(&p, g->n);
    empilhar(&p, origem);

    while (!pilha_vazia(&p)) {
        int u = desempilhar(&p);
        No *no;
        if (visitado[u]) continue;
        visitado[u] = 1;
        for (no = g->adj[u]; no != NULL; no = no->prox)
            if (!visitado[no->destino]) empilhar(&p, no->destino);
    }

    pilha_liberar(&p);
}

static void dfs_marcar(GrafoLista *g, int u, int *visitado) {
    No *p;
    visitado[u] = 1;
    for (p = g->adj[u]; p != NULL; p = p->prox)
        if (!visitado[p->destino]) dfs_marcar(g, p->destino, visitado);
}

int contar_componentes(GrafoLista *g) {
    int *visitado, i, componentes = 0;
    if (!g) return 0;

    visitado = (int *)calloc((size_t)g->n, sizeof(int));
    if (!visitado) return 0;

    for (i = 0; i < g->n; i++) {
        if (!visitado[i]) {
            componentes++;
            dfs_marcar(g, i, visitado);
        }
    }

    free(visitado);
    return componentes;
}

static int dfs_ciclo(GrafoLista *g, int u, int pai, int *visitado) {
    No *p;
    visitado[u] = 1;

    for (p = g->adj[u]; p != NULL; p = p->prox) {
        int v = p->destino;
        if (!visitado[v]) {
            if (dfs_ciclo(g, v, u, visitado)) return 1;
        } else if (v != pai) {
            return 1;
        }
    }
    return 0;
}

int tem_ciclo(GrafoLista *g) {
    int *visitado, i;
    if (!g) return 0;

    visitado = (int *)calloc((size_t)g->n, sizeof(int));
    if (!visitado) return 0;

    for (i = 0; i < g->n; i++) {
        if (!visitado[i] && dfs_ciclo(g, i, -1, visitado)) {
            free(visitado);
            return 1;
        }
    }

    free(visitado);
    return 0;
}
