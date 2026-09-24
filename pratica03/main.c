#include <stdio.h>
#include <stdlib.h>
#include "dag.h"

static void imprimir_ordem(const char *titulo, int *ordem, int tamanho) {
    int i;
    printf("%s", titulo);
    if (!ordem) {
        printf("impossivel (o digrafo possui ciclo)\n");
        return;
    }
    for (i = 0; i < tamanho; i++)
        printf("%d%s", ordem[i], (i + 1 == tamanho) ? "\n" : " -> ");
}

int main(void) {
    GrafoLista *g = criar_grafo_lista(6);
    int tamanho_kahn, tamanho_dfs;
    int *ordem_kahn, *ordem_dfs;

    if (!g) return 1;

    inserir_aresta_direcionada(g, 5, 2);
    inserir_aresta_direcionada(g, 5, 0);
    inserir_aresta_direcionada(g, 4, 0);
    inserir_aresta_direcionada(g, 4, 1);
    inserir_aresta_direcionada(g, 2, 3);
    inserir_aresta_direcionada(g, 3, 1);

    printf("Eh DAG? %s\n", eh_dag(g) ? "Sim" : "Nao");

    ordem_kahn = ordenacao_topologica_kahn(g, &tamanho_kahn);
    ordem_dfs = ordenacao_topologica_dfs(g, &tamanho_dfs);
    imprimir_ordem("Kahn: ", ordem_kahn, tamanho_kahn);
    imprimir_ordem("DFS:  ", ordem_dfs, tamanho_dfs);
    free(ordem_kahn);
    free(ordem_dfs);

    printf("\nAdicionando a aresta 1 -> 5 para formar um ciclo...\n");
    inserir_aresta_direcionada(g, 1, 5);
    printf("Eh DAG? %s\n", eh_dag(g) ? "Sim" : "Nao");

    ordem_kahn = ordenacao_topologica_kahn(g, &tamanho_kahn);
    imprimir_ordem("Kahn: ", ordem_kahn, tamanho_kahn);
    free(ordem_kahn);

    liberar_grafo(g);
    return 0;
}
