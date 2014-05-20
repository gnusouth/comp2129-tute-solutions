#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ITERATIONS (100000000)

#define PADDING_SIZE 56

// Thead arg struct.
typedef struct {
	unsigned int seed;
	unsigned int answer;

	#ifdef PADDING
    // Padding to fill a 64-byte cache line
	char padding[PADDING_SIZE];
	#endif
} WorkerArgs;

// Initialised by main()
int nthreads;

void *worker(void *arg)
{
	WorkerArgs *work = (WorkerArgs *) arg;

	printf("Thread working on args at %p\n", work);

	#ifdef LOCAL
    // Temporary local variable (to avoid false sharing)
	unsigned int answer = 0;
	#else
    // Set the answer to zero if we're modifying the struct directly (-DPADDING, or no args)
	work->answer = 0;
	#endif

	for (int i = 0; i < ITERATIONS / nthreads; i++)
	{
		#ifdef LOCAL
        // Update the temporary local variable if compiled with -DLOCAL
		answer += rand_r(&work->seed);
		#else
        // Otherwise, update the struct variable (source of false sharing if no padding is used).
		work->answer += rand_r(&work->seed);
		#endif
	}

	#ifdef LOCAL
    // If using the local variable approach, write the local variable's value back to the struct.
	work->answer = answer;
	#endif

	return NULL;
}

int main(int argc, char *argv[])
{
	// Read in the number of threads from the command line.
	if (argc != 2 || sscanf(argv[1], "%d", &nthreads) != 1)
	{
		fprintf(stderr, "usage: %s <nthreads>\n", argv[0]);
		return 1;
	}

	pthread_t threads[nthreads];

    /* The false sharing occurs here. These structs are allocated one after another on the stack,
     * and will be loaded into the same cache line by default (they're only 8 bytes each).
     * If you compile with -DPADDING, 56 bytes of padding will be inserted at the end of each struct
     * so that each one occupies an entire cache line. The other alternative is to avoid modifying the
     * struct variable from within the thread function by using a temporary local variable.
     * To get this behaviour, compile the program with -DLOCAL
     */
	WorkerArgs work[nthreads];

	for (int i = 0; i < nthreads; i++)
	{
		work[i].seed = i;
		pthread_create(&threads[i], NULL, worker, &work[i]);
	}

	unsigned int total = 0;
	for (int i = 0; i < nthreads; i++)
	{
		pthread_join(threads[i], NULL);
		total += work[i].answer;
	}

	printf("%u\n", total);
	return 0;
}
