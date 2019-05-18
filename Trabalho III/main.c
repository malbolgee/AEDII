#include <stdio.h>
#include <string.h>
#include "hash.h"

typedef struct produto{

	int id;
	float preco;
	char descricao[50];
	char nome[50];
	int disponibilidade;

} produto;

void main ()
{

	int i;
	FILE *fp = fopen("produtos", 'wb');

	printf("%zu\n", sizeof(produto));


}