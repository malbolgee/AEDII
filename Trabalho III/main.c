#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "hash.h"

typedef struct __product__type{

	unsigned id;
	char nome[51];
	char descricao[101];
	float preco;
	unsigned disponibilidade;
	unsigned vencimento;

} product_t;

product_t product_array[10000];

void get_product_info();

void main ()
{

	int i;
	char id[30];
	srand(time(NULL));
	product_t produto;

	hash_t *hash_produto;
	hash_produto = make__hash__table(10177);
	FILE *bin = fopen("produtos", "wb");
	get_product_info();

	for (i = 0; i < 10000; ++i)
	{

		fwrite(&product_array[i], sizeof(product_t), 1, bin);
		sprintf(id, "%d", product_array[i].id);
		hash__push(hash_produto, i, id);

	}

	fclose(bin);
	bin = fopen("produtos", "rb");

	scanf("%s", id);

	int idx = hash__search(hash_produto, id);

	if (idx < 0)
		printf("Registro não encontrado\n");
	else
	{

		fseek(bin, idx * sizeof(product_t), SEEK_SET);
		fread(&produto, sizeof(product_t), 1, bin);	
		printf("Id: %d\nNome: %s\nDescrição: %s\nPreço: %.2f\nDisponibilidade: %d\nVencimento: %d\n\n",
		produto.id, produto.nome, produto.descricao, produto.preco, produto.disponibilidade, produto.vencimento);

	}
	
	scanf("%s", id);

}

void get_product_info()
{

	unsigned i = 0;
	FILE *json = fopen("out", "r");

	while (fscanf(json, "%d%*[: ]%[ A-Za-z0-9-.&'+\"%%()\\/$é!#?ñ,]%*[: ]%[ A-Za-z0-9]%*[: ]%f%*[: ]%d%*[: ]%d\n", 
			&product_array[i].id, product_array[i].nome, product_array[i].descricao, &product_array[i].preco, 
			&product_array[i].disponibilidade, &product_array[i].vencimento) != EOF)
		i++;

	fclose(json);
	
}