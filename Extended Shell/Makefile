all: Run
Run: main.o main.h
	gcc main.o -o Run
main.o: main.c
	gcc -Wall -c main.c 
clean:
	rm -rf *.o Run
