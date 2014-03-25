#include <stdio.h>

void good_swap(int * a, int * b);
void bad_swap(int a, int b);
void does_this_work_swap(int a, int b);


int main()
{
	int a = 7;
	int b = 99;

	printf("Here are the initial values.\n");
	printf("a = %d, b = %d\n", a, b);

	printf("Swapping using pointers!\n");
	good_swap(&a, &b);
	printf("a = %d, b = %d\n", a, b);

	printf("Swapping without pointers!\n");
	bad_swap(a, b);
	printf("a = %d, b = %d\n", a, b);

	#ifdef _EXPERIMENT
	printf("Swapping without pointers, take two!\n");
	does_this_work_swap(a, b);
	printf("a = %d, b = %d\n", a, b);
	#endif

	return 0;
}


void good_swap(int * a, int * b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}


/* Attempt to swap a and b by assigning them to each other */
void bad_swap(int a, int b)
{
	int temp = a;
	a = b;
	b = temp;
}


/* Attempt to swap a and b by getting their addresses INSIDE the function call... */
void does_this_work_swap(int a, int b)
{
	int * a_ptr = &a;
	int * b_ptr = &b;
	good_swap(a_ptr, b_ptr);
}

