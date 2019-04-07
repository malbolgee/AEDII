#include "list.h"
#include <stdlib.h>
#include <stdio.h>

void list(l_list *__l1)
{

	__l1->primeiro = NULL;
	__l1->ultimo = NULL;

}

void push(l_list *__l1, const int __dado)
{

	__tipoNo *auxiliar;
	auxiliar = (__tipoNo *) malloc(sizeof(__tipoNo));

	if (!auxiliar)
		exit(1);

	if (__l1->primeiro)
		__l1->ultimo->proximo = auxiliar;
	else
		__l1->primeiro = auxiliar;

	__l1->ultimo = auxiliar;
	auxiliar->proximo = NULL;
	auxiliar->dado = __dado;

}

void array__to__list(l_list *__l1, const int *__array, const int __array__size)
{

	int i;
	for (i = 0; i < __array__size; ++i)
		push(__l1, __array[i]);

}


bool list__search(const l_list *__l1, const int __key)
{

	__tipoNo * auxiliar;
	auxiliar = __l1->primeiro;

	while (auxiliar)
	{

		if (auxiliar->dado == __key)
			return true;

		auxiliar = auxiliar->proximo;

	}

	return false;

}

void print__list(const l_list *__l1)
{

	__tipoNo *auxiliar;
	auxiliar = __l1->primeiro;

	while (auxiliar)
	{

		printf("%d ", auxiliar->dado);
		auxiliar = auxiliar->proximo;

	}

}

void erase__list(l_list *__l1)
{
	
	__tipoNo *tmp;
	__tipoNo *auxliliar = __l1->primeiro;
	
	while (auxliliar)
	{

		tmp = auxliliar;
		auxliliar = auxliliar->proximo;
		free(tmp);
		
	}

	__l1->primeiro = __l1->ultimo = NULL;

}

void print__list__to__idx(const l_list *__l1, int __idx)
{

	int i = 0;
	__tipoNo *auxiliar;
	auxiliar = __l1->primeiro;

	if (!auxiliar)
		return;

	while (i < __idx && auxiliar)
	{

		printf("%d ", auxiliar->dado);
		++i, auxiliar = auxiliar->proximo;

	}

}