#include "bin_tree.h"
#include "product.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Create a instance of a BST_t pointer by putting NULL in it. */
void make__binary__tree(BST_t **__root)
{

	*__root = NULL;

}

/* Inserts data and its registry pointer into a BST. */
BST_t * BST__id__push(BST_t *__root, const unsigned __data, const unsigned __rp)
{

	if (!__root)
	{

		__root = (BST_t *) malloc(sizeof(BST_t));
		__root->id = __data;
		__root->registry_pointer = __rp;
		__root->left = __root->right = NULL;

	}
	else if (__root->id < __data)
		__root->right = BST__id__push(__root->right, __data, __rp);
	else if (__root->id > __data)
		__root->left = BST__id__push(__root->left, __data, __rp);

	return __root;

}

/* Search for key on a BST. */
void BST__id__search(BST_t *__root, const unsigned __key, FILE *__STREAM)
{
	
	if (!__root)
		return;
	
	if (__root->id < __key)
		return BST__id__search(__root->right, __key, __STREAM);
	else if (__root->id > __key)
		return BST__id__search(__root->left, __key, __STREAM);
	else
	{

		product_t tmp;
		fseek(__STREAM, __root->registry_pointer * sizeof(product_t), SEEK_SET);
		fread(&tmp, sizeof(product_t), 1, __STREAM);
		return;

	}
	
}
