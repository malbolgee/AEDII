#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

// Cria o arquivo 'JSON-like' para o programa principal;

#define MAX_UN_SIZE 100000U
#define MAX_ID 2000000000U
#define MAX_ARRAY_SIZE 10000U

bool seen[MAX_ID + 1];
bool un[MAX_UN_SIZE];

void partially__ordered__array__fill(int *__array, const unsigned __size);

int main (int argc, char **argv)
{

	FILE *descri = fopen("description", "r");
	FILE *nome = fopen("names", "r");

	unsigned i;
	srand(time(NULL));
	char nomes[100];
	char descricao[100];
	int unidades[10000];
	double price;

	partially__ordered__array__fill(unidades, MAX_ARRAY_SIZE);

	for (i = 0; i < 10000; ++i)
	{

		unsigned id = (rand()) % MAX_ID + 1;
		if (seen[id])
		{

			while (seen[id])
				id = (rand()) % MAX_ID + 1;

			seen[id] = true;

		}
		else
			seen[id] = true;


		printf("%d:", id); // id;
		fscanf(nome, " %[^\n]", nomes);
		printf(" %s:", nomes); // nome;
		fscanf(descri, " %[^\n]", descricao);
		printf(" %s:", descricao); // descrição;
		printf(" %.2f:", log10(id)); // preço;
		printf(" %d:", unidades[i]); // unidade;
		printf(" %d\n", (rand() % 4) + 2019); // vencimento;
		
	}

	fclose(descri);
	fclose(nome);

	return 0;	

}

/* Cria um vetor com unidades de produtos que aceita uma taxa de 5% 
   de repetições. */
void partially__ordered__array__fill(int *__array, const unsigned __size)
{

	unsigned i = 0;
	unsigned char rep = 0.05 * __size;
	unsigned limit = __size;

	while (limit > 0)
	{

		unsigned idx = (rand() % MAX_UN_SIZE);
		
		if (!un[idx])
			__array[i++] = idx, un[idx] = true, --limit;
		else if (un[idx] && rep)
		{	

			unsigned aux = i;

			while (__array[aux++]);

			__array[aux] = idx, --rep;

		}

	}

}