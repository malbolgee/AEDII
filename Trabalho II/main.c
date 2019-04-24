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

int main ()
{

	unsigned i;
	srand(time(NULL));
	double soma1, soma2, soma3;
	clock_t t_ini, t_fim;

	int *vet = array(50);
	avl_tree *arvore_avl;
	bin_tree *arvore_binaria;
	arvore_binaria = make__binary__tree();
	unbiased__random__array__fill(vet, 50);

	for (i = 0; i < 50; ++i)
		arvore_binaria = binary__tree__push(arvore_binaria, vet[i]);

	printf("%sPercurso Pré-fixado%s:\n", GRN, NOC);
	binary__tree__prefix(arvore_binaria);
	printf("\n\n%sPercurso Infixado%s:\n", GRN, NOC);
	binary__tree__infix(arvore_binaria);
	printf("\n\n%sPercuso Pós-fixado%s:\n", GRN, NOC);
	binary__tree__posfix(arvore_binaria);
	printf("\n\n");

	binary__tree__erase(arvore_binaria);
	free__array(vet);

	// Simulação de pacotes de rede

	printf("%sSIMULAÇÃO DE RECEBIMENTO DE PACOTES DE REDES%s\n", RED, NOC);

	arvore_binaria = make__binary__tree();
	vet = array(100);

	partially__ordered__array__fill(vet, 100);
	arvore_binaria = array__to__binary__tree(arvore_binaria, vet, 100);

	printf("%sPacotes Recebidos%s:\n", GRN, NOC);
	print__array__to__idx(vet, 100);
	printf("\n\n");

	printf("%sArquivo Montado:%s\n", GRN, NOC);
	binary__tree__infix(arvore_binaria);
	printf("\n\n");

	binary__tree__erase(arvore_binaria);
	free__array(vet);

	arvore_binaria = make__binary__tree();
	vet = array(__MAXSIZE);

	array__no__repetition__fill(vet, __MAXSIZE);
	arvore_binaria = array__to__binary__tree(arvore_binaria, vet, __MAXSIZE);

	quickSort(vet, __MAXSIZE);

	// scanf("%d", &i);

	printf("%sBUSCAS NO VETOR E NA ÁRVORE BINÁRIA%s\n", RED, NOC);

	soma1 = soma2 = 0;
	for (i = 0; i < __TEST_COUNT; ++i)
	{


		int key = (rand() % (__MAXSIZE) << 2) + 1;

		t_ini = clock();
		binary__search(vet, __MAXSIZE, key);
		t_fim = clock();
		soma1 += (double)(t_fim - t_ini) / CLOCKS_PER_SEC;

		t_ini = clock();
		binary__tree__search(arvore_binaria, key);
		t_fim = clock();
		soma2 += (double)(t_fim - t_ini) / CLOCKS_PER_SEC;


	}

	binary__tree__erase(arvore_binaria);

	puts("===============================================================");
	printf("Média Busca Binária\t\tMédia Na Árvore Binaria\n");
	printf("      %lf\t\t\t       %lf\n", soma1 / 30, soma2 / 30);
	puts("===============================================================\n");


	printf("%sTESTES DE INSERÇÃO%s\n", RED, NOC);

	vet = array(__MAXSIZE);
	soma1 = soma2 = 0;
	for (i = 0; i < 10; ++i)
	{
		
		array__no__repetition__fill(vet, __MAXSIZE);

		arvore_avl = make__avl__tree();
		arvore_binaria = make__binary__tree();

		t_ini = clock();
		for (int j = 0; j < __MAXSIZE; ++j)
			arvore_avl = avl__tree__push(arvore_avl, vet[j]);
		t_fim = clock();
		soma1 += (double)(t_fim - t_ini) / CLOCKS_PER_SEC;

		t_ini = clock();
		for (int j = 0; j < __MAXSIZE; ++j)
			arvore_binaria = binary__tree__push(arvore_binaria, vet[j]);
		t_fim = clock();
		soma2 += (double)(t_fim - t_ini) / CLOCKS_PER_SEC;


		printf("Altura da AVL na %s iteração: %d\n", string[i], avl__tree__height(arvore_avl));
		printf("Altura da Árvore Binária na %s iteração: %d\n\n", string[i], binary__tree__height(arvore_binaria));

		arvore_avl = avl__tree__erase(arvore_avl);
		arvore_binaria = binary__tree__erase(arvore_binaria);
	

	}

	printf("===============================================================\n");
	printf("Média Inserção Binária\t\t   Média Inserção AVL\n");
	printf("      %lf\t\t\t       %lf\n", soma2 / 30, soma1 / 30);
	printf("===============================================================\n\n");

}
