#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

#define NTHREADS (4)
#define ITERATIONS (100000000)

void *worker(void *arg)
{
	double *ans = (double *)arg;

	// Use the answer slot to pass in the seed ...
	unsigned int state = *ans;
	double accum = 0;
	for (int i = 0; i < ITERATIONS / NTHREADS; i++)
	{
		double x = (double)rand_r(&state) / (double)RAND_MAX;
		double y = (double)rand_r(&state) / (double)RAND_MAX;
		accum += x * x + y * y;
	}
	*ans = accum;
	return NULL;
}

int main(void)
{
	pthread_t threads[NTHREADS];
	double accums[NTHREADS];
	for (int i = 0; i < NTHREADS; i++)
	{
		accums[i] = i;
		pthread_create(&threads[i], NULL, worker, &accums[i]);
	}

	double accum = 0;
	for (int i = 0; i < NTHREADS; i++)
	{
		pthread_join(threads[i], NULL);
		accum += accums[i];
	}

	double result = ((double)accum / (double)ITERATIONS);
	printf("Result:   %.6f\n", result);
	printf("Expected: %.6f\n", 2.0 / 3.0);
	return 0;
}
