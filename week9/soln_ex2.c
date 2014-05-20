#include <stdio.h>
#include <pthread.h>

#define NTHREADS (4)
#define BIGNUM   (100000)

int counter = 0;
pthread_mutex_t lock;

void *worker(void *arg)
{
	for (int i = 0; i < BIGNUM; i++)
	{
		pthread_mutex_lock(&lock);
		counter++;
		pthread_mutex_unlock(&lock);
	}
	return NULL;
}

int main(void)
{
	pthread_t threads[NTHREADS];
	pthread_mutex_init(&lock, NULL);

	for (int i = 0; i < NTHREADS; i++)
		pthread_create(&threads[i], NULL, worker, NULL);

	for (int i = 0; i < NTHREADS; i++)
		pthread_join(threads[i], NULL);

	pthread_mutex_destroy(&lock);
	printf("counter  = %d\n", counter);
	printf("expected = %d\n", NTHREADS * BIGNUM);
	return 0;
}
