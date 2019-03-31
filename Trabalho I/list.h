#include <stdbool.h>
#pragma once

typedef struct __tipoNo{

	int dado;
	struct __tipoNo *proximo;

} __tipoNo;

typedef struct __list{

	__tipoNo *primeiro;
	__tipoNo *ultimo;

} __list;

typedef __list l_list;

void list(__list *__l1);
void erase__list(__list *__l1);
void push(__list *__l1, int __dado);
void print__list(const __list *__l1);
bool list__search(const __list *__l1, int __key);
void print__list__to__idx(const __list *__l1, int __idx);
