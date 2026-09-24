#include <stdlib.h>
#include "coloracao.h"

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

int grau_vertice(GrafoLista *g, int v) {
    int grau = 0;
    No *p;
    if (!vertice_valido(g, v)) return -1;
    for (p = g->adj[v]; p != NULL; p = p->prox) grau++;
    return grau;
}

static int *colorir_na_ordem(GrafoLista *g, int *ordem, int *num_cores) {
    int *cor, *indisponivel, pos, maior_cor = -1;
    if (!g || !ordem || !num_cores) return NULL;

    cor = (int *)malloc((size_t)g->n * sizeof(int));
    indisponivel = (int *)malloc((size_t)g->n * sizeof(int));
    if (!cor || !indisponivel) {
        free(cor); free(indisponivel);
        return NULL;
    }

    for (pos = 0; pos < g->n; pos++) cor[pos] = -1;

    for (pos = 0; pos < g->n; pos++) {
        int u = ordem[pos], c;
        No *p;
        for (c = 0; c < g->n; c++) indisponivel[c] = 0;

        for (p = g->adj[u]; p != NULL; p = p->prox)
            if (cor[p->destino] >= 0) indisponivel[cor[p->destino]] = 1;

        for (c = 0; c < g->n; c++)
            if (!indisponivel[c]) break;
        cor[u] = c;
        if (c > maior_cor) maior_cor = c;
    }

    free(indisponivel);
    *num_cores = maior_cor + 1;
    return cor;
}

int *coloracao_gulosa(GrafoLista *g, int *num_cores) {
    int *ordem, *cor, i;
    if (!g || !num_cores) return NULL;
    ordem = (int *)malloc((size_t)g->n * sizeof(int));
    if (!ordem) return NULL;
    for (i = 0; i < g->n; i++) ordem[i] = i;
    cor = colorir_na_ordem(g, ordem, num_cores);
    free(ordem);
    return cor;
}

int *coloracao_welsh_powell(GrafoLista *g, int *num_cores) {
    int *ordem, i, j;
    int *cor;
    if (!g || !num_cores) return NULL;

    ordem = (int *)malloc((size_t)g->n * sizeof(int));
    if (!ordem) return NULL;
    for (i = 0; i < g->n; i++) ordem[i] = i;

    for (i = 0; i < g->n - 1; i++) {
        for (j = i + 1; j < g->n; j++) {
            int gi = grau_vertice(g, ordem[i]);
            int gj = grau_vertice(g, ordem[j]);
            if (gj > gi || (gj == gi && ordem[j] < ordem[i])) {
                int tmp = ordem[i];
                ordem[i] = ordem[j];
                ordem[j] = tmp;
            }
        }
    }

    cor = colorir_na_ordem(g, ordem, num_cores);
    free(ordem);
    return cor;
}

int eh_bipartido(GrafoLista *g) {
    int *cor, *fila, inicio, fim, s, i;
    if (!g) return 0;

    cor = (int *)malloc((size_t)g->n * sizeof(int));
    fila = (int *)malloc((size_t)g->n * sizeof(int));
    if (!cor || !fila) { free(cor); free(fila); return 0; }
    for (i = 0; i < g->n; i++) cor[i] = -1;

    for (s = 0; s < g->n; s++) {
        if (cor[s] != -1) continue;
        inicio = fim = 0;
        cor[s] = 0;
        fila[fim++] = s;

        while (inicio < fim) {
            int u = fila[inicio++];
            No *p;
            for (p = g->adj[u]; p != NULL; p = p->prox) {
                int v = p->destino;
                if (cor[v] == -1) {
                    cor[v] = 1 - cor[u];
                    fila[fim++] = v;
                } else if (cor[v] == cor[u]) {
                    free(cor); free(fila);
                    return 0;
                }
            }
        }
    }

    free(cor); free(fila);
    return 1;
}
