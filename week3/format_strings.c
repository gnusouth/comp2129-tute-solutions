#include <stdio.h>

char * names[] = {"Bob", "Jane Doe", "John Smith"};
int sids[] = {12345678, 23456789, 98765432};
double marks[] = {99.87632, 78.29561, 62.11345};

int main()
{
	printf("%-12s %-10s %s\n", "Name", "SID", "Mark");
	for (int i = 0; i < 3; i++)
	{
		printf("%-12s %-10d %.2f\n", names[i], sids[i], marks[i]);
	}

	return 0;
}
