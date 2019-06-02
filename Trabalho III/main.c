#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "bin_tree.h"
#include "hash.h"
#include "product.h"
#include "bin_tree_f.h"
#include "fort.h"

#define MAXID 15000

#define SWAP(a, b) {\
	float aux = a;\
	a = b;\
	b = aux;\
}

void result_table_id(char (*data)[]);
void result_table_price(char (*data)[]);

int range_tree_elements;
unsigned __stt = COL_START_P;
unsigned __end = COL_START_P;
unsigned hash_colisions;

void main ()
{

	unsigned i = 0;
	srand(time(NULL));
	BST_t *arvore;
	product_t produto;
	hash_t *hash_produto;
	BST_p_t *price_index_tree;
	clock_t t_ini, t_fim;
	double soma1, soma2, soma3, soma4, soma5, soma6;
	char data[6][60] = { 0 };

	// Criação da Árvore e da tabela Hash;
	make__binary__tree(&arvore);
	make__price__index__tree(&price_index_tree);
	hash_produto = make__hash__table(MAX_HASH_SIZE);

	// Abertura dos arquivos para leitura e para escrita;
	FILE *bin = fopen("produtos", "wb");
	FILE *json = fopen("out", "r");

	/* Escrevendo os registros no arquivo binário e suas 
	   chaves nas estruturas de indexação */

	hash_colisions = 0;
	while (get_product_info(&produto, json) != EOF)
	{

		fwrite(&produto, sizeof(product_t), 1, bin);
		hash__push(hash_produto, produto.id, i);
		arvore = BST__id__push(arvore, produto.id, i);
		price_index_tree = BST__price__push(price_index_tree, produto.price, i);
		++i;

	}

	// Fechando os arquivos;
	fclose(bin);
	fclose(json);

	printf("Quantidade de colisões na tabela hash: %d\n", hash_colisions);
	printf("Porcentagem de colisões na tebala hash: %.2f%%\n\n", (hash_colisions / 10000.0f) * 100);

	// Abertura do arquivo 'produtos' no modo leitura;
	bin = fopen("produtos", "rb");
		
	// Tempos das buscas com árvore, com hash e sequencial
	soma1 = soma2 = soma3 = 0;
	for (i = 0; i < 30; ++i)
	{

		unsigned key = (rand() % MAXID);

		t_ini = clock();
		BST__id__search(arvore, key, bin);
		t_fim = clock();
		soma1 += (double)((t_fim - t_ini) * 1000.0) / CLOCKS_PER_SEC;

		t_ini = clock();
		hash__find(hash_produto, key, bin);
		t_fim = clock();
		soma2 += (double)((t_fim - t_ini) * 1000.0) / CLOCKS_PER_SEC;

		t_ini = clock();
		linear__registry__search(key, bin);
		t_fim = clock();
		soma3 += (double)((t_fim - t_ini) * 1000.0) / CLOCKS_PER_SEC;
		rewind(bin);

	}

	sprintf(data[0], "%lf", soma1 / 30); sprintf(data[1], "%lf", soma2 / 30); sprintf(data[2], "%lf", soma3 / 30);
	result_table_id(data);

	soma1 = soma2 = soma3 = soma4 = soma5 = soma6 = 0;
	for (i = 0; i < 30; ++i)
	{

		float key1 = ((rand() % 9999) + 1) / 1000.0f;
		float key2 = ((rand() % 9999) + 1) / 1000.0f;

		if (key1 == key2)
			while (key1 == key2)
				key2 = ((rand() % 9999) + 1) / 1000.0f;

		if (key1 > key2)
			SWAP(key1, key2);

		t_ini = clock();
		linear__range__price__query(bin, key1, key2);
		t_fim = clock();
		soma1 += (double)((t_fim - t_ini) * 1000.0) / CLOCKS_PER_SEC;

		t_ini = clock();
		BST__price__range__query(price_index_tree, key1, key2, bin);
		t_fim = clock();
		soma2 += (double)((t_fim - t_ini) * 1000.0) / CLOCKS_PER_SEC;

		/* Rewind faz o o cabeçote do hd apontar de volta para o inicio do arquivo, 
		   isso é necessário paras as buscas sequenciais não retornarem tempos absurdos (baixos). */
		rewind(bin);
		t_ini = clock();
		linear__conditional__price__query(bin, key2, '<');
		t_fim = clock();
		soma3 += (double)((t_fim - t_ini) * 1000.0) / CLOCKS_PER_SEC;

		t_ini = clock();
		BST__price__range__gt(price_index_tree, key2, bin);
		t_fim = clock();
		soma4 += (double)((t_fim - t_ini) * 1000.0) / CLOCKS_PER_SEC;

		rewind(bin);
		t_ini = clock();
		linear__conditional__price__query(bin, key1, '>');
		t_fim = clock();
		soma5 += (double)((t_fim - t_ini) * 1000.0) / CLOCKS_PER_SEC;

		t_ini = clock();
		BST__price__range__lt(price_index_tree, key1, bin);
		t_fim = clock();
		soma6 += (double)((t_fim - t_ini) * 1000.0) / CLOCKS_PER_SEC;
		rewind(bin);

	}
	
	sprintf(data[0], "%lf", soma1 / 30); sprintf(data[1], "%lf", soma2 / 30); sprintf(data[2], "%lf", soma3 / 30);
	sprintf(data[3], "%lf", soma4 / 30); sprintf(data[4], "%lf", soma5 / 30); sprintf(data[5], "%lf", soma6 / 30);
	result_table_price(data);

}

void result_table_id(char (*data)[60])
{

	ft_table_t *table = ft_create_table();
	ft_set_border_style(table, FT_SOLID_STYLE);

	ft_write_ln(table, "Tempo Medio de Busca em Arquivo por Atributo Chave");
	ft_write_ln(table, "Indexado por ABP", "Indexado por Hashing", "Sequencial");
	ft_write_ln(table, strcat(data[0], " ms"), strcat(data[1], " ms"), strcat(data[2], " ms"));

	ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);
	ft_set_cell_prop(table, 0, 0, FT_CPROP_CONT_FG_COLOR, FT_COLOR_GREEN);
	ft_set_cell_prop(table, 2, FT_ANY_COLUMN, FT_CPROP_CONT_TEXT_STYLE, FT_TSTYLE_ITALIC);
	ft_set_cell_prop(table, FT_ANY_ROW, FT_ANY_COLUMN, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_CENTER);
	ft_set_cell_prop(table, 1, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);
	ft_set_cell_span(table, 0, 0, 3);

	printf("%s\n", ft_to_string(table));
	ft_destroy_table(table);

}

void result_table_price(char (*data)[60])
{

	ft_table_t *table = ft_create_table();
	ft_set_border_style(table, FT_SOLID_STYLE);

	ft_write_ln(table, "Tempo Medio de Busca em Arquivo por Atributo Nao Chave");
	ft_write_ln(table, "Indexado por ABP", "", "", "Sequencial");
	ft_write_ln(table, "'>=' '<='", ">", "<", "'>=' '<='", ">", "<");
	ft_write_ln(table, strcat(data[0], " ms"), strcat(data[2], " ms"), strcat(data[4], " ms"), strcat(data[1], " ms"), strcat(data[3], " ms"), strcat(data[5], " ms"));

	ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);
	ft_set_cell_prop(table, 0, 0, FT_CPROP_CONT_FG_COLOR, FT_COLOR_GREEN);
	ft_set_cell_prop(table, 2, FT_ANY_COLUMN, FT_CPROP_CONT_TEXT_STYLE, FT_TSTYLE_ITALIC);
	ft_set_cell_prop(table, FT_ANY_ROW, FT_ANY_COLUMN, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_CENTER);
	ft_set_cell_prop(table, 1, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);
	ft_set_cell_prop(table, 2, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);
	ft_set_cell_span(table, 0, 0, 6);
	ft_set_cell_span(table, 1, 0, 3);
	ft_set_cell_span(table, 1, 3, 3);

	printf("%s\n", ft_to_string(table));
	ft_destroy_table(table);

}