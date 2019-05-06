#include "avl_tree.h"
#include <stdio.h>
#include <stdlib.h>

void make__avl__tree(avl_tree **__root)
{

	*__root =  NULL;

}

avl_tree * avl__tree__push(avl_tree *__root, const int __data)
{

	if (!__root)
	{

		__root = (avl_tree *) malloc(sizeof(avl_tree));
		__root->left = __root->right = NULL;
		__root->id = __data;

	}
	else if (__root->id < __data)
	{

		__root->right = avl__tree__push(__root->right, __data);
		if (__balancing__factor(__root) == -2)
			if(__root->right->id < __data)
				__root = __LL(__root);
			else
				__root = __RL(__root);

	}
	else if (__root->id > __data)
	{

		__root->left = avl__tree__push(__root->left, __data);
		if (__balancing__factor(__root) == 2)
			if (__root->left->id > __data)
				__root = __RR(__root);
			else
				__root = __LR(__root);

	}

	__root->balancing_factor = __subtree__height(__root);
	return __root;

}

avl_tree * avl__tree__pop(avl_tree *__root, const int __key)
{

	avl_tree *aux;

	if (!__root)
		return NULL;
	else if (__root->id < __key)
	{

		__root->right = avl__tree__pop(__root->right, __key);
		if (__balancing__factor(__root) == 2)
			if (__balancing__factor(__root->left) >= 0)
				__root = __RR(__root);
			else
				__root = __LR(__root);

	}
	else if (__root->id > __key)
	{

		__root->left = avl__tree__pop(__root->left, __key);
		if (__balancing__factor(__root) == -2)
			if (__balancing__factor(__root->left) <= 0)
				__root = __LL(__root);
			else
				__root = __RL(__root);

	}
	else if (__root->right)
	{

		aux = __root->right;

		while (aux->left)
			aux = aux->left;

		__root->id = aux->id;
		__root->right = avl__tree__pop(__root->right, aux->id);

		if (__balancing__factor(__root) == 2)
			if(__balancing__factor(__root->left) >= 0)
				__root = __RR(__root);
			else
				__root = __LR(__root);

		free(aux);

	}
	else
		return __root->left;

	__root->balancing_factor = __subtree__height(__root);
	return __root;

}	


static int __subtree__height(const avl_tree *__root)
{

	int lefth, righth;
	if (!__root)
		return 0;

	if (!__root->left)
		lefth = 0;
	else
		lefth = __root->left->balancing_factor + 1;

	if (!__root->right)
		righth = 0;
	else
		righth = __root->right->balancing_factor + 1;

	return __MAX(righth, lefth);

}

static avl_tree * __avl__rotate__right(avl_tree *__node)
{

	avl_tree *aux;
	aux = __node->left;
	__node->left = aux->right;
	aux->right = __node;
	__node->balancing_factor = __subtree__height(__node);
	aux->balancing_factor = __subtree__height(aux);
	return aux;

}

static avl_tree * __avl__rotate__left(avl_tree *__node)
{

	avl_tree *aux;
	aux = __node->right;
	__node->right = aux->left;
	aux->left = __node;
	__node->balancing_factor = __subtree__height(__node);
	aux->balancing_factor = __subtree__height(aux);
	return aux;

}

static avl_tree * __LL(avl_tree *__node)
{

	__node = __avl__rotate__left(__node);
	return __node;

}

static avl_tree * __RR(avl_tree *__node)
{

	__node = __avl__rotate__right(__node);
	return __node;

}

static avl_tree * __LR(avl_tree *__node)
{

	__node->left = __avl__rotate__left(__node->left);
	__node = __avl__rotate__right(__node);
	return __node;

}

static avl_tree * __RL(avl_tree *__node)
{

	__node->right = __avl__rotate__right(__node->right);
	__node = __avl__rotate__left(__node);
	return __node;

}

static int __balancing__factor(const avl_tree *__root)
{

	int lefth, righth;
	if (!__root)
		return 0;

	if (__root->left)
		lefth = __root->left->balancing_factor + 1;
	else
		lefth = 0;

	if (__root->right)
		righth = __root->right->balancing_factor + 1;
	else
		righth = 0;

	return lefth - righth;

}

void avl__tree__infix(const avl_tree *__root)
{

	if (__root)
	{

		avl__tree__infix(__root->left);
		printf("%d ", __root->id);
		avl__tree__infix(__root->right);

	}

}

void avl__tree__posfix(const avl_tree *__root)
{

	if (__root)
	{

		avl__tree__posfix(__root->left);
		avl__tree__posfix(__root->right);
		printf("%d ", __root->id);
		
	}

}

void avl__tree__prefix(const avl_tree *__root)
{

	if (__root)
	{
		
		printf("%d ", __root->id);
		avl__tree__prefix(__root->left);
		avl__tree__prefix(__root->right);

	}

}

int avl__tree__height(const avl_tree *__root)
{

	int lefth, righth;
	if (!__root)
		return -1;

	lefth = avl__tree__height(__root->left);
	righth = avl__tree__height(__root->right);

	return __MAX(lefth, righth) + 1;

}

avl_tree * avl__tree__search(avl_tree *__root, const int __key)
{

	if (!__root)
		return NULL;

	if (__root->id < __key)
		return avl__tree__search(__root->right, __key);
	else if (__root->id > __key)
		return avl__tree__search(__root->left, __key);
	else
		return __root;

}

avl_tree * avl__tree__erase(avl_tree *__root)
{

	if (!__root)
	{

		avl__tree__erase(__root->left);
		avl__tree__erase(__root->right);
		free(__root);

	}

	return NULL;

}

avl_tree * array__to__avl__tree(avl_tree *__root, const int *__array, const unsigned __size)
{

	unsigned i;
	for (i = 0; i < __size; ++i)
		__root = avl__tree__push(__root, __array[i]);

	return __root;

}