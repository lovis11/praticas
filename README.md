# Teoria dos grafos - Prof José Reginaldo

Este repositório reúne as implementações desenvolvidas nas práticas da disciplina, abordando diferentes conceitos e algoritmos relacionados à teoria e representação de grafos.

As implementações foram desenvolvidas em **C**, utilizando alocação dinâmica de memória, estruturas encadeadas e algoritmos clássicos de grafos.

## 📂 Estrutura do Projeto

```text
praticas/
├── pratica01/
│   ├── grafo_lista.c
│   ├── grafo_lista.h
│   ├── grafo_matriz.c
│   ├── grafo_matriz.h
│   ├── main.c
│   └── Makefile
│
├── pratica02/
│   ├── busca_largura.c
│   ├── busca_largura.h
│   ├── busca_profundidade.c
│   ├── busca_profundidade.h
│   ├── main.c
│   └── Makefile
│
├── pratica03/
│   ├── dag.c
│   ├── dag.h
│   ├── main.c
│   └── Makefile
│
├── pratica04/
│   ├── conectividade.c
│   ├── conectividade.h
│   ├── planaridade.c
│   ├── planaridade.h
│   ├── main.c
│   └── Makefile
│
├── pratica05/
│   ├── coloracao.c
│   ├── coloracao.h
│   ├── main.c
│   └── Makefile
│
└── README.md
```

---

## 📌 Prática 01 — Representação de Grafos

Implementação das duas principais formas de representação de grafos:

* Matriz de adjacência;
* Lista de adjacência;
* Inserção de arestas;
* Remoção de arestas;
* Verificação de adjacência;
* Cálculo do grau de um vértice;
* Liberação da memória utilizada pelo grafo.

---

## 🔎 Prática 02 — Busca em Grafos

Implementação de algoritmos de busca e propriedades básicas de grafos.

Foram desenvolvidos:

* **BFS — Busca em Largura** utilizando fila;
* **DFS — Busca em Profundidade**;
* DFS recursiva com tempos de entrada e saída;
* Estrutura de fila para BFS;
* Estrutura de pilha para DFS;
* Contagem de componentes conexos;
* Detecção de ciclos;
* Verificação de grafos bipartidos por 2-coloração.

---

## 🔀 Prática 03 — Ordenação Topológica

Implementação de algoritmos utilizados em grafos direcionados acíclicos — **DAGs**.

Foram implementados:

* Ordenação topológica utilizando o **algoritmo de Kahn**;
* Cálculo do grau de entrada dos vértices;
* Ordenação topológica utilizando **DFS**;
* Detecção de ciclos em grafos direcionados;
* Verificação se um grafo é um DAG.

Quando existe um ciclo no grafo, não é possível obter uma ordenação topológica válida.

---

## 🌐 Prática 04 — Conectividade e Planaridade

Implementação de algoritmos relacionados à conectividade e planaridade de grafos.

### Conectividade

Utilização do **algoritmo de Tarjan** para encontrar:

* Vértices de articulação;
* Pontes;
* Tempos de descoberta;
* Valores `low` utilizados durante a DFS.

Uma aresta `(u, v)` é considerada ponte quando:

```text
low[v] > descoberta[u]
```

### Planaridade

Foram implementadas verificações baseadas em:

* Fórmula de Euler;
* Condição:

```text
m <= 3n - 6
```

* Identificação dos grafos clássicos não planares:

  * `K5`;
  * `K3,3`.

Para grafos pequenos, também são realizadas verificações relacionadas aos critérios de Kuratowski utilizados na prática.

---

## 🎨 Prática 05 — Coloração de Grafos

Implementação de algoritmos para coloração de vértices.

Foram desenvolvidos:

* Algoritmo de coloração gulosa;
* Heurística **Welsh-Powell**;
* Ordenação dos vértices por grau decrescente;
* Verificação de conflitos entre cores;
* Cálculo da quantidade de cores utilizadas;
* Verificação de bipartição por 2-coloração.

Na heurística Welsh-Powell, os vértices de maior grau são considerados primeiro durante o processo de coloração.

---

## ⚙️ Compilação

Cada prática possui seu próprio `Makefile`.

Para compilar uma prática, entre em sua respectiva pasta.

Exemplo:

```bash
cd praticas/pratica01
make
```

Depois execute:

### Linux / macOS

```bash
./main
```

### Windows

```bash
main.exe
```

O mesmo procedimento pode ser utilizado para as demais práticas:

```bash
cd praticas/pratica02
make
./main
```

```bash
cd praticas/pratica03
make
./main
```

```bash
cd praticas/pratica04
make
./main
```

```bash
cd praticas/pratica05
make
./main
```

---

## 🧹 Limpando os arquivos compilados

Quando disponível no `Makefile`, utilize:

```bash
make clean
```

Esse comando remove os arquivos gerados durante a compilação.

---

## 🛠️ Tecnologias utilizadas

* Linguagem **C**;
* GCC;
* Make;
* Visual Studio Code;
* Git;
* GitHub.

---

## 🌿 Fluxo de versionamento

Cada prática é desenvolvida em uma branch própria:

```text
pratica-01
pratica-02
pratica-03
pratica-04
pratica-05
```

Fluxo utilizado:

```bash
git checkout main
git pull origin main
git checkout -b pratica-XX
```

Após concluir a implementação:

```bash
git add .
git commit -m "feat: entrega da pratica XX. Refs #ID"
git push origin pratica-XX
```

Por fim, é aberto um **Pull Request** da branch da prática para a branch `main`.

---

## ✅ Conteúdos abordados

Ao longo das práticas foram estudados e implementados:

* Representação de grafos;
* Matriz de adjacência;
* Lista de adjacência;
* BFS;
* DFS;
* Componentes conexos;
* Detecção de ciclos;
* Grafos bipartidos;
* Ordenação topológica;
* DAGs;
* Algoritmo de Kahn;
* Algoritmo de Tarjan;
* Vértices de articulação;
* Pontes;
* Planaridade;
* Fórmula de Euler;
* `K5` e `K3,3`;
* Coloração de grafos;
* Algoritmo guloso;
* Heurística Welsh-Powell.

---

## 📚 Objetivo

O conjunto das práticas tem como objetivo aplicar na linguagem C os principais conceitos estudados em grafos, combinando implementação de estruturas de dados com algoritmos clássicos de busca, conectividade, ordenação, planaridade e coloração.
