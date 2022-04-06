CC = gcc -Wall

static:
	echo "STATIC LIB" >> raport2.txt
	make clean
	$(CC) -c mylib.c
	ar crs libmylib.a mylib.o
	$(CC) main.c -o main -L. -lmylib

shared:
	echo "SHARED LIB" >> raport2.txt
	make clean
	$(CC) -fPIC -c mylib.c
	$(CC) -shared -fPIC -o libmylib.so mylib.o
	$(CC) main.c -o main -L. -lmylib -Wl,-rpath=`pwd`

clean:
	rm -f *.o
	rm -f *.a
	rm -f *.so
	rm -f main

run:
	./main 4 create_table 3 wc_files big.txt medium.txt small.txt remove_block 1 remove_block 0
	./main 4 create_table 9 wc_files big.txt medium.txt small.txt big.txt medium.txt small.txt big.txt medium.txt small.txt remove_block 1 remove_block 0
	./main 7 create_table 8 wc_files big.txt medium.txt small.txt remove_block 0 wc_files big.txt medium.txt small.txt remove_block 0 wc_files big.txt medium.txt small.txt remove_block 0

zad2:
	make static
	make run
	make shared
	make run