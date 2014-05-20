#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Matrices here are WIDTH x WIDTH
#define WIDTH (512)

// The number of threads to use
#define NTHREADS 4

struct WorkChunk
{
	int start_row;
	int end_row;
	double * A;
	double * B;
	double * C;
};

double trace(double * A);
void multiply(double * A, double * B, double * C);

int main(void)
{
	// Create three matrices.
	double *A = calloc(WIDTH * WIDTH, sizeof(double));
	double *B = calloc(WIDTH * WIDTH, sizeof(double));
	double *C = calloc(WIDTH * WIDTH, sizeof(double));

	// Create initial values for A and B
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			A[WIDTH * i + j] = i + j;
			B[WIDTH * i + j] = 2 * i - j;
		}
	}

	// Set C = A x B
	multiply(A, B, C);

	// Print out the trace of the result.
	printf("%f\n", trace(C));

	free(A);
	free(B);
	free(C);
	return 0;
}

void * worker_fn(void * args)
{
	struct WorkChunk * chunk = (struct WorkChunk *) args;
	double * A = chunk->A;
	double * B = chunk->B;
	double * C = chunk->C;

	for (int i = chunk->start_row; i < chunk->end_row; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			C[WIDTH * i + j] = 0;
			for (int k = 0; k < WIDTH; k++)
			{
				C[WIDTH * i + j] += A[WIDTH * i + k] * B[WIDTH * k + j];
			}
		}
	}
	return NULL;
}

// Set outC = inA x inB.
void multiply(double * A, double * B, double * C)
{
	pthread_t threads[NTHREADS];
	struct WorkChunk work[NTHREADS];

	int rows_per_thread = WIDTH / NTHREADS;

	// Create threads
	for (int i = 0; i < NTHREADS; i++)
	{
		work[i].start_row = i * rows_per_thread;
		work[i].end_row = (i + 1) * rows_per_thread;

		if (i == NTHREADS - 1)
		{
			work[i].end_row = WIDTH;
		}

		work[i].A = A;
		work[i].B = B;
		work[i].C = C;

		int error = pthread_create(threads + i, NULL, worker_fn, (void * ) (work + i));
		if (error)
		{
			printf("Unable to create thread\n");
			return;
		}
	}

	// Join threads
	for (int i = 0; i < NTHREADS; i++)
	{
		pthread_join(threads[i], NULL);
	}
}

double trace(double *A)
{
	double sum = 0;
	for (int i = 0; i < WIDTH; i++)
	{
		sum += A[WIDTH * i + i];
	}
	return sum;
}
