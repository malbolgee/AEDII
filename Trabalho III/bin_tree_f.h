#include <stdio.h>
#pragma once

typedef struct __BST__prince__index{

	float key;
	unsigned registry_pointer;
	struct __BST__prince__index *right;
	struct __BST__prince__index *left;

} BST_p_t;

void      make__price__index__tree(BST_p_t **__root);
BST_p_t * BST__price__push(BST_p_t *__root, const float __data, const unsigned __rp);
void      BST__price__range__query(BST_p_t *__root, const float __k1, const float __k2, FILE *__STREAM);
void      BST__price__range__gt(BST_p_t *__root, const float __k1, FILE *__STREAM);
void      BST__price__range__lt(BST_p_t *__root, const float __k1, FILE *__STREAM);
void	  infix(BST_p_t *__root);