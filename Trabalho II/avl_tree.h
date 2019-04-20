#include <stdbool.h>
#pragma once

typedef struct __avl__tree__node{

	int id;
	char balancing_factor;
	struct __avl__tree__node *right;
	struct __avl__tree__node *left;

} avl_tree;

#define MAX(a, b) a > b ? a : b

avl_tree * make__avl__tree();
int __avl__height(const avl_tree *__root);
avl_tree * avl__tree__push(avl_tree *, const int __data);
int __subtree__height(const avl_tree *__root);
avl_tree * __avl__rotate__right(avl_tree *__node);
avl_tree * __avl__rotate__left(avl_tree *__node);
avl_tree * __RR(avl_tree *__node);
avl_tree * __LL(avl_tree *__node);
avl_tree * __RL(avl_tree *__node);
avl_tree * __LR(avl_tree *__node);
int __balancing__factor(const avl_tree *__root);
void avl__tree__infix(const avl_tree *__root);
void avl__tree__posfix(const avl_tree *__root);
void avl__tree__prefix(const avl_tree *__root);
int avl__tree__height(const avl_tree *__root);
avl_tree * avl__tree__pop(avl_tree *__root, const int __key);