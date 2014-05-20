#include <stdio.h>
#include <stdlib.h>

int main()
{
	int maxnum = 1000000;

	char * is_prime = malloc(maxnum * sizeof(char));

	// Mark all items initially prime
	for (int i = 0; i < maxnum; i++)
	{
		is_prime[i] = 1;
	}

	// Sieve
	for (int i = 2; i*i < maxnum; i++)
	{
		for (int j = i; i*j < maxnum; j++)
		{
			is_prime[i*j] = 0;
		}
	}
	is_prime[0] = 0;
	is_prime[1] = 0;

	// Print primes
	printf("Primes: ");
	for (int i = 0; i < maxnum; i++)
	{
		if (is_prime[i])
		{
			printf(" %d", i);
		}
	}
	printf("\n");

	free(is_prime);
	return 0;
}
