#include <stdbool.h>
#pragma once

typedef struct __avl__tree__node{

	int id;
	char balancing_factor;
	struct __avl__tree__node *right;
	struct __avl__tree__node *left;

} avl_tree;

