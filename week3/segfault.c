#include <stdio.h>

/*
 * Segmentation faults occur whenever you access memory that you're not supposed to.
 * The OS has set aside certain regions for your program, and it'll get angry if you
 * disregard it. This program accepts a command line argument which specifies the type
 * of segfault to perform.
 * To get a random address segfault, run: ./segfault 2
*/

int main(int argc, char * argv[])
{
	char seg_type = '1';

	if (argc > 1) {
		seg_type = argv[1][0];
	}

	int * pointer;
	switch (seg_type) {
	case '1':
		pointer = NULL;
		break;
	case '2':
		pointer = (int *) 0x92397123;
		break;
	case '3':
	default:
		pointer = (int *) &pointer;
		pointer += 10000;
	}

	printf("Let's see what's at address %p...\n", (void *) pointer);

	// Dereferencing is the dangerous bit...
	printf("%d\n", *pointer);

	return 0;
}
