#include "product.h"

/* Takes the information of a product_t from STREAM */
int get_product_info(product_t *__product, FILE *__STREAM)
{

	return fscanf(__STREAM, "%u%*[: ]%[ A-Za-z0-9-.&'+\"%%()\\/$!#?,]%*[: ]%[ A-Za-z0-9]%*[: ]%f%*[: ]%d%*[: ]%u\n", 
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

	product_t aux;
	unsigned i = 0;

	while (fread(&aux, sizeof(product_t), 1, __STREAM) != 0)
	{
		
		if (aux.id == __key)
			return i;

		++i;

	}

	return -1;

}

/* Sequencial search for the key values spacified by delim */
int linear__conditional__un__query(FILE *__STREAM, const unsigned __key, const char __delim)
{

	product_t tmp;	
	unsigned i = 0;

	if (__delim == '>')
	{
	
		while (fread(&tmp, sizeof(product_t), 1, __STREAM) != 0)
			if (tmp.availability > __key)
				++i;
				
		return i > 0 ? i : -1;

	}
	else if (__delim == '<')
	{

		while (fread(&tmp, sizeof(product_t), 1, __STREAM) != 0)
			if (tmp.availability < __key)
				++i;
			
		return i > 0 ? i : -1;

	}
	
}

/* Sequential search in STREAM for the values that are greater to 
   delim1 and lesser to delim2. */
int linear__range__un__query(FILE *__STREAM, const unsigned __delim1, const unsigned __delim2)
{
	
	product_t tmp;
	unsigned i = 0;

	while (fread(&tmp, sizeof(product_t), 1,__STREAM) != 0)
		if (tmp.availability > __delim1 && tmp.availability < __delim2)
			++i;

	return i;

}
