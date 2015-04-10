all:
	gcc -Wall -O2 -c hiddata.c
	gcc -Wall -O2 -c main.c
	ar -r libc64fc.a main.o hiddata.o

clean:	
	rm -f *.o libc64fc.a
