#include <stdlib.h>
#include "grafo_lista.h"

static int vertice_valido(const GrafoLista *g, int v) {
    return g != NULL && v >= 0 && v < g->n;
}

static No *criar_no(int destino) {
    No *novo = malloc(sizeof(No));
    if (novo == NULL) {
        return NULL;
    }

    novo->destino = destino;
    novo->prox = NULL;
    return novo;
}

static int existe_na_lista(const No *inicio, int destino) {
    const No *atual = inicio;

    while (atual != NULL) {
        if (atual->destino == destino) {
            return 1;
        }
        atual = atual->prox;
    }

    return 0;
}

static int adicionar_em_uma_lista(No **inicio, int destino) {
    No *novo = criar_no(destino);
    if (novo == NULL) {
        return 0;
    }

    novo->prox = *inicio;
    *inicio = novo;
    return 1;
}

static void remover_de_uma_lista(No **inicio, int destino) {
    No *atual = *inicio;
    No *anterior = NULL;

    while (atual != NULL) {
        if (atual->destino == destino) {
            if (anterior == NULL) {
                *inicio = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }
            free(atual);
            return;
        }

        anterior = atual;
        atual = atual->prox;
    }
}

GrafoLista *criar_grafo_lista(int n) {
    if (n <= 0) {
        return NULL;
    }

    GrafoLista *g = malloc(sizeof(GrafoLista));
    if (g == NULL) {
        return NULL;
    }

    g->n = n;
    g->adj = calloc((size_t)n, sizeof(No *));
    if (g->adj == NULL) {
        free(g);
        return NULL;
    }

    return g;
}

void inserir_aresta_lista(GrafoLista *g, int origem, int destino) {
    if (!vertice_valido(g, origem) || !vertice_valido(g, destino) || origem == destino) {
        return;
    }

    if (existe_na_lista(g->adj[origem], destino)) {
        return;
    }

    if (!adicionar_em_uma_lista(&g->adj[origem], destino)) {
        return;
    }

    if (!adicionar_em_uma_lista(&g->adj[destino], origem)) {
        remover_de_uma_lista(&g->adj[origem], destino);
    }
}

void remover_aresta_lista(GrafoLista *g, int origem, int destino) {
    if (!vertice_valido(g, origem) || !vertice_valido(g, destino)) {
        return;
    }

    remover_de_uma_lista(&g->adj[origem], destino);
    remover_de_uma_lista(&g->adj[destino], origem);
}

int grau_lista(const GrafoLista *g, int vertice) {
    if (!vertice_valido(g, vertice)) {
        return -1;
    }

    int grau = 0;
    const No *atual = g->adj[vertice];

    while (atual != NULL) {
        grau++;
        atual = atual->prox;
    }

    return grau;
}

int sao_adjacentes_lista(const GrafoLista *g, int v1, int v2) {
    if (!vertice_valido(g, v1) || !vertice_valido(g, v2)) {
        return 0;
    }

    return existe_na_lista(g->adj[v1], v2);
}

void liberar_grafo_lista(GrafoLista *g) {
    if (g == NULL) {
        return;
    }

    for (int i = 0; i < g->n; i++) {
        No *atual = g->adj[i];

        while (atual != NULL) {
            No *proximo = atual->prox;
            free(atual);
            atual = proximo;
        }
    }

    free(g->adj);
    free(g);
}
