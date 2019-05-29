#include "product.h"
#include "bin_tree_f.h"
#include <stdio.h>
#include <stdlib.h>

extern int range_tree_elements;

/* Create a BST_p_t index tree. */
void make__price__index__tree(BST_p_t **__root)
{

	*__root = NULL;

}

/* Insert DATA and its registry pointer to an BST_p_t 
   tree index. */
BST_p_t * BST__price__push(BST_p_t *__root, const float __data, const unsigned __rp)
{

	if (!__root)
	{

		__root = (BST_p_t *) malloc(sizeof(BST_p_t));
		__root->left = __root->right = NULL;
		__root->key = __data;	
		__root->registry_pointer = __rp;

	}
	else if (__root->key >= __data)
		__root->left = BST__price__push(__root->left, __data, __rp);
	else if (__root->key <= __data)
		__root->right = BST__price__push(__root->right, __data, __rp);

	return __root;

}

/* Range query in the BST index for values greater or  equal 
   to k1 and smaller or equal to k2 on STREAM. */
void BST__price__range__query(BST_p_t *__root, const float __k1, const float __k2, FILE *__STREAM)
{

	if (!__root)
		return;

	if (__k1 <= __root->key)
		BST__price__range__query(__root->left, __k1, __k2, __STREAM);

	if (__k1 <= __root->key && __k2 >= __root->key)
	{

		product_t tmp;
		fseek(__STREAM, __root->registry_pointer * sizeof(product_t), SEEK_SET);
		fread(&tmp, sizeof(product_t), 1, __STREAM);
		++range_tree_elements;

	}

	if (__k2 >= __root->key)
		BST__price__range__query(__root->right, __k1, __k2, __STREAM);

}

/* Search key values greater than k1 in BST index. */
void BST__price__range__gt(BST_p_t *__root, const float __k1, FILE *__STREAM)
{

	if (!__root)
		return;

	BST__price__range__gt(__root->left, __k1, __STREAM);
	BST__price__range__gt(__root->right, __k1, __STREAM);

	if (__root->key > __k1)
	{

		product_t tmp;
		fseek(__STREAM, __root->registry_pointer * sizeof(product_t), SEEK_SET);
		fread(&tmp, sizeof(product_t), 1, __STREAM);
		++range_tree_elements;

	}

	return;

}

/* Search key values lower than k1 in BST index. */
void BST__price__range__lt(BST_p_t *__root, const float __k1, FILE *__STREAM)
{

	if (!__root)
		return;

	BST__price__range__lt(__root->left, __k1, __STREAM);
	BST__price__range__lt(__root->right, __k1, __STREAM);

	if (__root->key < __k1)
	{

		product_t tmp;
		fseek(__STREAM, __root->registry_pointer * sizeof(product_t), SEEK_SET);
		fread(&tmp, sizeof(product_t), 1, __STREAM);
		++range_tree_elements;
	
	}
	
	return;

}

void infix(BST_p_t *__root)
{

	if (__root)
	{

		infix(__root->left);
		printf("%f\n", __root->key);
		infix(__root->right);

	}

}