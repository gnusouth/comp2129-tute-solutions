#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Matrices here are WIDTH x WIDTH
#define WIDTH (512)

double trace(double *A);
void multiply(double *inA, double *inB, double *outC);

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

// Set outC = inA x inB.
void multiply(double *inA, double *inB, double *outC)
{
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			outC[WIDTH * i + j] = 0;
			for (int k = 0; k < WIDTH; k++)
			{
				outC[WIDTH * i + j] += inA[WIDTH * i + k] * inB[WIDTH * k + j];
			}
		}
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
