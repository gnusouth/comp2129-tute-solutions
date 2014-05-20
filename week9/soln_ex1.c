#include <stdio.h>
#include <pthread.h>
#include <time.h>

#define NTHREADS (4)
#define BIGNUM   (10000000)

int counter = 0;

void *worker(void *arg)
{
	for (int i = 0; i < BIGNUM; i++)
		counter++;
	return NULL;
}

int main(void)
{
	pthread_t threads[NTHREADS];
	clock_t tick, tock;

	tick = clock();
	for (int i = 0; i < NTHREADS; i++)
		pthread_create(&threads[i], NULL, worker, NULL);
	tock = clock();
	printf("Time elapsed: %f seconds\n",
	       (double)(tock - tick) / CLOCKS_PER_SEC);

	for (int i = 0; i < NTHREADS; i++)
		pthread_join(threads[i], NULL);

	printf("counter  = %d\n", counter);
	printf("expected = %d\n", NTHREADS * BIGNUM);
	return 0;
}
