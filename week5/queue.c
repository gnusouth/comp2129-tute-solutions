#include <stdlib.h>
#include "queue.h"

struct Queue * queue_create(void)
{
	struct Queue * q = malloc(sizeof(struct Queue));
	*q = (struct Queue) {.front = NULL, .back = NULL};
	return q;
}

void queue_delete(struct Queue * q)
{
	struct Node * current = q->front;
	while (current != NULL)
	{
		struct Node * tmp = current;
		current = current->next;
		free(tmp);
	}
	free(q);
}

int queue_isempty(struct Queue * q)
{
	return (q->front == NULL);
}

void queue_push(struct Queue * q, int data)
{
	struct Node * n = malloc(sizeof(struct Node));
	*n = (struct Node) {.data = data, .next = q->back, .prev = NULL};

	if (q->front == NULL)
	{
		q->front = n;
	}

	if (q->back != NULL)
	{
		q->back->prev = n;
	}

	q->back = n;
}

int queue_pop(struct Queue * q)
{
	// Get the front of the queue
	struct Node * n = q->front;

	// Move the front pointer backwards
	q->front = n->prev;

	// If there was only one item, set back to NULL
	if (q->front == NULL)
	{
		q->back = NULL;
	}
	// Otherwise change the new front element's next pointer
	else
	{
		q->front->next = NULL;
	}

	// Extract the data from the node
	int data = n->data;

	// Free the node!
	free(n);

	// Return the data (which we stored before the free)
	return data;
}
