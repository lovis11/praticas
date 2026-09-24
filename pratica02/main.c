#include <stdio.h>
#include <stdlib.h>
#include "busca_largura.h"
#include "busca_profundidade.h"

int main(void) {
    GrafoLista *g = criar_grafo_lista(7);
    int dist[7], pred_bfs[7];
    int visitado[7] = {0}, entrada[7] = {0}, saida[7] = {0}, pred_dfs[7];
    int tempo = 0, i;

    if (!g) return 1;

    inserir_aresta(g, 0, 1);
    inserir_aresta(g, 1, 2);
    inserir_aresta(g, 2, 0);
    inserir_aresta(g, 2, 3);
    inserir_aresta(g, 4, 5);

    bfs(g, 0, dist, pred_bfs);
    printf("=== BFS a partir do vertice 0 ===\n");
    for (i = 0; i < g->n; i++)
        printf("Vertice %d: distancia = %d, predecessor = %d\n", i, dist[i], pred_bfs[i]);

    for (i = 0; i < g->n; i++) pred_dfs[i] = -1;
    dfs_recursiva(g, 0, visitado, entrada, saida, pred_dfs, &tempo);

    printf("\n=== DFS recursiva a partir do vertice 0 ===\n");
    for (i = 0; i < g->n; i++)
        printf("Vertice %d: entrada = %d, saida = %d, predecessor = %d\n",
               i, entrada[i], saida[i], pred_dfs[i]);

    printf("\nComponentes conexos: %d\n", contar_componentes(g));
    printf("Possui ciclo? %s\n", tem_ciclo(g) ? "Sim" : "Nao");
    printf("Eh bipartido? %s\n", eh_bipartido(g) ? "Sim" : "Nao");

    liberar_grafo(g);
    return 0;
}
