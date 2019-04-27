#include "bin_tree.h"
#include <stdio.h>
#include <stdlib.h>

bin_tree * make__binary__tree()
{

	return NULL;

}

bin_tree * binary__tree__push(bin_tree *__root, const int __data)
{

	if (!__root)
	{

		__root = (bin_tree *) malloc(sizeof(bin_tree));
		__root->id = __data;
		__root->left = __root->right = NULL;

	}
	else if (__root->id < __data)
		__root->right = binary__tree__push(__root->right, __data);
	else if (__root->id > __data)
		__root->left = binary__tree__push(__root->left, __data);

	return __root;

}

bin_tree * binary__tree__search(bin_tree *__root, const int __key)
{
	
	if (!__root)
		return NULL;
	
	if (__root->id < __key)
		return binary__tree__search(__root->right, __key);
	else if (__root->id > __key)
		return binary__tree__search(__root->left, __key);
	else
		return __root;
	
	
}

bin_tree * array__to__binary__tree(bin_tree *__root, const int *__array, const unsigned __size)
{

	unsigned i;
	for (i = 0; i < __size; ++i)
		__root = binary__tree__push(__root, __array[i]);

	return __root;

}

void binary__tree__infix(const bin_tree *__root)
{

	if (__root)
	{

		binary__tree__infix(__root->left);
		printf("%d ", __root->id);
		binary__tree__infix(__root->right);

	}

}

void binary__tree__posfix(const bin_tree *__root)
{

	if (__root)
	{

		binary__tree__posfix(__root->left);
		binary__tree__posfix(__root->right);
		printf("%d ", __root->id);

	}

}

void binary__tree__prefix(const bin_tree *__root)
{

	if (__root)
	{

		printf("%d ", __root->id);
		binary__tree__prefix(__root->left);
		binary__tree__prefix(__root->right);

	}

}

bin_tree * __find__max__value__node(bin_tree *__root)
{

	if (!__root)
		return NULL;
	else if (!__root->right)
		return __root;
	else
		return __find__max__value__node(__root->right);

}

bin_tree * __find__min__value__node(bin_tree *__root)
{

	if (!__root)
		return NULL;
	else if (!__root->left)
		return __root;
	else
		return __find__min__value__node(__root->left);

}

bin_tree * binary__tree__pop(bin_tree *__root, const int __key)
{

	bin_tree *tmp;

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

bin_tree * binary__tree__erase(bin_tree *__root)
{

	if (!__root)
		return NULL;

	binary__tree__erase(__root->left);
	binary__tree__erase(__root->right);
	free(__root);

}

int binary__tree__height(const bin_tree *__root)
{

	int lefth, righth;
	if (!__root)
		return -1;

	lefth = binary__tree__height(__root->left);
	righth = binary__tree__height(__root->right);

	return (lefth > righth ? lefth : righth) + 1;

}
