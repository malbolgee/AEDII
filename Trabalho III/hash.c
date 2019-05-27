#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hash.h"
#include "product.h"

static uint32_t __rotl(uint32_t __x, int8_t __r);
static uint32_t __avalanche(uint32_t __h);
static uint32_t murmurhash(const void *__key, const uint32_t __len, uint32_t __seed);

/* Makes a hash table of length SIZE. */
hash_t * make__hash__table(const unsigned __size)
{

	unsigned i;
	hash_t *__hash = (hash_t *) calloc(__size, sizeof(hash_t));
	if (!__hash)
		exit(1);

	return __hash;

}

/* Puts the key and its registry pointer into the hash table. */
void hash__push(hash_t *__hash, const char *__key, const unsigned __rp)
{

	element_t *aux = (element_t *) malloc(sizeof(element_t));

	if (!aux)
		exit(1);

	uint32_t idx = murmurhash(__key, strlen(__key), 0) % MAXHASHSIZE;

	if (__hash[idx].first)
		__hash[idx].last->next = aux;
	else
		__hash[idx].first = aux;

	__hash[idx].last = aux;
	aux->next = NULL;
	aux->data = atoi(__key);
	aux->registry_pointer = __rp;

}

/* Does a search for the key in the hash table index. */
void hash__search(hash_t *__hash, const char *__key, FILE *__STREAM)
{

	element_t *aux;
	unsigned idx = murmurhash(__key, strlen(__key), 0) % MAXHASHSIZE;

	unsigned id = atoi(__key);
	aux = __hash[idx].first;

	if (!aux)
		return;

	if (aux->data == id)
	{
		
		product_t tmp;
		fseek(__STREAM, aux->registry_pointer * sizeof(product_t), SEEK_SET);
		fread(&tmp, sizeof(product_t), 1, __STREAM);
		return;
		
	}
	else
	{

		while (aux)
		{

			if (aux->data == id)
			{
				
				product_t tmp;
				fseek(__STREAM, aux->registry_pointer * sizeof(product_t), SEEK_SET);
				fread(&tmp, sizeof(product_t), 1, __STREAM);
				return;

			}

			aux = aux->next;			

		}

		return;
		
	}

}

/* Does a left rotation of R bits in X. */
static uint32_t __rotl(uint32_t __x, int8_t __r)
{

	return (__x << __r) | (__x >> (32 - __r));

}

/* Bitmixer of h. */
static uint32_t __avalanche(uint32_t __h)
{

	__h ^= __h >> 16;
	__h *= 0x85ebca6b;
	__h ^= __h >> 13;
	__h *= 0xc2b2ae35;
	__h ^= __h >> 16;

	return __h;

}

/* Counts the number of colisions in the hash table. */
unsigned hash__colisions(const hash_t *__hash, const unsigned __size)
{

	element_t *j;
	unsigned i, ans = 0;

	for (i = 0; i < __size; ++i)
		if (__hash[i].first && __hash[i].first->next)
			for (j = __hash[i].first->next; j; j = j->next)
				++ans;

	return ans;

}

/* Hash function returns a 32bit hash number. */
static uint32_t murmurhash(const void *__key, const uint32_t __len, uint32_t __seed)
{

	char i;
	uint32_t k;
	const int nblocks = __len >> 2;
	const uint8_t *data = (const uint8_t *)__key;

	uint32_t h = __seed;

	const uint32_t c1 = 0xcc9e2d51;
	const uint32_t c2 = 0x1b873593;

	const uint32_t *blocks = (const uint32_t *)(data + nblocks * 4);

	for (i = -nblocks; i; ++i)
	{

		k = blocks[i];
		k = ROTL32(k, 15);
		k *= c2;

		h ^= k;
		h = ROTL32(h, 13);
		h = h * 5 + 0xe6546b64;

	}

	k = 0;
	const uint8_t *tail = (const uint8_t *)(data + nblocks * 4);
	
	switch(__len & 3)
	{

		case 3:
			k ^= tail[2] << 16;
			break;
		case 2:
			k ^= tail[1] << 8;
			break;
		case 1:
			k ^= tail[0];
			k *= c1; 
			k = ROTL32(k, 15);
			k *= c2; 
			h ^= k;
			break;

	};

	h ^= __len;
	h = __avalanche(h);

	return h;

}