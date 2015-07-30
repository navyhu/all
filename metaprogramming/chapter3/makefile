CFLAGS='-std=c++11'
CC=g++
#targets=quantity exercise0 exercise1_2 exercise3_4 exercise5 exercise6 exercise7
targets=exercise7

all:
	-mkdir -p bin
	for i in $(targets); do $(CC) $(CFLAGS) -o bin/$$i $$i.cpp; done

clean:
	rm -fR bin

.PHONY:clean all
