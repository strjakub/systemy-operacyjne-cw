CC = gcc -Wall

clean:
	rm -f *.o
	rm -f *.a
	rm -f *.so
	rm -f main
	rm -f main_s
	rm -f main_c

compile:
	make clean
	$(CC) catcher.c -o main_c
	$(CC) sender.c -o main_s
