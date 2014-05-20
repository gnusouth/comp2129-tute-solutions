CC = clang
CFLAGS = -W -Wall -pedantic -pg -g -std=gnu11
LDFLAGS = -lpthread

EXECUTABLES = philosophers matrixmult matrixmult_parallel sieve

default: $(EXECUTABLES)

clean:
	rm -f $(EXECUTABLES)

.PHONY: default clean
