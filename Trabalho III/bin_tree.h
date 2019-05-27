#include <stdio.h>
#include "product.h"
#pragma once

typedef struct __BST__id__index{

	unsigned id;
	unsigned registry_pointer;
	struct __BST__id__index *right;
	struct __BST__id__index *left;

} BST_t;

void    make__binary__tree(BST_t **__root);
BST_t * BST__id__push(BST_t *__root, const unsigned __data, const unsigned __rp);
void    BST__id__search(BST_t *__root, const unsigned __key, FILE *__STREAM);