#include <stdbool.h>
#pragma once

#define __MAXSIZE 1000000
#define __MAXSIZEORD 100000

int* array(int __tam);
void free__array(int *__vetor);
void quickSort(int *__vetor, int __tam);
void bubbleSort(int *__vetor, int __tam);
void insertionSort(int *__vetor, int __tam);
void array__print(const int *__vetor, int __tam);
void quickSort_v(int *__vetor, int __ini, int __fim);
bool buscaBin(const int *__vetor, int __tam, int __key);
bool array__search(const int *__vetor, int __tam, int __key);
