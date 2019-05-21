#include <stdint.h>
#pragma once

typedef struct __node__hash{

	int data;
	unsigned register_pointer;
	struct __node__hash *next;

} element_t;

typedef struct __hash__table{

	element_t *first;
	element_t *last;

} hash_t;

#define ROTL32(x, y) __rotl(x, y);

hash_t * make__hash__table(const unsigned __size);
void hash__push(hash_t *__hash, const unsigned __register_pointer, const char *__data);
int hash__search(hash_t *__hash, const char *__data);