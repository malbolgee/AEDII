#include "array.h"
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

int * array(const int __size)
{

	return (int *) malloc(sizeof(int) * __size);

}

void free__array(int *__array)
{

	free(__array);

}

bool array__linear__search(const int *__array, const int __size, const int __key)
{

	unsigned i;
	for (i = 0; i < __size; ++i)
		if (__array[i] == __key)
			return true;

	return false;

}

bool binary__search(const int *__array, const int __size, const int __key)
{

	int hi, low, mid;

	low = 0;
	hi = __size - 1;

	while (low <= hi)
	{
		mid = (low + hi) / 2;
		if (__array[mid] < __key)
			hi = mid - 1;
		else if (__array[mid] > __key)
			low = mid + 1;
		else
			return true;

	}

	return false;

}

void array__print(const int *__array, const int __size)
{

	int i;
	for (i = 0; i < __size; ++i)
		printf("%d ", __array[i]);

}

void print__array__to__idx(const int *__array, const int __idx)
{

	int i;
	for (i = 0; i < __idx; ++i)
		printf("%d ", __array[i]);

}

void array__fill__ordered(int *__array, const int __size)
{

	int i, j;
	for (i = 0, j = 0; i < __size; ++i, j += (rand() % 499) + 1)
		__array[i] = j;

}

void insertionSort(int *__array, const int __size)
{

	int i, j, pivot;
	i = 1;

	while (i < __size)
	{

		j = i - 1;
		pivot = __array[i];

		while (j >= 0 && __array[j] > pivot)
			__array[j + 1] = __array[j], --j;

		__array[j + 1] = pivot;
		++i;

	}

}

void bubbleSort(int *__array, int __size)
{

	int i;
	while (__size--)
	{

		for (i = 0; i < __size; ++i)
			if (__array[i] > __array[i + 1])
			{

				__array[i] ^= __array[i + 1];
				__array[i + 1] ^= __array[i];
				__array[i] ^= __array[i + 1];

			}

	}

}

void quickSort(int *__array, int __size)
{

	quickSort_v(__array, 0, __size - 1);

}

void quickSort_v(int *__array, int __ini, int __fim)
{

	int i, j, pivot, tmp;
	if (__ini < __fim)
	{

		i = __ini;
		j = __fim;
		pivot = __array[(i + j) / 2];

		do
		{

			while (__array[i] < pivot)
				++i;
			while (__array[j] > pivot)
				--j;

			if (i <= j)
			{	

				tmp = __array[i];
				__array[i] = __array[j];
				__array[j] = tmp;
				++i, --j;

			}

		} while (i <= j);

		quickSort_v(__array, __ini, j);
		quickSort_v(__array, i, __fim);

	}

}

void array__fill__random(const unsigned __size, const unsigned __argc,...)
{

	unsigned i, j;
	int *a[__argc];
	va_list valist;

	va_start(valist, __argc);

	for (i = 0; i < __argc; ++i)
		a[i] = va_arg(valist, int *);

	for (i = 0; i < __size; ++i)
		a[0][i] = __ARRAY__RANDOM__ELEMENT(__MAXSIZEORD);

	for (i = 1; i < __argc; ++i)
		for (j = 0; j < __size; ++j)
			a[i][j] = a[i - 1][j];
	
	va_end(valist);

}

void unbiased__random__array__fill(int *__array, const int __size)
{

	int tmp;
	unsigned i, idx;
	char *seen = (char *) calloc(__size << 2, sizeof(char));

	i = 0;
	tmp = __size;
	while (tmp > 0)
	{

		idx = __ARRAY__UNBIASED__RANDOM__ELEMENT(__size << 1);
		if (!seen[idx])
			__array[i++] = idx, --tmp, seen[idx] = true;

	}

	free(seen);

}

unsigned uniformily__rand(const unsigned n) 
{

	if (n == RAND_MAX + 1)
		return rand(); 
	else
	{ 

		int k; 
		long limit = (RAND_MAX / n) * n; 
		while (true)
		{

			k = rand();
			if (k < limit) 
				break;

		}

		return (k % n) + 1; 

	}

}

void partially__ordered__array__fill(int *__array, const int __size)
{

	unsigned i;
	bool *seen = (bool *) calloc(__size, sizeof(bool));

	unsigned char limit = (95 * 100) / __size;
	while (limit > 0)
	{

		unsigned idx = rand() % __size;
		if (!seen[idx])
			__array[idx] = idx + 800, seen[idx] = true, --limit;

	}

	free(seen);

	for (i = 0; i < __size; ++i)
		if (__array[i] == 0)
			__array[i] = __array[i - 1];

	seen = (bool *) calloc(__size, sizeof(bool));

	limit = 10;

	while (limit > 0)
	{

		unsigned idxO = rand() % __size;
		unsigned idxD = rand() % __size;

		while (idxD == idxO)
			idxD = rand() % __size;

		if (!seen[idxD] && !seen[idxO])
		{


			int aux = __array[idxD];
			__array[idxD] = __array[idxO];
			__array[idxO] = aux;
			seen[idxD] = true; seen[idxO] = true;
			--limit;

		}

	}

	free(seen);

}

void array__no__repetition__fill(int *__array, const int __size)
{

	int tmp;
	unsigned i, idx;
	char *seen = (char *) calloc(__size, sizeof(char));

	i = 0;
	tmp = __size;
	while (tmp > 0)
	{

		idx = (rand() % __size) + 1;
		if (!seen[idx])
			__array[i++] = idx, --tmp, seen[idx] = true;

	}

	free(seen);

}