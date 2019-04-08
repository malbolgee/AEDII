#include <stdbool.h>
#pragma once

typedef struct __tipoNo{

	int dado;
	struct __tipoNo *proximo;

} __tipoNo;

typedef struct __list{

	__tipoNo *primeiro;
	__tipoNo *ultimo;

} l_list;

void list(l_list *__l1);
void erase__list(l_list *__l1);
void push(l_list *__l1, const int __dado);
void print__list(const l_list *__l1);
bool list__search(const l_list *__l1, int __key);
void print__list__to__idx(const l_list *__l1, const int __idx);
void array__to__list(l_list *__l1, const int *__array, const int __size);