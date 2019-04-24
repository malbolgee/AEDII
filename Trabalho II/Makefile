output: main.o array.o bin_tree.o avl_tree.o
	gcc main.o array.o bin_tree.o avl_tree.o -o output

main.o: main.c
	gcc -O2 -c main.c

array.o: array.c
	gcc -O2 -c array.c

bin_tree.o: bin_tree.c
	gcc -O2 -c bin_tree.c

avl_tree.o: avl_tree.c
	gcc -O2 -c avl_tree.c

clean:
	rm *.o