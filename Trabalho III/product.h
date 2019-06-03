#include <stdio.h>
#pragma once

typedef struct __product__type{

	unsigned id;
	char name[51];
	char description[101];
	float price;
	unsigned availability;
	unsigned due;

} product_t;

#define MAX_UN_SIZE 100000U
#define MAX_ID 2000000000U

int  get_product_info(product_t *__product, FILE *__STREAM);
void info_print(product_t produto);
int  linear__registry__search(const unsigned __key, FILE *__STREAM);
int  linear__conditional__un__query(FILE *__STREAM, const unsigned __key, const char __delim);
int  linear__range__un__query(FILE *__STREMA, const unsigned __delim1, const unsigned __delim2);