CFLAGS='-std=c++11'
CC=g++
targets=practice1 morepractice1 exercise2
sources=practice1.cpp morepractice1.cpp exercise2.cpp

all:
	-mkdir bin
	for i in $(targets); do $(CC) $(CFLAGS) -o bin/$$i $$i.cpp; done

clean:
	rm -fR bin

.PHONY:clean all
