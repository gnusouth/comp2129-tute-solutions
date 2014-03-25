#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	// Check that a number has been provided as a cmd-line arg.
	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <number>\n", argv[0]);
		return 1;
	}

	// Convert the argument to an integer
	int n;
	if (sscanf(argv[1], "%d", &n) != 1)
	{
		fprintf(stderr, "Parse error on input %s\n", argv[1]);
		return 1;
	}

	// Allocate memory
	int *nums = (int *) malloc(n * sizeof(int));

	// Compute squares
	for (int i = 0; i < n; i++)
	{
		nums[i] = (i + 1) * (i + 1);
	}

	// Sum the squares
	int sum = 0;
	for (int i = 0; i < n; i++)
	{
		sum += nums[i];
	}

	printf("%d\n", sum);

	// FREE THE MEMORY.
	free(nums);
	return 0;
}
