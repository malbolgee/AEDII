output: main.o vetor.o list.o test.o
	gcc main.o vetor.o list.o test.o -o output

main.o: main.c
	gcc -c main.c

vetor.o: vetor.c vetor.h
	gcc -c vetor.c

list.o: list.c list.h
	gcc -c list.c

test.o: test.c test.h
	gcc -c test.c

clean:
	rm *.o