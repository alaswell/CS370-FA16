#	target: [dependencies]*
#		[<tab><target><endl>]
#
#	dependency1: file(s)
#		compile command

exec: PA1.c 
	g++ PA1.c -o PA1.out

debug: 
	g++ -g PA1.c -o debug.out

clean:
	rm -rf *.o hello

tar: 
	tar -cvf PA1.tar *.c *.o makefile
