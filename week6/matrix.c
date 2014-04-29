#include <stdio.h>

void print_matrix(int matrix[3][3]);
void print_vector(int vector[3]);
void matrix_multiply(int matrix[3][3], int ivector[3], int ovector[3]);

int main(void)
{
	int matrix[3][3] = {	{1, 0, 1},
				{0, -1, -2},
				{-1, 1, 0}
	};

	int ivector[3] = {1, 1, 1};
	int ovector[3] = {0, 0, 0};

	printf("Matrix:\n");
	print_matrix(matrix);
	printf("\n");

	printf("Vector:\n");
	print_vector(ivector);
	printf("\n");

	// Calculate the product
	matrix_multiply(matrix, ivector, ovector);

	printf("Product:\n");
	print_vector(ovector);

	return 0;
}


void matrix_multiply(int matrix[3][3], int ivector[3], int ovector[3])
{
	for (int i = 0; i < 3; i++)
	{
		ovector[i] = 0;
		for (int j = 0; j < 3; j++)
		{
			ovector[i] += matrix[i][j] * ivector[j];
		}
	}
}


void print_matrix(int matrix[3][3])
{
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			printf("%2d ", matrix[i][j]);
		}
		printf("\n");
	}
}


void print_vector(int vector[3])
{
	for (int i = 0; i < 3; i++) {
		printf("%2d\n", vector[i]);
	}
}
