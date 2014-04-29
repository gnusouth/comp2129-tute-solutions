#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NTHREADS 4
#define ARRAY_SIZE 32001

// Worker data struct
typedef struct
{
	int * array;
	int start;
	int end;
	int answer;
} WorkerArgs;

// Worker function
void * worker(void * args)
{
	WorkerArgs * wargs = (WorkerArgs *) args;

	wargs->answer = 0;
	for (int i = wargs->start; i < wargs->end; i++)
	{
		wargs->answer += wargs->array[i];
	}

	return NULL;
}

int main()
{
	// Create the array
	int array[ARRAY_SIZE];

	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		array[i] = i + 1;
	}

	// Create the structs for the workers
	WorkerArgs arguments[NTHREADS];

	for (int i = 0; i < NTHREADS; i++)
	{
		arguments[i].array = array;
		arguments[i].start = i * (ARRAY_SIZE / NTHREADS);
		arguments[i].end = (i + 1) * (ARRAY_SIZE / NTHREADS);
		arguments[i].answer = -1;
	}

	// Make sure the last thread goes right to the end
	arguments[NTHREADS - 1].end = ARRAY_SIZE;

	// Create the threads
	pthread_t threads[NTHREADS];

	for (int i = 0; i < NTHREADS; i++)
	{
		pthread_create(&threads[i], NULL, worker, (void *) &arguments[i]);
	}

	// Collect the results
	int sum = 0;
	for (int i = 0; i < NTHREADS; i++)
	{
		if (pthread_join(threads[i], NULL) != 0)
		{
			printf("Thread error!!\n");
			continue;
		}
		// Fetch the partial sum from the args array
		sum += arguments[i].answer;
	}

	// Print and check the result (maths wins)
	int expected = ((ARRAY_SIZE + 1) * ARRAY_SIZE) / 2;

	printf("computed = %d\n", sum);
	printf("expected = %d\n", expected);

	return 0;
}
