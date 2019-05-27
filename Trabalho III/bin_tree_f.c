#include "product.h"
#include "bin_tree_f.h"
#include <stdio.h>

/* Range query in the BST index for values greater or  equal 
   to k1 and smaller or equal to k2 on STREAM. */
void BST__price__range__query(BST_p_t *__root, const float __k1, const float __k2, FILE *__STREAM)
{

	if (!__root)
		return;

	if (__k1 <= __root->key)
		BST__price__range__query(__root->left, __k1, __k2, __STREAM);

	if (__k1 <= __root->key && __k2 >= __root->key)
	{

		product_t tmp;
		fseek(__STREAM, __root->registry_pointer * sizeof(product_t), SEEK_SET);
		fread(&tmp, sizeof(product_t), 1, __STREAM);
		info_print(tmp);

	}

	if (__k2 >= __root->key)
		BST__price__range__query(__root->right, __k1, __k2, __STREAM);


}