#include "product.h"
#include "bin_tree_un.h"
#include <stdio.h>
#include <stdlib.h>

extern int range_tree_elements;

/* Create a BSTun_t index tree. */
void make__un__index__tree(BSTun_t **__root)
{

	*__root = NULL;

}

/* Insert DATA and its registry pointer to an BSTun_t 
   tree index. */
BSTun_t * BST__un__push(BSTun_t *__root, const unsigned __data, const unsigned __rp)
{

	if (!__root)
	{

		__root = (BSTun_t *) malloc(sizeof(BSTun_t));
		__root->left = __root->right = NULL;
		__root->key = __data;	
		__root->registry_pointer = __rp;

	}
	else if (__root->key > __data)
		__root->left = BST__un__push(__root->left, __data, __rp);
	else
		__root->right = BST__un__push(__root->right, __data, __rp);

	return __root;

}

/* Range query in the BST index for values greater or  equal 
   to k1 and smaller or equal to k2 on STREAM. */
void BST__un__range__query(BSTun_t *__root, const unsigned __k1, const unsigned __k2, FILE *__STREAM)
{

	if (!__root)
		return;

	if (__k1 < __root->key)
		BST__un__range__query(__root->left, __k1, __k2, __STREAM);

	if (__k1 < __root->key && __k2 > __root->key)
	{

		product_t tmp;
		fseek(__STREAM, __root->registry_pointer * sizeof(product_t), SEEK_SET);
		fread(&tmp, sizeof(product_t), 1, __STREAM);

	}

	if (__k2 > __root->key)
		BST__un__range__query(__root->right, __k1, __k2, __STREAM);

}

/* Search key values greater than k1 in BST index. */
void BST__un__range__gt(BSTun_t *__root, const unsigned __k1, FILE *__STREAM)
{

	if (!__root)
		return;

	if (__root->key >= __k1)
		BST__un__range__gt(__root->left, __k1, __STREAM);

	BST__un__range__gt(__root->right, __k1, __STREAM);
	
	if (__root->key >= __k1)
	{

		product_t tmp;
		fseek(__STREAM, __root->registry_pointer * sizeof(product_t), SEEK_SET);
		fread(&tmp, sizeof(product_t), 1, __STREAM);

	}

}

/* Search key values lower than k1 in BST index. */
void BST__un__range__lt(BSTun_t *__root, const unsigned __k1, FILE *__STREAM)
{

	if (!__root)
		return;

	BST__un__range__lt(__root->left, __k1, __STREAM);

	if (__root->key <= __k1)
		BST__un__range__lt(__root->right, __k1, __STREAM);

	if (__root->key <= __k1)
	{

		product_t tmp;
		fseek(__STREAM, __root->registry_pointer * sizeof(product_t), SEEK_SET);
		fread(&tmp, sizeof(product_t), 1, __STREAM);
	
	}
	
}

void infix(BSTun_t *__root)
{

	if (__root)
	{

		infix(__root->left);
		printf("%u\n", __root->key);
		infix(__root->right);

	}

}