#include <stdio.h>
#include <pthread.h>

#define NTHREADS (4)
#define BIGNUM   (10000000)

int counter = 0;

void * worker(void * arg)
{
	for (int i = 0; i < BIGNUM; i++)
	{
		counter++;
	}
	return NULL;
}

int main(void)
{
	pthread_t threads[NTHREADS];

	for (int i = 0; i < NTHREADS; i++)
	{
		pthread_create(&threads[i], NULL, worker, NULL);
	}

	for (int i = 0; i < NTHREADS; i++)
	{
		pthread_join(threads[i], NULL);
	}

	printf("counter  = %d\n", counter);
	printf("expected = %d\n", NTHREADS * BIGNUM);
	return 0;
}
