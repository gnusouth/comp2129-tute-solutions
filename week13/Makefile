CC = clang
CFLAGS = -W -Wall -std=gnu11 -pedantic -g
LDFLAGS = -lm

no_sse:
	$(CC) $(CFLAGS) -o no_sse sse_example.c $(LDFLAGS)

sse:
	$(CC) $(CFLAGS) -DUSE_SSE -o sse sse_example.c $(LDFLAGS)
