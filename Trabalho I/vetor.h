#include <stdbool.h>
#pragma once

#define __MAXSIZE 1000000
#define __MAXSIZEORD 100000
#define __ARRAY__RANDOM__ELEMENT ((rand() % (__MAXSIZEORD) << 2) + 1)

int* array(const int __size);
void free__array(int *__array);
void quickSort(int *__array, int __size);
void bubbleSort(int *__array, int __size);
void insertionSort(int *__array, const int __size);
void array__print(const int *__array, const int __size);
void array__fill__ordered(int *__array, const int __size);
void quickSort_v(int *__array, int __ini, int __fim);
void print__array__to__idx(const int *__array, const int __idx);
void array__fill__random(const int __size, const int __argc, ...);
bool binary__search(const int *__array, int __size, const int __key);
bool array__linear__search(const int *__array, const int __size, const int __key);
