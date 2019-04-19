#include "b_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

b_tree * binary__tree()
{

	return NULL;

}

b_tree * binary__tree__push(b_tree *__root, const int __data)
{

	if (!__root)
	{

		__root = (b_tree *) malloc(sizeof(b_tree));
		__root->id = __data;
		__root->left = __root->right = NULL;

	}
	else if (__root->id < __data)
		__root->right = binary__tree__push(__root->right, __data);
	else if (__root->id > __data)
		__root->left = binary__tree__push(__root->left, __data);

	return __root;

}

bool binary__tree__search(const b_tree *__root, const int __key)
{

	if (!__root)
		return false;
	
	if (__root->id < __key)
		binary__tree__search(__root->right, __key);
	else if (__root->id > __key)
		binary__tree__search(__root->left, __key);
	else
		return true;

}

b_tree * array__to__binary__tree(b_tree *__root, const int *__array, const unsigned __size)
{

	unsigned i;
	for (i = 0; i < __size; ++i)
		__root = binary__tree__push(__root, __array[i]);

	return __root;

}

void binary__tree__infix(const b_tree *__root)
{

	if (__root)
	{

		binary__tree__infix(__root->left);
		printf("%d ", __root->id);
		binary__tree__infix(__root->right);

	}

}

void binary__tree__posfix(const b_tree *__root)
{

	if (__root)
	{

		binary__tree__posfix(__root->left);
		binary__tree__posfix(__root->right);
		printf("%d ", __root->id);

	}

}

void binary__tree__prefix(const b_tree *__root)
{

	if (__root)
	{

		printf("%d ", __root->id);
		binary__tree__prefix(__root->left);
		binary__tree__prefix(__root->right);

	}

}

b_tree * __find__max__value__node(b_tree *__root)
{

	if (!__root)
		return NULL;
	else if (!__root->right)
		return __root;
	else
		return __find__max__value__node(__root->right);

}

b_tree * __find__min__value__node(b_tree *__root)
{

	if (!__root)
		return NULL;
	else if (!__root->left)
		return __root;
	else
		return __find__min__value__node(__root->left);

}

b_tree * binary__tree__pop(b_tree *__root, const int __key)
{

	b_tree *tmp;

	if (!__root)
		return NULL;
	else if (__root->id > __key)
		__root->left = binary__tree__pop(__root->left, __key);
	else if (__root->id < __key)
		__root->right = binary__tree__pop(__root->right, __key);
	else if (__root->left && __root->right)
	{

		tmp = __find__max__value__node(__root->left);
		__root->id = tmp->id;
		__root->left = binary__tree__pop(__root->left, __root->id);

	}
	else
	{

		tmp = __root;
		if (!__root->left)
			__root = __root->right;
		else if (!__root->right)
			__root = __root->left;

		free(tmp);

	}

	return __root;

}

b_tree * binary__tree__erase(b_tree *__root)
{

	if (!__root)
	{

		binary__tree__erase(__root->left);
		binary__tree__erase(__root->right);
		free(__root);

	}

	return NULL;

}

int binary__tree__height(const b_tree *__root)
{

	int lefth, righth;
	if (!__root)
		return -1;

	lefth = binary__tree__height(__root->left);
	righth = binary__tree__height(__root->right);

	return (lefth > righth ? lefth : righth) + 1;

}
