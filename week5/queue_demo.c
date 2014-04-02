#include <stdio.h>
#include "queue.h"

int main()
{
	Queue q = queue_create();

	queue_push(q, 2);
	queue_push(q, 0);
	queue_push(q, 4);
	queue_push(q, 8);

	while (!queue_isempty(q))
	{
		int item = queue_pop(q);
		printf("%d", item);
	}
	printf("\n");

	queue_delete(q);
	return 0;
}
