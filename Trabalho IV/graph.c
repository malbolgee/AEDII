#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include "graph.h"

#define __EDGES(x, y) (int)((((x * x) - x) / 2) * y)

static int __parent(int __vertex, int *p);
static void __all__paths(graph_t *__graph, int __vertex, int *__p, int __k);

extern int k;
extern int ans[1100];
extern aux_t q[1100];

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
	__graph->parent = (unsigned *) calloc(__vertex, sizeof(unsigned));
	__graph->cycle = false;

}

/* Prints the Adjacency Matrix in the screen. */
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
	free(__graph->seen);
	free(__graph->parent);
	__graph->vertex = 0;
	__graph->cycle = false;

}

/* Does a dfs traversal in the graph. */
void dfs(graph_t __graph, const unsigned __u)
{

	unsigned short i;
	__graph.seen[__u] = true;
	ans[k++] = __u;
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

	tmp = ((__EDGES(vertex, __connectivness)) - (vertex - 1));

	while (tmp > 0)
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
	q[__vertex].vertex = __vertex;
	q[__vertex].level = 0;
	__graph.seen[__vertex] = true;

	while (str < end)
	{

		int v = queue[str++];
		for (i = 0; i < __graph.vertex; ++i)
		{

			if (__graph.adj[v][i])
			{
				if (!__graph.seen[i])
				{

					__graph.seen[i] = true;
					queue[end++] = i;
				 	q[i].level = q[v].level + 1;
					q[i].vertex = i;

				}

			}

		}

	}

}

/* Look for a cycle in a given graph. */
void dfs_c(graph_t *__graph, const unsigned __vertex)
{

	unsigned i;
	__graph->seen[__vertex] = true;
	ans[k++] = __vertex;
	if (__graph->cycle)
		return;	

	for (i = 0; i < __graph->vertex; ++i)
	{

		if (__graph->adj[__vertex][i])
			if (!__graph->seen[i])
				__graph->parent[i] = __vertex, dfs_c(__graph, i);
			else if (__graph->parent[__vertex] != i)
				__graph->cycle = true;

	}

}

/* Resets a graph passed as parameter. */
void reset(graph_t *__graph)
{

	unsigned i;
	for (i = 0; i < __graph->vertex; ++i)
		__graph->seen[i] = __graph->parent[i] = 0;

}

/* Creates a graph that does not contain a cycle. */
void make_acyclic_graph(graph_t *__graph)
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

}

/* Find all paths in a graph from a given source. */
void all_path(graph_t *__graph, const unsigned __vertex)
{

	int k = 0;
	int p[__graph->vertex];
	__all__paths(__graph, __vertex, p, k);

}

static void __all__paths(graph_t *__graph, int __vertex, int *__path,int __k)
{

	int i, end = 1;
	__graph->seen[__vertex] = 1;
	__path[__k] = __vertex;

	for (i = 0; i < __graph->vertex; ++i)
		if (__graph->adj[__vertex][i] && __graph->seen[i] != 1)
			__all__paths(__graph, i, __path, __k + 1), end = 0;

	if (end)
	{

		for (i = 0; i <= __k; ++i)
			printf("%d ", __path[i]);
		
		printf("\n");
		
	}

	__graph->seen[__vertex] = 2;

}