output: main.o bin_tree.o hash.o
	gcc main.o bin_tree.o hash.o -o output

main.o: main.c
	gcc -c main.c

bin_tree.o: bin_tree.c
	gcc -c bin_tree.c

avl_tree.o: hash.c
	gcc -c hash.c

clean:
	rm *.o