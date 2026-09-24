#include <stdlib.h>
#include "planaridade.h"

int eh_planar_euler(GrafoLista *g) {
    int m;
    if (!g) return 0;
    if (g->n < 3) return 1;
    m = numero_arestas(g);
    return m <= 3 * g->n - 6;
}

static int **matriz_do_grafo(GrafoLista *g) {
    int **a, i;
    a = (int **)malloc((size_t)g->n * sizeof(int *));
    if (!a) return NULL;
    for (i = 0; i < g->n; i++) {
        No *p;
        a[i] = (int *)calloc((size_t)g->n, sizeof(int));
        if (!a[i]) {
            int j;
            for (j = 0; j < i; j++) free(a[j]);
            free(a);
            return NULL;
        }
        for (p = g->adj[i]; p != NULL; p = p->prox)
            a[i][p->destino] = 1;
    }
    return a;
}

static void liberar_matriz(int **a, int n) {
    int i;
    if (!a) return;
    for (i = 0; i < n; i++) free(a[i]);
    free(a);
}

static void suprimir_vertices_grau_2(int **a, int n, int *ativo) {
    int mudou = 1;
    while (mudou) {
        int v;
        mudou = 0;
        for (v = 0; v < n; v++) {
            int grau = 0, x = -1, y = -1, u;
            if (!ativo[v]) continue;
            for (u = 0; u < n; u++) {
                if (ativo[u] && a[v][u]) {
                    if (grau == 0) x = u;
                    else if (grau == 1) y = u;
                    grau++;
                }
            }
            if (grau == 2) {
                a[x][y] = a[y][x] = 1;
                for (u = 0; u < n; u++) a[v][u] = a[u][v] = 0;
                ativo[v] = 0;
                mudou = 1;
                break;
            }
        }
    }
}

static int possui_k5_matriz(int **a, int n, int *ativo) {
    int a0, b, c, d, e;
    for (a0 = 0; a0 < n; a0++) if (ativo[a0])
    for (b = a0 + 1; b < n; b++) if (ativo[b])
    for (c = b + 1; c < n; c++) if (ativo[c])
    for (d = c + 1; d < n; d++) if (ativo[d])
    for (e = d + 1; e < n; e++) if (ativo[e]) {
        int v[5] = {a0, b, c, d, e};
        int i, j, ok = 1;
        for (i = 0; i < 5 && ok; i++)
            for (j = i + 1; j < 5; j++)
                if (!a[v[i]][v[j]]) { ok = 0; break; }
        if (ok) return 1;
    }
    return 0;
}

static int possui_k33_matriz(int **a, int n, int *ativo) {
    int s0, s1, s2, s3, s4, s5;
    for (s0 = 0; s0 < n; s0++) if (ativo[s0])
    for (s1 = s0 + 1; s1 < n; s1++) if (ativo[s1])
    for (s2 = s1 + 1; s2 < n; s2++) if (ativo[s2])
    for (s3 = s2 + 1; s3 < n; s3++) if (ativo[s3])
    for (s4 = s3 + 1; s4 < n; s4++) if (ativo[s4])
    for (s5 = s4 + 1; s5 < n; s5++) if (ativo[s5]) {
        int s[6] = {s0, s1, s2, s3, s4, s5};
        int p1, p2, p3;
        for (p1 = 0; p1 < 4; p1++)
        for (p2 = p1 + 1; p2 < 5; p2++)
        for (p3 = p2 + 1; p3 < 6; p3++) {
            int ladoA[3] = {s[p1], s[p2], s[p3]};
            int ladoB[3], bi = 0, i, j, ok = 1;
            for (i = 0; i < 6; i++)
                if (i != p1 && i != p2 && i != p3) ladoB[bi++] = s[i];
            for (i = 0; i < 3 && ok; i++)
                for (j = 0; j < 3; j++)
                    if (!a[ladoA[i]][ladoB[j]]) { ok = 0; break; }
            if (ok) return 1;
        }
    }
    return 0;
}

static int testar_kuratowski(GrafoLista *g, int qual) {
    int **a, *ativo, i, resultado;
    if (!g || g->n > 10) return 0;
    a = matriz_do_grafo(g);
    ativo = (int *)malloc((size_t)g->n * sizeof(int));
    if (!a || !ativo) {
        liberar_matriz(a, g ? g->n : 0);
        free(ativo);
        return 0;
    }
    for (i = 0; i < g->n; i++) ativo[i] = 1;
    suprimir_vertices_grau_2(a, g->n, ativo);
    resultado = (qual == 5) ? possui_k5_matriz(a, g->n, ativo)
                            : possui_k33_matriz(a, g->n, ativo);
    liberar_matriz(a, g->n);
    free(ativo);
    return resultado;
}

int tem_subdivisao_k5(GrafoLista *g) {
    return testar_kuratowski(g, 5);
}

int tem_subdivisao_k33(GrafoLista *g) {
    return testar_kuratowski(g, 33);
}

int eh_planar_heuristico(GrafoLista *g) {
    if (!g) return 0;
    if (!eh_planar_euler(g)) return 0;
    if (g->n <= 10 && (tem_subdivisao_k5(g) || tem_subdivisao_k33(g))) return 0;
    return 1;
}
