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
