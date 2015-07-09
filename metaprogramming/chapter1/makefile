targets=bin/tpractice1 bin/tmorepractice1

sources=practice1.cpp morepractice1.cpp

all:$(targets)

$(targets):$(sources)
	g++ -std=c++11 -o $@ $<

clean:
	rm -f $(targets)

.PHONY:clean all
