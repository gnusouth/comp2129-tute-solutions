CC = gcc
CFLAGS = -W -Wall -std=gnu99 -pedantic

EXECUTABLES = ex1 ex2 ex3 ex4 ex5 ex6 ex7 copycat

all: $(EXECUTABLES)

ex%: ex%.c

ex4: ex4.c
	$(CC) $(CFLAGS) -o $@ $< -lm

copycat: copycat.c

clean:
	rm -f $(EXECUTABLES)

.PHONY: all clean
