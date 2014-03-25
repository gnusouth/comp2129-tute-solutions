CC = gcc
CFLAGS = -W -Wall -std=c99 -pedantic -g

EXECUTABLES = break_me format_strings segfault stats swapfest

all: $(EXECUTABLES)

break_me: break_me.c

format_strings: format_strings.c

segfault: segfault.c

swapfest: swapfest.c

swap_experiment: swapfest.c
	$(CC) $(CFLAGS) -D_EXPERIMENT -o swap_experiment swapfest.c

stats: stats.c
	$(CC) $(CFLAGS) -o stats stats.c -lm

clean:
	rm -f $(EXECUTABLES)

.PHONY: all clean
