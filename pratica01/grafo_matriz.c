#include <stdio.h>
#include <stdlib.h>
#include "grafo_matriz.h"

static int vertice_valido(const GrafoMatriz *g, int v) {
    return g != NULL && v >= 0 && v < g->n;
}

GrafoMatriz *criar_grafo_matriz(int n) {
    if (n <= 0) {
        return NULL;
    }

    GrafoMatriz *g = malloc(sizeof(GrafoMatriz));
    if (g == NULL) {
        return NULL;
    }

    g->n = n;
    g->adj = calloc((size_t)n, sizeof(int *));
    if (g->adj == NULL) {
        free(g);
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        g->adj[i] = calloc((size_t)n, sizeof(int));
        if (g->adj[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(g->adj[j]);
            }
            free(g->adj);
            free(g);
            return NULL;
        }
    }

    return g;
}

void inserir_aresta_matriz(GrafoMatriz *g, int origem, int destino) {
    if (!vertice_valido(g, origem) || !vertice_valido(g, destino) || origem == destino) {
        return;
    }

    g->adj[origem][destino] = 1;
    g->adj[destino][origem] = 1;
}

void remover_aresta_matriz(GrafoMatriz *g, int origem, int destino) {
    if (!vertice_valido(g, origem) || !vertice_valido(g, destino)) {
        return;
    }

    g->adj[origem][destino] = 0;
    g->adj[destino][origem] = 0;
}

int grau_matriz(const GrafoMatriz *g, int vertice) {
    if (!vertice_valido(g, vertice)) {
        return -1;
    }

    int grau = 0;
    for (int i = 0; i < g->n; i++) {
        grau += g->adj[vertice][i];
    }

    return grau;
}

int sao_adjacentes_matriz(const GrafoMatriz *g, int v1, int v2) {
    if (!vertice_valido(g, v1) || !vertice_valido(g, v2)) {
        return 0;
    }

    return g->adj[v1][v2] != 0;
}

void liberar_grafo_matriz(GrafoMatriz *g) {
    if (g == NULL) {
        return;
    }

    for (int i = 0; i < g->n; i++) {
        free(g->adj[i]);
    }

    free(g->adj);
    free(g);
}
