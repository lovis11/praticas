#ifndef BUSCA_PROFUNDIDADE_H
#define BUSCA_PROFUNDIDADE_H

#include "busca_largura.h"

typedef struct {
    int *dados;
    int topo, capacidade;
} Pilha;

void pilha_inicializar(Pilha *p, int capacidade);
int pilha_vazia(Pilha *p);
void empilhar(Pilha *p, int valor);
int desempilhar(Pilha *p);
void pilha_liberar(Pilha *p);

void dfs_recursiva(GrafoLista *g, int u, int *visitado,
                   int *tempo_entrada, int *tempo_saida,
                   int *pred, int *tempo);
void dfs_iterativa(GrafoLista *g, int origem, int *visitado);
int contar_componentes(GrafoLista *g);
int tem_ciclo(GrafoLista *g);

#endif
