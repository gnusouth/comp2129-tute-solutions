CC = clang
CFLAGS = -W -Wall -pedantic -std=gnu11

EXECUTABLES = function_pointer int_sort race fast_sum

all: $(EXECUTABLES)

function_pointer: function_pointer.c

int_sort: int_sort.c

race: race.c
	$(CC) $(CFLAGS) race.c -o race -lpthread

fast_sum: fast_sum.c
	$(CC) $(CFLAGS) fast_sum.c -o fast_sum -lpthread

clean:
	rm -f $(EXECUTABLES)

.PHONY: clean
