#include <stdbool.h>
#pragma once

typedef struct __binary__tree__node{

	int id;
	struct __binary__tree__node *right;
	struct __binary__tree__node *left;

} b_tree;

b_tree * make__binary__tree();
int binary__tree__height(const b_tree *__root);
void binary_tree_pop(b_tree *, const int __key);
void binary__tree__infix(const b_tree *);
void binary__tree__posfix(const b_tree *);
void binary__tree__prefix(const b_tree *);
bool binary__tree__search(const b_tree *, const int __key);
b_tree * binary__tree__pop(b_tree *__root, const int __key);
b_tree * __find__max__value__node(b_tree *__root);
b_tree * __find__min__value__node(b_tree *__root);
b_tree * binary__tree__erase(b_tree *__root);
b_tree * binary__tree__push(b_tree *__root, const int __data);
b_tree * array__to__binary__tree(b_tree *__root, const int *__array, const unsigned __size);