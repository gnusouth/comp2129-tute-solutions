#include <stdio.h>
#include <math.h>

int main(void)
{
	float one = 1;
	float eps = 1;

	// Repeatedly halve epsilon until we get absurdity
	while (one + eps != one)
	{
		eps /= 2;
	}

	printf("1 + %g = 1\n", eps);
	printf("log2(eps) = %g\n", log(eps) / log(2));
	return 0;
}
