#include <stdint.h>
#include <stdio.h>
#pragma once

typedef struct __hash__array__type{

	int data;
	unsigned registry_pointer;

} hash_t;

#define ROTL32(x, y) __rotl(x, y);

#define PRIME_HASH_SIZE 100003U // Prime number for hash table size.
#define COL_START_P PRIME_HASH_SIZE + 1
#define COL_END_P (unsigned)((PRIME_HASH_SIZE * 0.15F) + COL_START_P + 1)
#define MAX_HASH_SIZE COL_END_P
#define EMPTY -1

hash_t * make__hash__table(const unsigned __size);
void     hash__push(hash_t *__hash, const unsigned __data, const unsigned __rp);
void     hash__find(hash_t *__hash, const unsigned __data, FILE *__STREAM);