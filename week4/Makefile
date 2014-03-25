CC = gcc
CFLAGS = -W -Wall -pedantic -std=c99

EXECUTABLES = args stderr countlines linelens sumsqs

all: $(EXECUTABLES)

args: args.c

stderr: stderr.c

countlines: countlines.c

linelens: linelens.c

sumsqs: sumsqs.c

clean:
	rm -rf $(EXECUTABLES)

.PHONY: all clean
