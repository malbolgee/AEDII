#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#pragma once

typedef struct __hash__array__type{

	int data;
	unsigned registry_pointer;

} hash_t;

#ifndef PRIME_HASH_SIZE
	#define PRIME_HASH_SIZE 100003U // A prime number for the hash table size.
#endif

#define COL_START_P PRIME_HASH_SIZE + 1 // Marks the beginning of the 'collision-zone'.
#define COL_END_P (unsigned)((PRIME_HASH_SIZE * 0.15F) + COL_START_P + 1) // Calculates 15% plus space for the 'collision-zone'. 
#define MAX_HASH_SIZE COL_END_P // Real size of the hash table.
#define EMPTY -1

hash_t * make__hash__table(const unsigned __size);
void     hash__push(hash_t *__hash, const unsigned __data, const unsigned __rp);
void     hash__find(hash_t *__hash, const unsigned __data, FILE *__STREAM);