#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include "graph.h"

#define __EDGES(x, y) (int)((((x * x) - x) / 2) * y)

static int __parent(int __vertex, int *p);

/* Creates an adjacency matrix with a vertex number of vertices. */
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

/* prints the Adjacency Matrix in the screen. */
void print_graph(const graph_t __graph)
{

	unsigned i, j;
	unsigned vertex = __graph.vertex;

	for (i = 0; i < vertex; ++i)
	{

		for (j = 0; j < vertex; ++j)
			printf("%hhd ", __graph.adj[i][j]);

		printf("\n");

	}

}

/* Destroy the graph passed as a parameter. */
void free_graph(graph_t *__graph)
{

	unsigned i, vertex;
	vertex = __graph->vertex;
	for (i = 0; i < vertex; ++i)
		free(__graph->adj[i]);

	free(__graph->adj);

}

/* Does a dfs traversal in the graph. */
void dfs(graph_t __graph, const unsigned __u)
{

	unsigned short i;
	__graph.seen[__u] = true;
	printf("%d - ", __u);
	for (i = 0; i < __graph.vertex; ++i)
		if (__graph.adj[__u][i])
			if(!__graph.seen[i])
				dfs(__graph, i);

}

/* Creates a conected graph with given amount of connectivness. */
void make_connected(graph_t *__graph, const float __connectivness)
{

	unsigned tmp, vertex;
	unsigned u, v, pu, pv, i;

	vertex = __graph->vertex;
	int *p = calloc(vertex + 1, sizeof(int));

	for (i = 1; i <= vertex; ++i)
		p[i] = i;

	tmp = vertex - 1;

	while (tmp)
	{

		u = rand() % vertex;
		v = rand() % vertex;

		while (u == v)
		{

			u = rand() % vertex;
			v = rand() % vertex;

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

	tmp = ((__EDGES(vertex, __connectivness)) - (vertex - 1)) + 1;

	while (tmp)
	{

		u = rand() % vertex;
		v = rand() % vertex;

		while (u == v)
		{

			v = rand() % vertex;
			u = rand() % vertex;

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

/* Does a bfs traversal in the graph. */
void bfs(graph_t __graph, const unsigned __vertex)
{

	int i, j, str, end;
	int queue[__graph.vertex];

	str = end = 0;
	queue[end++] = __vertex;
	__graph.seen[__vertex] = true;

	print_graph(__graph);

	while (str < end)
	{

		int v = queue[str++];
		printf("Vértice: %d\n", v);
		for (i = 0; i < __graph.vertex; ++i)
		{
			
			if (__graph.adj[v][i])
				if (!__graph.seen[i])
					__graph.seen[i] = true, queue[end++] = i;

		}

	}

}