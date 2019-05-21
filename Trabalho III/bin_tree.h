#pragma once

typedef struct __binary__tree__node{

	unsigned id;
	unsigned registry_pointer;
	struct __binary__tree__node *right;
	struct __binary__tree__node *left;

} bin_tree_t;

void make__binary__tree(bin_tree_t **__root);
bin_tree_t * binary__tree__push(bin_tree_t *__root, const unsigned __data, const unsigned __rp);
int binary__tree__search(bin_tree_t *, const unsigned __key);
void binary__tree__infix(const bin_tree_t *__root);