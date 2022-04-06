CC = gcc -Wall

clean:
	rm -f *.o
	rm -f *.a
	rm -f *.so
	rm -f main
	rm -f main-lib
	rm -f main-sys

run_lib:
	make clean
	echo "LIB" >> pomiar_zad_1
	$(CC) main-lib.c -o main

run_sys:
	make clean
	echo "SYS" >> pomiar_zad_1
	$(CC) main-sys.c -o main

run:
#	make run_lib
#	./main
#	make run_sys
#	./main
	make run_lib
	./main we wy
	make run_sys
	./main we wy
