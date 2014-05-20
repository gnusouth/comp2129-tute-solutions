CC = clang
CFLAGS = -W -Wall -std=gnu11 -pedantic
LDFLAGS = -lpthread -lm

EXECUTABLES = monte-carlo monte-carlo-two-thirds

.PHONY: all clean

all: $(EXECUTABLES)

monte-carlo: monte-carlo.c

monte-carlo-two-thirds: monte-carlo-two-thirds.c

clean:
	rm -f $(EXECUTABLES)
