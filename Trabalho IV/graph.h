#include <stdbool.h>

#pragma once

typedef struct __graph__type{

	char *seen;
	char **adj;
	unsigned vertex;
	unsigned *parent;
	bool cycle;

} graph_t;

typedef struct {

	int vertex, level;

} aux_t;

void make_graph(graph_t *__graph, const unsigned __vertex);
void print_graph(const graph_t __graph);
void dfs(graph_t __graph, const unsigned __vertex);
void make_connected(graph_t *__graph, const float __connectivness);
void free_graph(graph_t *__graph);
void bfs(graph_t __graph, const unsigned __vertex);
void dfs_c(graph_t *__graph, const unsigned __vertex);
void reset(graph_t *__graph);
void make_acyclic_graph(graph_t *__graph);