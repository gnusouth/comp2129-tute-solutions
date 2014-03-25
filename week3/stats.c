#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXLEN (1024)

// "Forward" declaration of functions, so we can use them before we define them.
double compute_mean(double * nums, int array_length);
double compute_stdev(double * nums, double mean, int array_length);

int main()
{
	double nums[MAXLEN];

	int array_length = 0;
	while (1)
	{
		int num_matches = scanf("%lf", &nums[array_length]);

		/* Check for a successful match */
		if (num_matches == 1)
		{
			array_length++;
		}
		else
		{
			printf("Input format error.\n");
			exit(1);
		}

		/* If the last number read was -1, leave the loop. */
		if (nums[array_length - 1] == -1)
		{
			array_length--;
			break;
		}

		/* If the region of allocated memory is full, leave the loop. */
		if (array_length == MAXLEN)
		{
			printf("Max number of arguments reached.\n");
			break;
		}
	}

	double mean = compute_mean(nums, array_length);
	double stdev = compute_stdev(nums, mean, array_length);

	printf("mean: %.2lf\n", mean);
	printf("stdev: %.2lf\n", stdev);
	return 0;
}

double compute_mean(double * nums, int array_length)
{
	if (array_length == 0)
	{
		return 0.0;
	}

	double mean = 0.0;
	for (int i = 0; i < array_length; i++)
	{
		mean += nums[i];
	}
	mean /= array_length;
	return mean;
}

double compute_stdev(double * nums, double mean, int array_length)
{
	if (array_length <= 1)
	{
		return 0.0;
	}

	double stdev = 0.0;
	double diff;
	for (int i = 0; i < array_length; i++)
	{
		diff = nums[i] - mean;
		stdev += diff*diff;
	}
	stdev /= (array_length - 1);
	stdev = sqrt(stdev);
	return stdev;
}
