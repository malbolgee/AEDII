output: main.o array.o b_tree.o avl_tree.o
	gcc main.o array.o b_tree.o avl_tree.o -o output

main.o: main.c
	gcc -O2 -c main.c

array.o: array.c
	gcc -O2 -c array.c

b_tree.o: b_tree.c
	gcc -O2 -c b_tree.c

avl_tree.o: avl_tree.c
	gcc -O2 -c avl_tree.c

clean:
	rm *.o