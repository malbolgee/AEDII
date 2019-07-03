#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include "graph.h"

#define __EDGES(x, y) (int)((((x * x) - x) / 2) * y)

static int __parent(int __vertex, int *p);

void make_graph(graph_t *__graph, const unsigned __vertex)
{

	unsigned i;
	char **__adj = (char **) calloc(__vertex, sizeof(char *));

	for (i = 0; i < __vertex; ++i)
		__adj[i] = (char *) calloc(__vertex, sizeof(char));

	__graph->adj = __adj;
	__graph->vertex = __vertex;
	__graph->seen = (char *) calloc(__vertex, sizeof(char));

}


void print_graph(const graph_t __graph, const unsigned __vertex)
{

	unsigned i, j;
	for (i = 0; i < __vertex; ++i)
	{

		for (j = 0; j < __vertex; ++j)
			printf("%hhd ", __graph.adj[i][j]);

		printf("\n");

	}

}

void free_graph(graph_t *__graph, const unsigned __vertex)
{

	unsigned i;
	for (i = 0; i < __vertex; ++i)
		free(__graph->adj[i]);

	free(__graph->adj);

}

void dfs(graph_t __graph, const unsigned __u)
{

	unsigned short i;
	__graph.seen[__u] = true;
	printf("Vertice: %d\n", __u);
	for (i = 0; i < __graph.vertex; ++i)
		if (__graph.adj[__u][i])
			if(!__graph.seen[i])
				dfs(__graph, i);

}

void make_connected(graph_t *__graph, const unsigned __vertex, const float __connectivness)
{

	unsigned tmp;
	unsigned u, v, pu, pv, i;

	int *p = calloc(__vertex, sizeof(int));

	for (i = 1; i < __vertex; ++i)
		p[i] = i;

	tmp = __vertex - 1;

	while (tmp)
	{

		u = rand() % __vertex;
		v = rand() % __vertex;

		while (u == v)
		{

			u = rand() % __vertex;
			v = rand() % __vertex;

		}

		if (!__graph->adj[u][v])
		{

			pu = __parent(u, p);
			pv = __parent(v, p);

			if (pu != pv)
			{

				p[pu] = p[pv];
				__graph->adj[u][v] = __graph->adj[v][u] = 1;
				--tmp;

			}

		}

	}

	tmp = ((__EDGES(__vertex, __connectivness)) - (__vertex - 1)) + 1;

	while (tmp)
	{

		u = rand() % __vertex;
		v = rand() % __vertex;

		while (u == v)
		{

			v = rand() % __vertex;
			u = rand() % __vertex;

		}

		if (!__graph->adj[u][v])
			__graph->adj[u][v] = __graph->adj[v][u] = 1, --tmp;

	}

	free(p);

}

static int __parent(int __vertex, int *p)
{

	if (__vertex == p[__vertex])
		return __vertex;

	return __parent(p[__vertex], p);

}