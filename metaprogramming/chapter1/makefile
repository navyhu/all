CFLAGS='-std=c++11'
CC=g++
targets=practice1 morepractice1 exercise2 exercise4

all:
	-mkdir -p bin
	for i in $(targets); do $(CC) $(CFLAGS) -o bin/$$i $$i.cpp; done

clean:
	rm -fR bin

.PHONY:clean all
