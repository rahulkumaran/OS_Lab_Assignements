all: Run

Run: main.o shmcsa.h
	gcc main.o -o Run
main.o: main.c
	gcc -Wall -c main.c 
clean:
	rm -rf *.o Run
