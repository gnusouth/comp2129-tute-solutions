CC = clang
CFLAGS = -W -Wall -std=gnu11 -pedantic
LDFLAGS = -lpthread

EXECUTABLES = philosophers falseshare robots

default: $(EXECUTABLES)

padded:
	clang $(CFLAGS) -DPADDING -o padded falseshare.c $(LDFLAGS)

local:
	clang $(CFLAGS) -DLOCAL -o local falseshare.c $(LDFLAGS)

clean:
	rm -f $(EXECUTABLES) local padded

.PHONY: default clean padded local
