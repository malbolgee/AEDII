#include "bin_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void make__binary__tree(bin_tree_t **__root)
{

	*__root = NULL;

}

bin_tree_t * binary__tree__push(bin_tree_t *__root, const unsigned __data, const unsigned __rp)
{

	if (!__root)
	{

		__root = (bin_tree_t *) malloc(sizeof(bin_tree_t));
		__root->id = __data;
		__root->registry_pointer = __rp;
		__root->left = __root->right = NULL;

	}
	else if (__root->id < __data)
		__root->right = binary__tree__push(__root->right, __data, __rp);
	else if (__root->id > __data)
		__root->left = binary__tree__push(__root->left, __data, __rp);

	return __root;

}

int binary__tree__search(bin_tree_t *__root, const unsigned __key)
{
	
	if (!__root)
		return -1;
	
	if (__root->id < __key)
		return binary__tree__search(__root->right, __key);
	else if (__root->id > __key)
		return binary__tree__search(__root->left, __key);
	else
		return __root->registry_pointer;
	
}

void binary__tree__infix(const bin_tree_t *__root)
{

	if (__root)
	{

		binary__tree__infix(__root->left);
		printf("%d ", __root->id);
		binary__tree__infix(__root->right);

	}

}
