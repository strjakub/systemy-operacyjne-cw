CC = gcc -Wall

clean:
	rm -f *.o
	rm -f *.a
	rm -f *.so
	rm -f main
	rm -f fork
	rm -f exec

run:
	make clean
	$(CC) -DFORK main.c -o fork
	$(CC) -DEXEC main.c -o exec
	./fork ignore
	./fork handler
	./fork pending
	./exec ignore
	./exec handler
	./exec pending
	make clean