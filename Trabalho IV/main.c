#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "graph.h"

#define GRN  "\x1B[32m"
#define NOC "\033[0m"
#define RED  "\x1B[31m"

int k;
aux_t q[1100] = { 0 };
int ans[1100] = { 0 };
int compara(const void *, const void *);

int main(int argc, char **argv)
{

	int u, v;
	int i, j, z;
	int tam, idx;
	float cn[5] = {0.25, 0.50, 0.75, 1};
	srand(clock());
	graph_t grafo;
	clock_t t_ini, t_fim;
	double soma1, soma2;

	soma1 = soma2 = 0;
	/* Tempos de caminhamento com DFS e BFS. */
	for (i = 0; i < 20; ++i)
	{

		tam = (rand() % 500) + 10;
		idx = rand() % 4;
		make_graph(&grafo, tam);
		make_connected(&grafo, cn[idx]);
		printf("Quantidade de Vértices: %d\n", tam);
		printf("Conectividade: %.f%%\n", cn[idx] * 100);

		k = 0;
		printf("%sCAMINHAMENTO DFS%s\n\n", RED, NOC);
		t_ini = clock();
		dfs(grafo, rand() % tam);
		t_fim = clock();
		soma1 += (double)((t_fim - t_ini) * 1000.0) / CLOCKS_PER_SEC;

		bool flag = false;
		printf("{ ");
		for (j = 0; j < k; ++j)
			if (flag)
				printf(", %d", ans[j]);
			else
				printf("%d", ans[j]), flag = true;

		printf(" }");

		printf("\n\n");

		reset(&grafo);
		for (j = 0; j < 1100; ++j)
			q[j].level = q[j].vertex = 0;	

		int ver = rand() % tam;
		grafo.parent[ver] = -1;
		t_ini = clock();
		bfs(grafo, ver);
		t_fim = clock();
		
		soma2 += (double)((t_fim - t_ini) * 1000.0) / CLOCKS_PER_SEC;

		qsort(q, tam, sizeof(aux_t), compara);

		int ant = 0;
		printf("%sCAMINHAMENTO BFS%s\n\n", RED, NOC);
		printf("%sNível %d%s\n", GRN, ant, NOC);
		for (j = 0; j < tam; ++j)
		{
			
			if (q[j].level == ant)
				printf("%d ", q[j].vertex);
			else
			{

				ant = q[j].level; 
				printf("\n%sNível %d%s\n", GRN, ant, NOC);
				printf("%d ", q[j].vertex);

			}
		}
		
		printf("\n\n");
		free_graph(&grafo);

		printf("###################################################################\n\n");

	}

	printf("Média de tempo com caminhamento DFS %lf\n", soma1 / 20);
	printf("Média de tempo com caminhamento BFS %lf\n", soma2 / 20);

	/*Todos os caminhos usando DFS. */

	tam = (rand() % 10) + 10;
	graph_t grafo_p;

	make_graph(&grafo_p, tam);
	make_connected(&grafo_p, 0.20);
	printf("%sTODOS OS CAMINHOS USANDO DFS%s\n\n", RED, NOC);
	for (i = 0, z = 1; i < tam; ++i, ++z)
	{

		printf("%sCaminho %d%s\n", GRN, z, NOC);
		k = 0;
		dfs(grafo_p, i);
		bool flag = false;
		printf("{ ");
		for (j = 0; j < k; ++j)
			if (flag)
				printf(", %d", ans[j]);
			else
				printf("%d", ans[j]), flag = true;

		printf(" }");

		printf("\n");
		reset(&grafo_p);

	}

	printf("\n\n");
	graph_t grafo_4;

	printf("%sDETECÇÃO DE CICLOS USANDO DFS%s\n", RED, NOC);
	for (i = 0; i < 10; ++i)
	{

		int x = rand() % 2;
		idx = rand() % 4;
		tam = (rand() % 30) + 10;

		if (x)
		{
			
			k = 0;
			make_graph(&grafo_4, tam);
			make_connected(&grafo_4, cn[idx]);
			dfs_c(&grafo_4, rand() % tam);

		}
		else
		{
			
			k = 0;
			make_graph(&grafo_4, tam);
			make_acyclic_graph(&grafo_4);
			dfs_c(&grafo_4, rand() % tam);

		}

		bool flag = false;
		printf("{ ");
		for (j = 0; j < k; ++j)
			if (flag)
				printf(", %d", ans[j]);
			else
				printf("%d", ans[j]), flag = true;

		printf(" }");

		printf("\n%s%s%s\n", GRN, grafo_4.cycle ? "Ciclo!" : "Sem ciclo!", NOC);
		free_graph(&grafo_4);

	}

	return 0;

}

int compara(const void *a, const void *b)
{

	return ((aux_t *)a)->level - ((aux_t *)b)->level;

}