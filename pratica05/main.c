#include <stdio.h>
#include <stdlib.h>
#include "coloracao.h"

static void imprimir_cores(const char *nome, int *cores, int n, int num_cores) {
    int i;
    printf("%s (%d cores):\n", nome, num_cores);
    for (i = 0; i < n; i++)
        printf("  vertice %d -> cor %d\n", i, cores[i] + 1);
}

int main(void) {
    GrafoLista *g = criar_grafo_lista(5);
    int num_gulosa, num_wp;
    int *gulosa, *wp;

    if (!g) return 1;

    /* Ciclo impar C5: precisa de 3 cores e nao e bipartido. */
    inserir_aresta(g, 0, 1);
    inserir_aresta(g, 1, 2);
    inserir_aresta(g, 2, 3);
    inserir_aresta(g, 3, 4);
    inserir_aresta(g, 4, 0);

    gulosa = coloracao_gulosa(g, &num_gulosa);
    wp = coloracao_welsh_powell(g, &num_wp);

    if (!gulosa || !wp) {
        free(gulosa); free(wp); liberar_grafo(g);
        return 1;
    }

    imprimir_cores("Coloracao gulosa", gulosa, g->n, num_gulosa);
    printf("\n");
    imprimir_cores("Welsh-Powell", wp, g->n, num_wp);
    printf("\nEh bipartido? %s\n", eh_bipartido(g) ? "Sim" : "Nao");

    free(gulosa);
    free(wp);
    liberar_grafo(g);
    return 0;
}
