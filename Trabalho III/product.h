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

int  get_product_info(product_t *__product, FILE *__STREAM);
void info_print(product_t produto);
int  linear__registry__search(const unsigned __key, FILE *__STREAM);
int  linear__conditional__price__query(FILE *__STREAM, const float __key, const char __delim);
int  linear__range__price__query(FILE *__STREMA, const float __delim1, const float __delim2);