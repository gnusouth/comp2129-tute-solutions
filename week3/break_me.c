#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int x, y, z;
	int *ptr;
	scanf("%d %d %d", &x, &y, &z);

	if (x < y) {
		ptr = &x;
	}
	if (x < z) {
		ptr = &y;
	}
	else {
		ptr = &z;
	}

	if (x > z) {
		*ptr = z;
	}

	printf("Made it through the conditionals!\n");

	printf("Magic number is: %d\n", *ptr);

	return 0;
}
