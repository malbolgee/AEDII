#include <stdint.h>
#pragma once

typedef struct __node__hash{

	int data;
	unsigned register_pointer;
	struct __node__hash *next;

} __node__hash;

typedef struct __hash__table{

	__node__hash *first;
	__node__hash *last;

} hash_t;

#define ROTL32(x, y) __rotl(x, y);

void hash_push(hash_t *__hash, const unsigned __register_pointer, const int __data);
void hash_search(hash_t *__hash, const int __data);