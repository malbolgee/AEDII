#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include "vetor.h"
#include "list.h"
#include "test.h"

int main ()
{

	SEED;
	int i, j;
	int *vetor;
	r_results results = { 0.0 };
	clock_t t_ini, t_fim;
			
	vetor = array(__MAXSIZE);
	array__fill__ordered(vetor, __MAXSIZE);

	for (i = 0; i < __NUMBER__TEST; ++i)
	{
		
		int key = __RAND__KEY;

		t_ini = clock();
		binary__search(vetor, __MAXSIZE, key);
		t_fim = clock();
		results.r_searchs[i][0] = (double)(t_fim - t_ini) / CLOCKS_PER_SEC;

		t_ini = clock();
		array__linear__search(vetor, __MAXSIZE, key);
		t_fim = clock();
		results.r_searchs[i][1] = (double)(t_fim - t_ini) / CLOCKS_PER_SEC;
	
	}

	result(&results, __SEARCH__ARRAY);

	l_list lista;
	list(&lista);
	array__to__list(&lista, vetor, __MAXSIZE);

	for (i = 0; i < __NUMBER__TEST; ++i)
	{

		int key = __RAND__KEY;

		t_ini = clock();
		array__linear__search(vetor, __MAXSIZE, key);
		t_fim = clock();
		results.r_searchs[i][0] = (double)(t_fim - t_ini) / CLOCKS_PER_SEC;

		t_ini = clock();
		list__search(&lista, key);
		t_fim = clock();
		results.r_searchs[i][1] = (double)(t_fim - t_ini) / CLOCKS_PER_SEC;

	}

	result(&results, __SEARCH__ARRAY__AND__LIST);
	free__array(vetor);
	erase__list(&lista);

	int *vetor1 = array(__MAXSIZEORD);
	int *vetor2 = array(__MAXSIZEORD);
	int *vetor3 = array(__MAXSIZEORD);

	progress__bar(1, __NUMBER__TEST);
	for (i = 1; i <= __NUMBER__TEST; ++i)
	{
		
		array__fill__random(4, __MAXSIZEORD, vetor1, vetor2, vetor3);

		t_ini = clock();
		bubbleSort(vetor1, __MAXSIZEORD);
		t_fim = clock();
		results.r_sort[i][0] = (double)(t_fim - t_ini) / CLOCKS_PER_SEC;

		t_ini = clock();
		insertionSort(vetor2, __MAXSIZEORD);
		t_fim = clock();
		results.r_sort[i][1] = (double)(t_fim - t_ini) / CLOCKS_PER_SEC;

		t_ini = clock();
		quickSort(vetor3, __MAXSIZEORD);
		t_fim = clock();
		results.r_sort[i][2] = (double)(t_fim - t_ini) / CLOCKS_PER_SEC;

		progress__bar(i, __NUMBER__TEST);
		
	}

	printf("%s\n\n", KWHT);
	result(&results, __SORT);

	return 0;

}

