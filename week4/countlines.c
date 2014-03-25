#include <stdio.h>

char buf[1024];

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
		return 1;
	}

	FILE *fp = fopen(argv[1], "r");

	if (fp == NULL)
	{
		sprintf(buf, "%s: %s", argv[0], argv[1]);
		perror(buf);
		return 1;
	}

	int count = 0;
	while (fgets(buf, sizeof(buf), fp) != NULL)
	{
		count++;
	}
	fclose(fp);

	printf("%d\n", count);
	return 0;
}
