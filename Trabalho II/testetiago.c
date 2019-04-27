//Murtagh tests
#include <stdio.h>
#include "bin_tree.h"

int main(void){
    int i;
    int vet[] = {20,7,34,4,15,27,42,2,6,12,38};
    bin_tree *t;
    bin_tree *arv;
    arv = make__binary__tree();
    
    for(i = 0; i < 11; i++){
        arv = binary__tree__push(arv, vet[i]);
    }

    binary__tree__infix(arv);
    t = binary__tree__search(arv, 2);
    printf("\n\nValor de t->id: %d\n", t->id);
    printf("Valor do primeiro nó: %d\n", arv->id);

    t = __find__max__value__node(arv);
    printf("Valor máximo: %d\n", t->id);
    t = __find__min__value__node(arv);
    printf("Valor mínimo: %d\n", t->id);
    printf("Altura da árvore: %d\n", binary__tree__height(arv));
}
