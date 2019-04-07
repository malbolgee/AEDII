output: main.o vetor.o list.o
	gcc main.o vetor.o list.o -o output

main.o: main.c
	gcc -O2 -c main.c -Wall

vetor.o: vetor.c vetor.h
	gcc -O2 -c vetor.c -Wall

list.o: list.c list.h
	gcc -O2 -c list.c -Wall

clean:
	rm *.o