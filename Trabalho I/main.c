#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vetor.h"
#include "list.h"

#define GRN  "\x1B[32m"
#define NOC "\033[0m"

void progress__bar(const int __count, const int __max);

int main ()
{

	int i;
	int *vetor;
	double soma1, soma2, soma3;
	clock_t t_ini, t_fim;
	
	soma1 = soma2 = 0;
	vetor = array(__MAXSIZE);
	array__fill__ordered(vetor, __MAXSIZE);

	srand(time(NULL));
	for (i = 0; i < 30; ++i)
	{
		
		int key = (rand() % (__MAXSIZE) << 2) + 1;

		t_ini = clock();
		binary__search(vetor, __MAXSIZE, key);
		t_fim = clock();
		soma1 += (double)(t_fim - t_ini) / CLOCKS_PER_SEC;

		t_ini = clock();
		array__linear__search(vetor, __MAXSIZE, key);
		t_fim = clock();
		soma2 += (double)(t_fim - t_ini) / CLOCKS_PER_SEC;
	
	}

	printf("===============================================================\n");
	printf("Média Busca Binária\t\tMédia Busca Sequencial\n");
	printf("      %lf\t\t\t       %lf\n", soma1 / 30, soma2 / 30);
	printf("===============================================================\n\n");

	l_list lista;
	list(&lista);
	array__to__list(&lista, vetor, __MAXSIZE);

	soma1 = soma2 = 0;
	for (i = 0; i < 30; ++i)
	{

		int key = (rand() % (__MAXSIZE) << 2) + 1;

		t_ini = clock();
		array__linear__search(vetor, __MAXSIZE, key);
		t_fim = clock();
		soma1 += (double)(t_fim - t_ini) / CLOCKS_PER_SEC;

		t_ini = clock();
		list__search(&lista, key);
		t_fim = clock();
		soma2 += (double)(t_fim - t_ini) / CLOCKS_PER_SEC;

	}

	puts("===============================================================\n");
	printf("Média B.S. no Vetor\t\tMédia B.S na Lista\n");
	printf("      %lf\t\t\t      %lf\n", soma1 / 30, soma2 / 30);
	puts("===============================================================\n");

	free__array(vetor);
	erase__list(&lista);

	int *vetor1 = array(__MAXSIZEORD);
	int *vetor2 = array(__MAXSIZEORD);
	int *vetor3 = array(__MAXSIZEORD);

	progress__bar(0, 30);
	soma1 = soma2 = soma3 = 0;
	for (i = 1; i <= 30; ++i)
	{
		
		array__fill__random(__MAXSIZEORD, 3, vetor1, vetor2, vetor3);

		t_ini = clock();
		bubbleSort(vetor1, __MAXSIZEORD);
		t_fim = clock();
		soma1 += (double)(t_fim - t_ini) / CLOCKS_PER_SEC;

		t_ini = clock();
		insertionSort(vetor2, __MAXSIZEORD);
		t_fim = clock();
		soma2 += (double)(t_fim - t_ini) / CLOCKS_PER_SEC;

		t_ini = clock();
		quickSort(vetor3, __MAXSIZEORD);
		t_fim = clock();
		soma3 += (double)(t_fim - t_ini) / CLOCKS_PER_SEC;

		progress__bar(i, 30);
		
	}

	printf("\r%c[2K%s", 27, NOC);
	puts("===============================================================");
	printf("Média BubbleSort\tMédia InsertionSort\tMédia QuickSort\n");
	printf("    %lf\t\t     %lf\t\t    %lf\n", soma1 / 30, soma2 / 30, soma3 / 30);
	puts("===============================================================");
	printf("O QuickSort foi x%d mais rápido do que o Bubble e x%d mais rápido do que o Insertion\n", (int)((soma1 / 30) / (soma3 / 30)), (int)((soma2 / 30) / (soma3 / 30)));

	return 0;

}

void progress__bar(const int __count, const int __max)
{

	int i;
	char prefix[] = "[";
	int prefix_length = sizeof(prefix) - 1;
	char *buffer = calloc(__max + 1, 1);
	
	strcpy(buffer, prefix);
	for (i = 0; i < __max; ++i)
		buffer[prefix_length + i] = i < __count ? '#' : ' ';
 
	printf("\r%s%c[2KProgresso das Ordenações: %s%.2f%%]", GRN, 27, buffer, 100.0f * __count / __max);
	fflush(stdout);
	free(buffer);
	
}