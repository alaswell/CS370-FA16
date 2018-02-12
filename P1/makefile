#	target: [dependencies]*
#		[<tab><target><endl>]
#
#	dependency1: file(s)
#		compile command

exec: PA1.o 
	g++ PA1.c -o PA1.out

main.o: main.cpp functions.h
	g++ PA1.c

clean:
	rm -rf *.o hello

tar: 
	tar -cvf PA1.tar *.c *.o makefile
