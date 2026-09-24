#include <stdio.h>
#include <stdlib.h>
#include "grafo_matriz.h"
#include "grafo_lista.h"

static void testar_matriz(void) {
    GrafoMatriz *g = criar_grafo_matriz(5);

    if (g == NULL) {
        printf("Erro ao criar o grafo por matriz.\n");
        return;
    }

    inserir_aresta_matriz(g, 0, 1);
    inserir_aresta_matriz(g, 0, 2);
    inserir_aresta_matriz(g, 1, 3);
    inserir_aresta_matriz(g, 2, 4);

    printf("=== GRAFO COM MATRIZ DE ADJACENCIA ===\n");
    printf("Grau do vertice 0: %d\n", grau_matriz(g, 0));
    printf("0 e 2 sao adjacentes? %s\n",
           sao_adjacentes_matriz(g, 0, 2) ? "Sim" : "Nao");
    printf("0 e 4 sao adjacentes? %s\n",
           sao_adjacentes_matriz(g, 0, 4) ? "Sim" : "Nao");

    remover_aresta_matriz(g, 0, 2);
    printf("Apos remover (0,2), 0 e 2 sao adjacentes? %s\n",
           sao_adjacentes_matriz(g, 0, 2) ? "Sim" : "Nao");
    printf("Novo grau do vertice 0: %d\n\n", grau_matriz(g, 0));

    liberar_grafo_matriz(g);
}

static void testar_lista(void) {
    GrafoLista *g = criar_grafo_lista(5);

    if (g == NULL) {
        printf("Erro ao criar o grafo por lista.\n");
        return;
    }

    inserir_aresta_lista(g, 0, 1);
    inserir_aresta_lista(g, 0, 2);
    inserir_aresta_lista(g, 1, 3);
    inserir_aresta_lista(g, 2, 4);

    printf("=== GRAFO COM LISTA DE ADJACENCIA ===\n");
    printf("Grau do vertice 0: %d\n", grau_lista(g, 0));
    printf("0 e 2 sao adjacentes? %s\n",
           sao_adjacentes_lista(g, 0, 2) ? "Sim" : "Nao");
    printf("0 e 4 sao adjacentes? %s\n",
           sao_adjacentes_lista(g, 0, 4) ? "Sim" : "Nao");

    remover_aresta_lista(g, 0, 2);
    printf("Apos remover (0,2), 0 e 2 sao adjacentes? %s\n",
           sao_adjacentes_lista(g, 0, 2) ? "Sim" : "Nao");
    printf("Novo grau do vertice 0: %d\n", grau_lista(g, 0));

    liberar_grafo_lista(g);
}

int main(void) {
    testar_matriz();
    testar_lista();
    return EXIT_SUCCESS;
}
