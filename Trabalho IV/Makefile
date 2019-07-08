output: main.o graph.o
	gcc main.o graph.o -o output

main.o: main.c
	gcc -c main.c

graph.o: graph.c
	gcc -c graph.c

clean:
	rm *.o