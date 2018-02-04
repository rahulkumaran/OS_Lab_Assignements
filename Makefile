all : Run
Run : main.o server.h client.h structures.h
	gcc main.o -o Run
main.o : main.c
	gcc -c -Wall main.c
clean:
	rm -rf *.o Run
