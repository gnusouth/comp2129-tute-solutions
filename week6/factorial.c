#include <stdio.h>

int factorial(int);

int main()
{
	int x = 6;
	int fac_x = factorial(x);
	printf("%d! = %d\n", x, fac_x);
	return 0;
}

int factorial(int n)
{
	int result = 1;
	if (n > 0)
	{
		result = n * factorial(n - 1);
	}
	return result;
}
