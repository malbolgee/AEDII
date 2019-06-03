output: main.o bin_tree.o hash.o product.o fort.o bin_tree_un.o
	gcc main.o bin_tree.o hash.o product.o fort.o bin_tree_un.o -o output

main.o: main.c
	gcc -c main.c

fort.o: fort.c
	gcc -c fort.c

bin_tree_f.o: bin_tree_un.c
	gcc -c bin_tree_un.c

product.o: product.c
	gcc -c product.c

bin_tree.o: bin_tree.c
	gcc -c bin_tree.c

avl_tree.o: hash.c
	gcc -c hash.c

clean:
	rm *.o