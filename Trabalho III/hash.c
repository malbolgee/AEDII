#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hash.h"
#include "product.h"

static uint32_t hash(uint32_t x);

extern unsigned __stt;
extern unsigned __end;
extern unsigned hash_colisions;

hash_t * make__hash__table(const unsigned __size)
{

	hash_t *hash = (hash_t *) malloc(sizeof(hash_t) * __size);
	if (hash == NULL)
		exit(1);

	memset(hash, -1, sizeof(hash) * __size);

	return hash;

}

void hash__push(hash_t *__hash, const unsigned __data, const unsigned __rp)
{

	unsigned idx = hash(__data) % (PRIME_HASH_SIZE);
	if (__hash[idx].data == EMPTY)
	{

		__hash[idx].data = __data;
		__hash[idx].registry_pointer = __rp;

	}
	else if (__hash[idx].data != EMPTY)
	{

		++hash_colisions;
		__hash[__end].data = __data;
		__hash[__end++].registry_pointer = __rp;

	}

}

void hash__find(hash_t *__hash, const unsigned __data, FILE *__STREAM)
{

	unsigned idx = hash(__data) % (PRIME_HASH_SIZE);

	if (__hash[idx].data == __data)
	{

		product_t tmp;
		fseek(__STREAM, __hash[idx].registry_pointer * sizeof(product_t), SEEK_SET);
		fread(&tmp, sizeof(product_t), 1, __STREAM);
		return;
		
	}
	else if (__hash[idx].data == EMPTY)
		return;
	else
	{

		unsigned i;
		for (i = COL_START_P; i < __end; ++i)
		{

			if (__hash[i].data == __data)
			{

				product_t tmp;
				fseek(__STREAM, __hash[i].registry_pointer * sizeof(product_t), SEEK_SET);
				fread(&tmp, sizeof(product_t), 1, __STREAM);
				return;

			}

		}

		return;

	}

}

/* MurMurHash3 bitmixer. */
static uint32_t hash(uint32_t x)
{

	x ^= x >> 16;
	x *= 0x85ebca6b;
	x ^= x >> 13;
	x *= 0xc2b2ae35;
	x ^= x >> 16;
	
    return x;

}