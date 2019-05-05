#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "bin_tree.h"
#include "avl_tree.h"
#include "array.h"

#define GRN  "\x1B[32m"
#define NOC "\033[0m"
#define RED  "\x1B[31m"

char *string[10] = { "Primeira", "Segunda", "Terceira", "Quarta", "Quinta", "Sexta", "Sétima", "Oitava", "Nona", "Décima" };

#define __TEST_COUNT 30
#define LOG printf("\n\n")

int compare(const void *a, const void *b);
double median(const double *__array, const unsigned __size);
double average(const double *__array, const unsigned __size);


int main ()
{

	unsigned i;
	srand(time(NULL));
	clock_t t_ini, t_fim;
	double soma1[30], soma2[30];

	int *vet = array(50);
	avl_tree *arvore_avl;
	bin_tree *arvore_binaria;

	// Preenchimento do vetor e da árvore;

	array__no__repetition__fill(vet, 50);
	
	make__binary__tree(&arvore_binaria);
	array__to__binary__tree(&arvore_binaria, vet, 50);

	// Percursos em árvore;

	printf("%sPERCURSOS EM ÁRVORE BINÁRIA%s\n", RED, NOC);

	printf("%sPercurso Pré-fixado%s:\n", GRN, NOC);
	binary__tree__prefix(arvore_binaria);
	printf("\n\n%sPercurso Infixado%s:\n", GRN, NOC);
	binary__tree__infix(arvore_binaria);
	printf("\n\n%sPercuso Pós-fixado%s:\n", GRN, NOC);
	binary__tree__posfix(arvore_binaria); printf("\n\n");
	

	// Liberação do vetor e da árvore;
	free__array(vet);
	arvore_binaria = binary__tree__erase(arvore_binaria);

	// Simulação de pacotes de rede;

	printf("%sSIMULAÇÃO DE RECEBIMENTO DE PACOTES DE REDES%s\n", RED, NOC);

	// Criação do vetor e da árvore binária;
	vet = array(100);
	make__binary__tree(&arvore_binaria);

	// Preenchimento da árvore e do vetor;
	partially__ordered__array__fill(vet, 100);
	array__to__binary__tree(&arvore_binaria, vet, 100);

	// Demonstração dos 'pacotes';

	printf("%sPacotes Recebidos%s:\n", GRN, NOC);
	print__array__to__idx(vet, 100);
	printf("\n\n");

	printf("%sArquivo Montado:%s\n", GRN, NOC);
	binary__tree__infix(arvore_binaria);
	printf("\n\n");

	// Liberação do vetor e da árvore;

	free__array(vet);
	arvore_binaria =  binary__tree__erase(arvore_binaria);

	// COMPARAÇÀO DE BUSCAS NO VETOR E NA ÁRVORE BINÁRIA;

	// Criação do vetor e da árvore binária;

	vet = array(__MAXSIZE);
	make__binary__tree(&arvore_binaria);

	// Preenchimento do vetor e da árvore;

	array__no__repetition__fill(vet, __MAXSIZE);
	array__to__binary__tree(&arvore_binaria, vet, __MAXSIZE);

	// Vetor precisa estar ordenado para buscas binárias;
	quickSort(vet, __MAXSIZE);

	printf("%sBUSCAS NO VETOR E NA ÁRVORE BINÁRIA%s\n", RED, NOC);

	memset(soma1, 0, sizeof(soma1));
	memset(soma2, 0, sizeof(soma2));
	for (i = 0; i < __TEST_COUNT; ++i)
	{

		int key = (rand() % __MAXSIZE) + 1;

		t_ini = clock();
		binary__search(vet, __MAXSIZE, key);
		t_fim = clock();
		soma1[i] += (double)((t_fim - t_ini) * 1000.0) / CLOCKS_PER_SEC;

		t_ini = clock();
		binary__tree__search(arvore_binaria, key);
		t_fim = clock();
		soma2[i] += (double)((t_fim - t_ini) * 1000.0) / CLOCKS_PER_SEC;

	}

	// Liberação do vetor e da árvore binária;
	free__array(vet);
	arvore_binaria = binary__tree__erase(arvore_binaria);

	// Resultados das buscas;
	puts("===============================================================");
	printf("Média Busca em Vetor\t\tMédia Busca na ABP\n");
	printf("      %lf ms\t\t     %lf ms\n", average(soma1, __TEST_COUNT), average(soma2, __TEST_COUNT));
	puts("===============================================================");
	printf("Mediana Busca no Vetor\t\t  Mediana na ABP\n");
	printf("      %lf ms\t\t     %lf ms\n", median(soma1, __TEST_COUNT), median(soma2, __TEST_COUNT));
	puts("===============================================================\n");

	printf("%sTESTES DE INSERÇÃO%s\n", RED, NOC);
	
	// Criação do vetor;
	vet = array(__MAXSIZE);

	memset(soma1, 0, sizeof(soma1));
	memset(soma2, 0, sizeof(soma2));

	for (i = 0; i < 10; ++i)
	{
		
		// Preenchimento do vetor;
		array__no__repetition__fill(vet, __MAXSIZE);

		// Cada iteração, novas árvores precisam ser criadas;
		make__avl__tree(&arvore_avl);
		make__binary__tree(&arvore_binaria);

		t_ini = clock();
		for (int j = 0; j < __MAXSIZE; ++j)
			arvore_avl = avl__tree__push(arvore_avl, vet[j]);
		t_fim = clock();
		soma2[i] += (double)((t_fim - t_ini) * 1000.0) / CLOCKS_PER_SEC;

		t_ini = clock();
		for (int j = 0; j < __MAXSIZE; ++j)
			arvore_binaria = binary__tree__push(arvore_binaria, vet[j]);
		t_fim = clock();
		soma1[i] += (double)((t_fim - t_ini) * 1000.0) / CLOCKS_PER_SEC;

		printf("Altura da AVL na %s iteração: %d\n", string[i], avl__tree__height(arvore_avl));
		printf("Altura da ABP na %s iteração: %d\n\n", string[i], binary__tree__height(arvore_binaria));

		// Liberação das árvores após cada iteração;
		arvore_avl = avl__tree__erase(arvore_avl);
		arvore_binaria = binary__tree__erase(arvore_binaria);
	
	}	

	puts("===============================================================");
	printf("Média Inserção Binária\t\t   Média Inserção AVL\n");
	printf("      %lf ms\t\t      %lf ms\n", average(soma1, 10), average(soma2, 10));
	puts("===============================================================");
	printf(" Mediana Inserção ABP\t\t   Mediana Inserção AVL\n");
	printf("      %lf ms\t\t      %lf ms\n", median(soma1,10), median(soma2, 10));
	puts("===============================================================\n");

	// Liberação do vetor;
	free__array(vet);

	// TESTES DE BUSCAS NA ÁRVORE AVL E NA ÁRVORE BINÁRIA;

	// Criação do vetor, da árvore avl e da árvore binária;
	vet = array(__MAXSIZE);
	make__avl__tree(&arvore_avl);
	make__binary__tree(&arvore_binaria);

	// Preenchimento do vetor e das árvores;

	array__no__repetition__fill(vet, __MAXSIZE);
	array__to__binary__tree(&arvore_binaria, vet, __MAXSIZE);
	arvore_avl = array__to__avl__tree(arvore_avl, vet, __MAXSIZE);

	printf("%sBUSCAS NA ÁRVORE BINÁRIA E NA ÁRVORE AVL%s\n", RED, NOC);

	memset(soma1, 0, sizeof(soma1));
	memset(soma2, 0, sizeof(soma2));
	for (i = 0; i < __TEST_COUNT; ++i)
	{

		// Geração da chave de busca;
		int key = (rand() % __MAXSIZE) + 1;

		t_ini = clock();
		binary__tree__search(arvore_binaria, key);
		t_fim = clock();
		soma1[i] += (double)((t_fim - t_ini) * 1000.0) / CLOCKS_PER_SEC;

		t_ini = clock();
		avl__tree__search(arvore_avl, key);
		t_fim = clock();
		soma2[i] += (double)((t_fim - t_ini) * 1000.0) / CLOCKS_PER_SEC;

	}

	arvore_avl = avl__tree__erase(arvore_avl);
	arvore_binaria = binary__tree__erase(arvore_binaria);

	puts("===============================================================");
	printf("Média Busca ABP\t\t\t\tMédia Busca AVL\n");
	printf("    %lf ms\t\t\t\t   %lf ms\n", average(soma1, __TEST_COUNT), average(soma2, __TEST_COUNT));
	puts("===============================================================");
	printf("Mediana Busca APB\t\t\tMediana Busca AVL\n");
	printf("    %lf ms\t\t\t\t   %lf ms\n", median(soma1, __TEST_COUNT), median(soma2, __TEST_COUNT));
	puts("===============================================================\n");

	scanf("%d", &i);

}

int compare(const void *a, const void *b)
{

	if (*(double *)a == *(double *)b)
		return 0;
	else if (*(double *)a > *(double *)b)
		return 1;
	else
		return -1;

}

double average(const double *__array, const unsigned __size)
{

	unsigned i;
	double sum = 0;

	for (i = 0; i < __size; ++i)
		sum += __array[i];

	return sum / __size;

}

double median(const double *__array, const unsigned __size)
{

	double __tmp[__size];
	memcpy(__tmp, __array, sizeof(double) * __size);
	qsort(__tmp, __size, sizeof(double), compare);
	
	if (__size & 1)
		return __tmp[__size / 2];
	else
		return (__tmp[(__size / 2) - 1] + __tmp[(__size / 2)]) / 2;

}