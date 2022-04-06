CC = gcc -Wall

static:
	echo "STATIC LIB" >> raport3a.txt
	make clean
	$(CC) -c mylib.c
	ar crs libmylib.a mylib.o
	$(CC) main.c -o main -L. -lmylib

shared:
	echo "SHARED LIB" >> raport3a.txt
	make clean
	$(CC) -fPIC -c mylib.c
	$(CC) -shared -fPIC -o libmylib.so mylib.o
	$(CC) main.c -o main -L. -lmylib -Wl,-rpath=`pwd`


dynamic:
	echo "DYNAMIC LIB" >> raport3a.txt
	make clean
	$(CC) -fPIC -c mylib.c -o mylib.o
	$(CC) -Wl,-rpath=. -fPIC -shared -o libmylib.so mylib.o
	$(CC) -fPIC -L. -o main_dynamic main_dynamic.c -ldl -D DYNAMIC

clean:
	rm -f *.o
	rm -f *.a
	rm -f *.so
	rm -f main
	rm -f main_dynamic

run:
	./main 4 create_table 3 wc_files big.txt medium.txt small.txt remove_block 1 remove_block 0
	./main 10 create_table 9 wc_files big.txt medium.txt small.txt big.txt medium.txt small.txt big.txt medium.txt small.txt remove_block 3 remove_block 3 remove_block 3 remove_block 3 remove_block 3 remove_block 2 remove_block 1 remove_block 0
	./main 17 create_table 8 wc_files big.txt remove_block 0 wc_files big.txt remove_block 0 wc_files big.txt remove_block 0 wc_files big.txt remove_block 0 wc_files big.txt remove_block 0 wc_files big.txt remove_block 0 wc_files big.txt remove_block 0 wc_files big.txt remove_block 0

run_dynamic:
	./main_dynamic 4 create_table 3 wc_files big.txt medium.txt small.txt remove_block 1 remove_block 0
	./main_dynamic 4 create_table 9 wc_files big.txt medium.txt small.txt big.txt medium.txt small.txt big.txt medium.txt small.txt remove_block 3 remove_block 3 remove_block 3 remove_block 3 remove_block 3 remove_block 2 remove_block 1 remove_block 0
	./main_dynamic 17 create_table 8 wc_files big.txt remove_block 0 wc_files big.txt remove_block 0 wc_files big.txt remove_block 0 wc_files big.txt remove_block 0 wc_files big.txt remove_block 0 wc_files big.txt remove_block 0 wc_files big.txt remove_block 0 wc_files big.txt remove_block 0

zad3a:
	make static
	make run
	make shared
	make run
	make dynamic
	make run_dynamic