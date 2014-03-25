#include <stdio.h>

int main(int argc, char *argv[])
{
	for (int i = 0; i < argc; i++)
	{
		printf("arg[%d]: %s\n", i, argv[i]);
	}
	printf("%c\n", argv[1][0]);
	return 0;
}
