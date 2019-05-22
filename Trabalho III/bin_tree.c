#include "bin_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Create a instance of a bin_tree_t pointer by putting NULL in it. */
void make__binary__tree(bin_tree_t **__root)
{

	*__root = NULL;

}

/* Inserts data and its registry pointer into a BST. */
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

/* Search for key on a BST. */
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

/* Range query in the BST index for values greater or  equal 
   to k1 and smaller or equal to k2 on STREAM. */
void binary__tree__range__query(bin_tree_t *__root, const unsigned __k1, const unsigned __k2, FILE *__stream)
{

	if (!__root)
		return;

	if (__k1 <= __root->id)
		binary__tree__range__query(__root->left, __k1, __k2, __stream);

	if (__k1 <= __root->id && __k2 >= __root->id)
	{

		product_t tmp;
		fseek(__stream, __root->registry_pointer * sizeof(product_t), SEEK_SET);
		fread(&tmp, sizeof(product_t), 1, __stream);
		info_print(tmp);

	}

	if (__k2 >= __root->id)
		binary__tree__range__query(__root->right, __k1, __k2, __stream);


}

/* Does a infix traversal on a BST. */
void binary__tree__infix(const bin_tree_t *__root)
{

	if (__root)
	{

		binary__tree__infix(__root->left);
		printf("%d ", __root->id);
		binary__tree__infix(__root->right);

	}

}

/* Prints a product_t type fields. */
void info_print(product_t produto)
{

	printf("Id: %d\nNome: %s\nDescrição: %s\nPreço: %.2f\nDisponibilidade: %d\nVencimento: %d\n\n",
		produto.id, produto.nome, produto.descricao, produto.preco, produto.disponibilidade, produto.vencimento);

}