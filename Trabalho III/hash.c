#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hash.h"

static uint32_t __rotl(uint32_t __x, int8_t __r);
static uint32_t __avalanche(uint32_t __h);
static uint32_t murmurhash(const void *__key, const uint32_t __len, uint32_t __seed);

hash_t * make__hash__table(const unsigned __size)
{

	unsigned i;
	hash_t *__hash = (hash_t *) calloc(__size, sizeof(hash_t));
	if (!__hash)
		exit(1);

	return __hash;

}

void hash__push(hash_t *__hash, const unsigned __register_pointer, const char *__data)
{

	element_t *aux;
	aux = (element_t *) malloc(sizeof(element_t));

	if (!aux)
		exit(1);

	uint32_t idx = murmurhash(__data, strlen(__data), 123);

	if (__hash[idx].first)
		__hash[idx].last->next = aux;
	else
		__hash[idx].first = aux;

	__hash[idx].last = aux;
	aux->next = NULL;
	aux->data = atoi(__data);
	aux->register_pointer = __register_pointer;

}

int hash__search(hash_t *__hash, const char *__data)
{

	element_t *aux;
	unsigned idx = murmurhash(__data, strlen(__data), 123);

	unsigned id = atoi(__data);
	aux = __hash[idx].first;

	if (!aux)
		return -1;

	if (aux->data == id)
		return aux->register_pointer;
	else
	{

		while (aux)
		{

			if (aux->data == id)
				return aux->register_pointer;

			aux = aux->next;			

		}

		return -1;
		
	}

}

static uint32_t __rotl(uint32_t __x, int8_t __r)
{

	return (__x << __r) | (__x >> (32 - __r));

}

static uint32_t __avalanche(uint32_t __h)
{

	__h ^= __h >> 16;
	__h *= 0x85ebca6b;
	__h ^= __h >> 13;
	__h *= 0xc2b2ae35;
	__h ^= __h >> 16;

	return __h;

}

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

	return h % 10177;

}