#include <stdio.h>
#include <stdlib.h>

int ascending_order(const void * x, const void * y)
{
	const int * a = x;
	const int * b = y;
	return (*a - *b);
}

int descending_order(const void * x, const void * y)
{
	const int * a = x;
	const int * b = y;
	return (*b - *a);
}

int magnitude_order(const void * x, const void * y)
{
	// Make the void pointers into int pointers
	const int * a = x;
	const int * b = y;

	// Return the difference between the absolute values
	return (abs(*a) - abs(*b));
}

void print_array(int * array, int length)
{
	printf("{");
	for (int i = 0; i < length - 1; i++)
	{
		printf("%d, ", array[i]);
	}
	printf("%d}\n", array[length - 1]);
}

int main()
{
	int array_length = 9;
	int array[] = {10, 5, 6, -1, 9, 5, 8, 1, -5};

	printf("The original array: ");
	print_array(array, array_length);

	printf("The array sorted in ascending order: ");
	qsort(array, array_length, sizeof(int), ascending_order);
	print_array(array, array_length);

	printf("The array sorted in descending order: ");
	qsort(array, array_length, sizeof(int), descending_order);
	print_array(array, array_length);

	printf("The array sorted by magnitude: ");
	qsort(array, array_length, sizeof(int), magnitude_order);
	print_array(array, array_length);

	return 0;
}
