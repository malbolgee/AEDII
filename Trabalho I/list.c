#include "list.h"
#include <stdlib.h>
#include <stdio.h>

void list(__list *__l1)
{

	__l1->primeiro = NULL;
	__l1->ultimo = NULL;

}

void push(__list *__l1, int __dado)
{

	__tipoNo *auxiliar;
	auxiliar = (__tipoNo *) malloc(sizeof(__tipoNo));

	if (!auxiliar)
		exit(1);

	if (__l1->primeiro)
	{

		__l1->ultimo->proximo = auxiliar;
		auxiliar->proximo = NULL;

	}
	else
		__l1->primeiro = auxiliar;

	__l1->ultimo = auxiliar;
	auxiliar->dado = __dado;

}

bool list__search(const __list *__l1, int __key)
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

void print__list(const __list *__l1)
{

	__tipoNo *auxiliar;
	auxiliar = __l1->primeiro;

	while (auxiliar)
	{

		printf("%d ", auxiliar->dado);
		auxiliar = auxiliar->proximo;

	}

}

void erase__list(__list *__l1)
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

void print__list__to__idx(const __list *__l1, int __idx)
{

	int i = 0;
	__tipoNo *auxiliar;
	auxiliar = __l1->primeiro;

	if (!auxiliar)
		return;

	while (i < __idx && auxiliar)
	{

		printf("%d\n", auxiliar->dado);
		++i, auxiliar = auxiliar->proximo;

	}

}