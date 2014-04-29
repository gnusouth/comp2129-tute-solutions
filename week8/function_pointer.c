#include <stdio.h>

char int_to_char(int x)
{
	if (x < 0 || x >= 10)
	{
		return '!';
	}
	return ('0' + x);
}

int ** fake_2d_array(int * array)
{
	return (int **) array;
}

int main()
{
	// Create a function pointer
	char (*my_function)(int) = int_to_char;

	// Call the function
	printf("%c\n", my_function(7));

	// Watch out for the weird syntax
	int ** (*pointless)(int *) = fake_2d_array;

	int * thing = NULL;
	if (pointless(thing) == NULL)
	{
		printf("It works!\n");
	}

	return 0;
}
