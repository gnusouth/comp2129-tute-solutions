#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

#define NTHREADS (2)
#define ITERATIONS (100000000)

void *worker(void *arg)
{
	int *ans = (int *)arg;

	// Use the answer slot to pass in the seed ...
	unsigned int state = *ans;
	int count = 0;
	for (int i = 0; i < ITERATIONS / NTHREADS; i++)
	{
		double x = (double)rand_r(&state) / (double)RAND_MAX;
		double y = (double)rand_r(&state) / (double)RAND_MAX;
		if (x * x + y * y <= 1)
		{
			count++;
		}
	}
	*ans = count;
	return NULL;
}

int main(void)
{
	pthread_t threads[NTHREADS];

	int counts[NTHREADS];

	for (int i = 0; i < NTHREADS; i++)
	{
		counts[i] = i;
		pthread_create(&threads[i], NULL, worker, &counts[i]);
	}

	int count = 0;

	for (int i = 0; i < NTHREADS; i++)
	{
		pthread_join(threads[i], NULL);
		count += counts[i];
	}

	double pi = ((double) count / (double) ITERATIONS) * 4;
	printf("Estimated Pi: %.8f\n", pi);
	printf("Actual Pi   : %.8f\n", M_PI);
	return 0;
}
