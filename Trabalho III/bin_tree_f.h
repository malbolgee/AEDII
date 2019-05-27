#include <stdio.h>
#pragma once

typedef struct __BST__prince__index{

	float key;
	unsigned registry_pointer;
	struct __BST__prince__index *right;
	struct __BST__prince__index *left;

} BST_p_t;

void    BST__price__range__query(BST_p_t *__root, const float __k1, const float __k2, FILE *__STREAM);
