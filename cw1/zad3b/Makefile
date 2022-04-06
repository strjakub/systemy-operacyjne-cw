CC = gcc -Wall

static:
	echo "STATIC LIB" >> raport3b.txt
	make clean
	$(CC) -c mylib.c
	ar crs libmylib.a mylib.o

shared:
	echo "SHARED LIB" >> raport3b.txt
	make clean
	$(CC) -fPIC -c mylib.c
	$(CC) -shared -fPIC -o libmylib.so mylib.o


dynamic:
	echo "DYNAMIC LIB" >> raport3b.txt
	make clean
	$(CC) -fPIC -c mylib.c -o mylib.o
	$(CC) -Wl,-rpath=. -fPIC -shared -o libmylib.so mylib.o

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

zad3b:
	echo "-----------" >> raport3b.txt
	echo "    -O0    " >> raport3b.txt
	echo "-----------" >> raport3b.txt
	make static
	$(CC) main.c -o main -L. -lmylib -O0
	make run
	make shared
	$(CC) main.c -o main -L. -lmylib -Wl,-rpath=`pwd` -O0
	make run
	make dynamic
	$(CC) -fPIC -L. -o main_dynamic main_dynamic.c -ldl -D DYNAMIC -O0
	make run_dynamic
	echo "-----------" >> raport3b.txt
	echo "    -O2    " >> raport3b.txt
	echo "-----------" >> raport3b.txt
	make static
	$(CC) main.c -o main -L. -lmylib -O2
	make run
	make shared
	$(CC) main.c -o main -L. -lmylib -Wl,-rpath=`pwd` -O2
	make run
	make dynamic
	$(CC) -fPIC -L. -o main_dynamic main_dynamic.c -ldl -D DYNAMIC -O2
	make run_dynamic
	echo "-----------" >> raport3b.txt
	echo "    -Os    " >> raport3b.txt
	echo "-----------" >> raport3b.txt
	make static
	$(CC) main.c -o main -L. -lmylib -Os
	make run
	make shared
	$(CC) main.c -o main -L. -lmylib -Wl,-rpath=`pwd` -Os
	make run
	make dynamic
	$(CC) -fPIC -L. -o main_dynamic main_dynamic.c -ldl -D DYNAMIC -Os
	make run_dynamic
