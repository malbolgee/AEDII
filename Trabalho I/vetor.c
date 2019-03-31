#include "vetor.h"
#include <stdlib.h>
#include <stdio.h>

int* array(int __tam)
{

	return (int *) malloc(sizeof(int) * __tam);

}

void free__array(int *__vetor)
{

	free(__vetor);

}

bool array__search(const int *__vetor, int __size, int __key)
{

	int i;
	for (i = 0; i < __size; ++i)
		if (__vetor[i] == __key)
			return true;

	return false;

}

bool buscaBin(const int *__vetor, int __tam, int __key)
{

	int hi, low, mid;

	low = 0;
	hi = __tam - 1;

	while (low < hi)
	{
		mid = (low + hi) / 2;
		if (__vetor[mid] < __key)
			hi = mid - 1;
		else if (__vetor[mid] > __key)
			low = mid + 1;
		else
			return true;

	}

	return false;

}

void array__print(const int *__vetor, int __tam)
{

	int i;
	for (i = 0; i < __tam; ++i)
		printf("%d ", __vetor[i]);

}

void insertionSort(int *__vetor, int __tam)
{

	int i, j, pivot;
	i = 1;

	while (i < __tam)
	{

		j = i - 1;
		pivot = __vetor[i];

		while (j >= 0 && __vetor[j] > pivot)
			__vetor[j + 1] = __vetor[j], --j;

		__vetor[j + 1] = pivot;
		++i;

	}

}

void bubbleSort(int *__vetor, int __tam)
{

	int i, j;
	while (__tam--)
	{

		for (i = 0; i < __tam; ++i)
			if (__vetor[i] > __vetor[i + 1])
			{

				__vetor[i] ^= __vetor[i + 1];
				__vetor[i + 1] ^= __vetor[i];
				__vetor[i] ^= __vetor[i + 1];

			}

	}

}

void quickSort(int *__vetor, int __tam)
{

	quickSort_v(__vetor, 0, __tam - 1);

}

void quickSort_v(int *__vetor, int __ini, int __fim)
{

	int i, j, pivo, tmp;
	if (__ini < __fim)
	{

		i = __ini;
		j = __fim;
		pivo = __vetor[(i + j) / 2];

		do
		{

			while (__vetor[i] < pivo)
				++i;
			while (__vetor[j] > pivo)
				--j;

			if (i <= j)
			{	

				tmp = __vetor[i];
				__vetor[i] = __vetor[j];
				__vetor[j] = tmp;
				++i, --j;

			}

		} while (i <= j);

		quickSort_v(__vetor, __ini, j);
		quickSort_v(__vetor, i, __fim);

	}

}
