#include <stdio.h>
#pragma once

typedef struct __product__type{

	unsigned id;
	char nome[51];
	char descricao[101];
	float preco;
	unsigned disponibilidade;
	unsigned vencimento;

} product_t;

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
void binary__tree__range__query(bin_tree_t *__root, const unsigned __k1, const unsigned __k2s, FILE *__stream);
void info_print(product_t produto);