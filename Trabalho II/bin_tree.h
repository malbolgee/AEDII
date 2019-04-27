#pragma once

typedef struct __binary__tree__node{

	int id;
	struct __binary__tree__node *right;
	struct __binary__tree__node *left;

} bin_tree;

bin_tree * make__binary__tree();
bin_tree * binary__tree__push(bin_tree *__root, const int __data);
bin_tree * binary__tree__search(bin_tree *, const int __key);
bin_tree * array__to__binary__tree(bin_tree *__root, const int *__array, const unsigned __size);
void binary__tree__infix(const bin_tree *);
void binary__tree__posfix(const bin_tree *);
void binary__tree__prefix(const bin_tree *);
bin_tree * __find__max__value__node(bin_tree *__root);
bin_tree * __find__min__value__node(bin_tree *__root);
bin_tree * binary__tree__pop(bin_tree *__root, const int __key);
bin_tree * binary__tree__erase(bin_tree *__root);
int binary__tree__height(const bin_tree *__root);