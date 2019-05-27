#include <stdint.h>
#include <stdio.h>
#pragma once

typedef struct __node__hash{

	int data;
	unsigned registry_pointer;
	struct __node__hash *next;

} element_t;

typedef struct __hash__table{

	element_t *first;
	element_t *last;

} hash_t;

#define ROTL32(x, y) __rotl(x, y);
#define MAXHASHSIZE 20011

hash_t * make__hash__table(const unsigned __size);
void     hash__push(hash_t *__hash, const char *__key, const unsigned __rp);
void     hash__search(hash_t *__hash, const char *__data, FILE *__STREAM);
unsigned hash__colisions(const hash_t *__hash, const unsigned __size);