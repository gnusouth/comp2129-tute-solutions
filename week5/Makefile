# Setting the C compiler here means that it gets used for make's inbuilt rules
CC = gcc

# Same for CFLAGS, but we can also insert it explicitly with $(CFLAGS)
CFLAGS = -Wall -W -std=c99 -pedantic -g

all: preproc queue_demo

# Let's compile preproc one step at a time.
# Remember that $@ is the target and $^ is all the dependencies.
# See if you can edit this to make the secret message appear.
# Which stage should you add -DDEBUG at?
preproc: preproc.o
	gcc $(CFLAGS) -o $@ $^

preproc.o: preproc.s
	gcc $(CFLAGS) -c -o $@ $^

preproc.s: preproc.i
	gcc $(CFLAGS) -S -o $@ $^

preproc.i: preproc.c
	gcc $(CFLAGS) -DDEBUG -E -o $@ $^

queue_demo: queue_demo.c queue.o
	gcc $(CFLAGS) -o $@ $^

queue.o: queue.c queue.h

clean:
	rm -f *.o preproc.s preproc.i
	rm -f queue_demo preproc

# Phony should depend on all targets that aren't real files (they're "phony" targets).
.PHONY: all clean
