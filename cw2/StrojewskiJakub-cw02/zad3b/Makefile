CC = gcc -Wall

clean:
	rm -f *.o
	rm -f *.a
	rm -f *.so
	rm -f main
	rm -f main-lib
	rm -f main-sys

run:
	make clean
	$(CC) main.c -o main
	./main one
