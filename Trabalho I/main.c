#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "vetor.h"
#include "list.h"
#include "test.h"

int main ()
{

	int i, j;
	float tempo;
	time_t t_ini, t_fim;
	float soma_busca_list;
	float soma_busca_linear;
	float soma_busca_binaria;
	float soma_bubble, soma_quick, soma_insertion;
		
	//Busca sequêncial e binária pelos mesmos valores x30;

	int *vetor;
	vetor = array(__MAXSIZE);

	srand(time(NULL));
	for (i = 0, j = 0; i < __MAXSIZE; ++i, j += (rand() % 499) + 1)
		vetor[i] = j;

	soma_busca_linear = 0;
	soma_busca_binaria = 0;
	for (i = 0; i < 30; ++i)
	{
		
		int key = (rand() % (__MAXSIZE - 1) << 2) + 1;

		printf("Teste #%d:\n", i + 1);
		t_ini = time(NULL);
		buscaBin(vetor, __MAXSIZE, key);
		t_fim = time(NULL);
		tempo = difftime(t_fim, t_ini);
		soma_busca_binaria += tempo;
		result_kl(tempo, __BINARIA);

		// ----------------------------------------------------------------------------

		t_ini = time(NULL);
		array__search(vetor, __MAXSIZE, key);
		t_fim = time(NULL);
		tempo = difftime(t_fim, t_ini);
		soma_busca_linear += tempo;
		result_kl(tempo, __LINEAR);
		printf("\n");

	}

	result_kl(soma_busca_binaria, __MEDIA__BINARIA);
	result_kl(soma_busca_linear, __MEDIA__LINEAR);
	printf("\n");

	// Buscas Sequenciais em vetor e em lista encadeada;

	l_list lista;
	list(&lista);

	for (i = 0; i < __MAXSIZE; ++i)
		push(&lista, vetor[i]);
	
	soma_busca_list = 0;
	soma_busca_linear = 0;
	for (i = 0; i < 30; ++i)
	{

		int key = (rand() % (__MAXSIZE - 1) << 2) + 1;
		printf("Teste #%d:\n", i + 1);

		// Busca sequencial em vetor;

		t_ini = time(NULL);
		array__search(vetor, __MAXSIZE, key);
		t_fim = time(NULL);
		tempo = difftime(t_fim, t_ini);
		soma_busca_linear += tempo;
		result_kl(tempo, __LINEAR__VETOR);

		// Busca sequencial em lista;

		t_ini = time(NULL);
		list__search(&lista, key);
		t_fim = time(NULL);
		tempo = difftime(t_fim, t_ini);
		soma_busca_list += tempo;
		result_kl(tempo, __LINEAR__LIST);
		printf("\n");

	}

	result_kl(soma_busca_linear, __MEDIA__VETOR);
	result_kl(soma_busca_list, __MEDIA__LIST);
	printf("\n");

	free__array(vetor);
	erase__list(&lista);

	int *vetor1 = array(__MAXSIZEORD);
	int *vetor2 = array(__MAXSIZEORD);
	int *vetor3 = array(__MAXSIZEORD);

	soma_bubble = soma_quick = soma_insertion = 0;
	for (i = 0; i < 30; ++i)
	{

		printf("Teste #%d:\n", i + 1);
		for (j = 0; j < __MAXSIZEORD; ++j)
			vetor1[j] = (rand() % (__MAXSIZEORD - 1) << 2) + 1;

		for (j = 0; j < __MAXSIZEORD; ++j)
			vetor2[j] = vetor1[j];

		for (j = 0; j < __MAXSIZEORD; ++j)
			vetor3[j] = vetor2[j];

		t_ini = time(NULL);
		bubbleSort(vetor1, __MAXSIZEORD);
		t_fim = time(NULL);
		tempo = difftime(t_fim, t_ini);
		soma_bubble += tempo;
		printf("Bubble demorou %f segundos\n", tempo);

		// ---------------------------------------------------------------------------

		t_ini = time(NULL);
		insertionSort(vetor2, __MAXSIZEORD);
		t_fim = time(NULL);
		tempo = difftime(t_fim, t_ini);
		soma_insertion += tempo;
		printf("insertion demorou %f segundos\n", tempo);

		//  --------------------------------------------------------------------------

		t_ini = time(NULL);
		quickSort(vetor3, __MAXSIZEORD);
		t_fim = time(NULL);
		tempo = difftime(t_fim, t_ini);
		soma_quick += tempo;
		printf("quick demorou %f segundos\n", tempo);
		printf("\n");
		
	}

	result_kl(soma_bubble, __MEDIA__BUBBLE);
	result_kl(soma_insertion, __MEDIA__INSERTION);
	result_kl(soma_quick, __MEDIA__QUICK);

	return 0;

}