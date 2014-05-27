#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Global barrier variables
pthread_barrier_t barrier_1;
pthread_barrier_t barrier_2;

// Thread argument struct.
struct WorkerArgs
{
	int * board1;
	int * board2;
	int start;
	int end;
	int array_length;
	int num_generations;
};

typedef struct WorkerArgs WorkerArgs;

// Prints the board, using ' ' for a dead cell, and 'A' for a live cell.
void print_board(int *board, int width)
{
	for (int i = 0; i < width; i++)
	{
		printf("%c", (board[i] == 0) ? ' ' : 'A');
	}
	printf("\n");
}

// Worker function that computes the evolution of a section of the board.
void * next_gen(void * args)
{
	// Extract variables from the struct, as usual.
	WorkerArgs * work = (WorkerArgs *) args;
	int array_length = work->array_length;
	int num_generations = work->num_generations;

	// Store local current and next pointers (they get swapped later)
	int * current = work->board1;
	int * next = work->board2;

	for (int t = 0; t < num_generations; t++)
	{
		// Wait for the main thread to print the current generation
		pthread_barrier_wait(&barrier_1);

		// Compute the next generation
		for (int i = work->start; i < work->end; i++)
		{
			int left = (i + array_length - 1) % array_length;
			int right = (i + 1) % array_length;
			next[i] = current[left] ^ current[right];
		}

		// Swap the local copies of the pointers
		int * temp = current;
		current = next;
		next = temp;

		// Wait for all the threads
		pthread_barrier_wait(&barrier_2);
	}

	return NULL;
}

int main(void)
{
	int width = 64;
	int generations = 32;
	int * board1 = calloc(width, sizeof(int));
	int * board2 = calloc(width, sizeof(int));

	// Initial generation: only one live cell in the middle
	board1[width / 2] = 1;

	// Thread stuff
	// Note: nthreads is the number of threads to *create*
	int nthreads = 4;
	pthread_t threads[nthreads];
	WorkerArgs work[nthreads];

	// Initialise the barriers
	// We use nthreads + 1 to account for the main thread
	pthread_barrier_init(&barrier_1, NULL, nthreads + 1);
	pthread_barrier_init(&barrier_2, NULL, nthreads + 1);

	// Divide the work between the threads and spin them up
	int work_per_thread = width / nthreads;

	for (int i = 0; i < nthreads; i++)
	{
		work[i].board1 = board1;
		work[i].board2 = board2;
		work[i].array_length = width;
		work[i].num_generations = generations;

		work[i].start = i * work_per_thread;
		work[i].end = (i + 1) * work_per_thread;

		if (i == nthreads - 1)
		{
			work[i].end = width;
		}

		pthread_create(threads + i, NULL, next_gen, work + i);
	}

	// Let the threads compute the system's behaviour, while the main thread prints things
	for (int i = 0; i < generations; i++)
	{
		// Print the current generation.
		// printf("Generation %02d: ", i);
		print_board(board1, width);

		// Signal that the current generation has been printed
		pthread_barrier_wait(&barrier_1);

		// Wait for the threads to compute the next generation
		pthread_barrier_wait(&barrier_2);
	}

	// Join the threads (once the full number of generations has elapsed)
	for (int i = 0; i < nthreads; i++)
	{
		pthread_join(threads[i], NULL);
	}

	// Free resources (very important!)
	free(board1);
	free(board2);
	pthread_barrier_destroy(&barrier_1);
	pthread_barrier_destroy(&barrier_2);
	return 0;
}
