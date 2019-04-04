#include <stdbool.h>
#pragma once

#define __MAXSIZE 1000000
#define __MAXSIZEORD 100000
#define __ARRAY__RANDOM__ELEMENT ((rand() % (__MAXSIZEORD) << 2) + 1)
#define SEED srand(time(NULL))

int* array(int __size);
void free__array(int *__array);
void array__fill__random(int argc, ...);
void quickSort(int *__array, int __size);
void bubbleSort(int *__array, int __size);
void insertionSort(int *__array, int __size);
void array__print(const int *__array, int __size);
void array__fill__ordered(int *__array, int __szie);
void quickSort_v(int *__array, int __ini, int __fim);
bool buscaBin(const int *__array, int __size, int __key);
bool array__search(const int *__array, int __size, int __key);
