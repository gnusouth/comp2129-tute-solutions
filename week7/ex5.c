#include <stdio.h>
#include <math.h>

#define TERMS 10000000L

int main(void)
{
	float sum1 = 0, sum2 = 0;

	// Add up biggest to smallest
	for (long i = 1; i <= TERMS; i++)
	{
		float n = i;
		sum1 += n;
	}

	// Add up smallest to biggest
	for (long i = TERMS; i > 0; i--)
	{
		float n = i;
		sum2 += n;
	}

	printf("Biggest to smallest: %.4f\n", sum1);
	printf("Smallest to biggest: %.4f\n", sum2);

	long long actual_sum = (TERMS*(TERMS - 1)) / 2;
	printf("Actual sum: %lld\n", actual_sum);

	return 0;
}
