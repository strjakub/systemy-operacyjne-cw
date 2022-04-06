CC = gcc -Wall

clean:
	rm -f *.o
	rm -f *.a
	rm -f *.so
	rm -f main
	rm -f count
	rm -f w*.txt

run:
	make clean
	$(CC) count.c -o count
	$(CC) main.c -o main
	./main 10
	sleep 1
	make clean
	$(CC) count.c -o count
	$(CC) main.c -o main
	./main 20
	sleep 1
	make clean
	$(CC) count.c -o count
	$(CC) main.c -o main
	./main 50
	sleep 1
	make clean