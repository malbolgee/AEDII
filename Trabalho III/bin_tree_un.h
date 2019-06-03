#include <stdio.h>
#pragma once

typedef struct __BST__un__index{

	unsigned key;
	unsigned registry_pointer;
	struct __BST__un__index *right;
	struct __BST__un__index *left;

} BSTun_t;

void      make__un__index__tree(BSTun_t **__root);
BSTun_t * BST__un__push(BSTun_t *__root, const unsigned __data, const unsigned __rp);
void      BST__un__range__query(BSTun_t *__root, const unsigned __k1, const unsigned __k2, FILE *__STREAM);
void      BST__un__range__gt(BSTun_t *__root, const unsigned __k1, FILE *__STREAM);
void      BST__un__range__lt(BSTun_t *__root, const unsigned __k1, FILE *__STREAM);
void	  infix(BSTun_t *__root);