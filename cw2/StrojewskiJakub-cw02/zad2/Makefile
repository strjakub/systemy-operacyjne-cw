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
	echo "LIB" >> pomiar_zad_2
	$(CC) main-lib.c -o main
	./main a we

run_sys:
	make clean
	echo "SYS" >> pomiar_zad_2
	$(CC) main-sys.c -o main
	./main a we

run:
	make run_lib
	make run_sys