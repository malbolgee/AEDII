#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "bin_tree.h"
#include "hash.h"
#include "product.h"
#include "fort.h"

#define MAXID 15000

void result_table_id(char (*data)[3][60]);
void table_fill(char (*data)[3][60], int test);
enum { ID, PC };

void main ()
{

	char id[30];
	unsigned i = 0;
	srand(time(NULL));
	BST_t *arvore;
	product_t produto;
	hash_t *hash_produto;
	clock_t t_ini, t_fim;
	double soma1, soma2, soma3;
	char ssoma1[30], ssoma2[30], ssoma3[30];
	char data[3][3][60] = { 0 };

	// Criação da Árvore e da tabela Hash;
	make__binary__tree(&arvore);
	hash_produto = make__hash__table(MAXHASHSIZE);

	// Abertura dos arquivos para leitura e para escrita;
	FILE *bin = fopen("produtos", "wb");
	FILE *json = fopen("out", "r");

	/* Escrevendo os registros no arquivo binário e suas 
	   chaves na tebela hash e na arvore binária de busca */
	while (get_product_info(&produto, json) != EOF)
	{

		fwrite(&produto, sizeof(product_t), 1, bin);
		sprintf(id, "%d", produto.id);
		hash__push(hash_produto, id, i);
		arvore = BST__id__push(arvore, produto.id, i);
		++i;

	}

	// Fechando os arquivos;
	fclose(bin);
	fclose(json);

	int aux = hash__colisions(hash_produto, MAXHASHSIZE);
	printf("Quantidade de colisões a tabela hash: %d\n", aux);
	printf("Porcentagem de colisões na tebala hash: %.2f%%\n", (aux * 100.0f) / MAXHASHSIZE);

	// Abertura do arquivo 'produtos' no modo leitura;
	bin = fopen("produtos", "rb");

	// Tempos das buscas com árvore, com hash e sequencial
	soma1 = soma2 = soma3 = 0;
	for (i = 0; i < 30; ++i)
	{

		unsigned key = (rand() % MAXID);
		sprintf(id, "%d", key);

		t_ini = clock();
		BST__id__search(arvore, key, bin);
		t_fim = clock();
		soma1 += (double)((t_fim - t_ini) * 1000.0) / CLOCKS_PER_SEC;

		t_ini = clock();
		hash__search(hash_produto, id, bin);
		t_fim = clock();
		soma2 += (double)((t_fim - t_ini) * 1000.0) / CLOCKS_PER_SEC;

		t_ini = clock();
		linear__registry__search(key, bin);
		t_fim = clock();
		soma3 += (double)((t_fim - t_ini) * 1000.0) / CLOCKS_PER_SEC;

	}

	sprintf(data[2][0], "%lf", soma1 / 30); sprintf(data[2][1], "%lf", soma2 / 30); sprintf(data[2][2], "%lf", soma3 / 30);
	table_fill(data, ID);
	result_table_id(data);
	
}

void result_table_id(char (*data)[3][60])
{

	ft_table_t *table = ft_create_table();
	ft_set_border_style(table, FT_SOLID_STYLE);

	ft_write_ln(table, data[0][0]);
	ft_write_ln(table, data[1][0], data[1][1], data[1][2]);
	ft_write_ln(table, data[2][0], data[2][1], data[2][2]);

	ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);
	ft_set_cell_prop(table, 0, 0, FT_CPROP_CONT_FG_COLOR, FT_COLOR_GREEN);
	ft_set_cell_prop(table, 2, FT_ANY_COLUMN, FT_CPROP_CONT_TEXT_STYLE, FT_TSTYLE_ITALIC);
	ft_set_cell_prop(table, FT_ANY_ROW, FT_ANY_COLUMN, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_CENTER);
	ft_set_cell_prop(table, 1, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);
	ft_set_cell_span(table, 0, 0, 3);

	printf("%s\n", ft_to_string(table));
	ft_destroy_table(table);

}

void table_fill(char (*data)[3][60], int test)
{

	if (test == ID)
	{

		strcpy(data[0][0], "Tempo Medio de Busca em Arquivo por Atributo Chave");
		strcpy(data[1][0], "Indexado por ABP");
		strcpy(data[1][1], "Indexado por Hashing");
		strcpy(data[1][2], "Sequencial");
		strcat(data[2][0], " ms");
		strcat(data[2][1], " ms");
		strcat(data[2][2], " ms");

	}

}