#include <stdio.h>
#include <stdlib.h>
#include "conectividade.h"
#include "planaridade.h"

int main(void) {
    GrafoLista *g = criar_grafo_lista(6);
    GrafoLista *k33 = criar_grafo_lista(6);
    int articulacao[6], total_art, total_pontes, i, j;
    Aresta pontes[16];

    if (!g || !k33) return 1;

    inserir_aresta(g, 0, 1);
    inserir_aresta(g, 1, 2);
    inserir_aresta(g, 2, 0);
    inserir_aresta(g, 1, 3);
    inserir_aresta(g, 3, 4);
    inserir_aresta(g, 4, 5);
    inserir_aresta(g, 5, 3);

    total_art = encontrar_articulacoes(g, articulacao);
    printf("=== Conectividade (Tarjan) ===\n");
    printf("Articulacoes (%d): ", total_art);
    for (i = 0; i < g->n; i++)
        if (articulacao[i]) printf("%d ", i);
    printf("\n");

    total_pontes = detectar_pontes(g, pontes, 16);
    printf("Pontes (%d): ", total_pontes);
    for (i = 0; i < total_pontes && i < 16; i++)
        printf("(%d,%d) ", pontes[i].u, pontes[i].v);
    printf("\n");

    for (i = 0; i < 3; i++)
        for (j = 3; j < 6; j++)
            inserir_aresta(k33, i, j);

    printf("\n=== Planaridade ===\n");
    printf("Grafo de conectividade passa em Euler? %s\n",
           eh_planar_euler(g) ? "Sim" : "Nao");
    printf("Grafo de conectividade: %s\n",
           eh_planar_heuristico(g) ? "planar pela heuristica" : "nao planar pela heuristica");

    printf("K3,3 passa em Euler? %s\n", eh_planar_euler(k33) ? "Sim" : "Nao");
    printf("K3,3 detectado pela heuristica de Kuratowski? %s\n",
           tem_subdivisao_k33(k33) ? "Sim" : "Nao");
    printf("K3,3: %s\n",
           eh_planar_heuristico(k33) ? "planar pela heuristica" : "nao planar pela heuristica");

    liberar_grafo(g);
    liberar_grafo(k33);
    return 0;
}
