#pragma once

#define __MAXSIZE 1000000
#define __MAXSIZEORD 100000
#define __ARRAY__RANDOM__ELEMENT(x) ((rand() % (x << 2) + 1))
#define __ARRAY__UNBIASED__RANDOM__ELEMENT(x) (uniformily__rand(x))

int * array(const unsigned __size);
void free__array(int *__array);
void quickSort(int *__array, const unsigned __size);
static void quickSort_v(int *__array, int __ini, int __fim);
void bubbleSort(int *__array, unsigned __size);
void insertionSort(int *__array, const unsigned __size);
void array__print(const int *__array, const unsigned __size);
void array__fill__ordered(int *__array, const unsigned __size);
void print__array__to__idx(const int *__array, const unsigned __idx);
void array__fill__random(const unsigned __size, const unsigned __argc, ...);
int binary__search(const int *__array, const unsigned __size, const int __key);
int array__linear__search(const int *__array, const unsigned __size, const int __key);
void partially__ordered__array__fill(int *__array, const unsigned __size);
void array__no__repetition__fill(int *__array, const unsigned __size);