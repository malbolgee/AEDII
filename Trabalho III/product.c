#include "product.h"

/* Takes the information of a product_t from STREAM */
int get_product_info(product_t *__product, FILE *__STREAM)
{

	return fscanf(__STREAM, "%u%*[: ]%[ A-Za-z0-9-.&'+\"%%()\\/$é!#?ñ,]%*[: ]%[ A-Za-z0-9]%*[: ]%f%*[: ]%d%*[: ]%u\n", 
			&__product->id, __product->name, __product->description, &__product->price, 
			&__product->availability, &__product->due);
	
}

/* Prints a product_t type fields. */
void info_print(product_t produto)
{

	printf("Id: %d\nNome: %s\nDescrição: %s\nPreço: R$%.2f\nDisponibilidade: %d UN\nVencimento: %d\n\n",
		produto.id, produto.name, produto.description, produto.price, produto.availability, produto.due);

}

/* Linear search for key on STREAM */
int linear__registry__search(const unsigned __key, FILE *__STREAM)
{

	unsigned i;
	product_t aux;

	i = 0;
	while (fread(&aux, sizeof(product_t), 1, __STREAM) != 0)
	{
		
		if (aux.id == __key)
			return i;

		++i;

	}

	return -1;

}

/* Sequencial search for the key values spacified by the delim*/
int linear__conditional__price__query(FILE *__STREAM, const float __key, const char __delim)
{

	if (__delim == '>')
	{

		unsigned i = 0;
		product_t tmp;
		while (fread(&tmp, sizeof(product_t), 1, __STREAM) != 0)
			if (tmp.price > __key)
				++i;
				
		return i;

	}
	else if (__delim == '<')
	{

		unsigned i = 0;
		product_t tmp;
		while (fread(&tmp, sizeof(product_t), 1, __STREAM) != 0)
			if (tmp.price < __key)
				++i;
			
		return i;

	}
	
}

/* Sequential search in STREAM for the values that are inside 
   delimiters delim1 and delim2. */
int linear__range__price__query(FILE *__STREAM, const float __delim1, const float __delim2)
{
	
	unsigned i = 0;
	product_t tmp;
	while (fread(&tmp, sizeof(product_t), 1,__STREAM) != 0)
		if (tmp.price >= __delim1 && tmp.price <= __delim2)
			++i;

	return i;

}
