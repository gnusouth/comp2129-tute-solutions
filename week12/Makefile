CC = clang
CFLAGS = -W -Wall -pedantic -std=gnu11
LDFLAGS = -lpthread

EXECUTABLES = palindrome automata automata_parallel

default: $(EXECUTABLES)

palindrome: palindrome.c
	$(CC) $(CFLAGS) -DTEST -o palindrome $^

recursive: palindrome.c
	$(CC) $(CFLAGS) -DRECURSIVE -o palindrome $^

# If compiler optimisations are enabled, tail calls will be optimised
# and the recursive algorithm won't fail because of stack overflows!
optimised_recursive: palindrome.c
	$(CC) $(CFLAGS) -O3 -DRECURSIVE -o palindrome $^

iterative: palindrome.c
	$(CC) $(CFLAGS) -DITERATIVE -o palindrome $^

clean:
	rm -f $(EXECUTABLES)

.PHONY: default clean
