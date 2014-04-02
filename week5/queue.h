#ifndef QUEUE_H
#define QUEUE_H

struct Node
{
	int data;
	struct Node * next;
	struct Node * prev;
};

struct Queue
{
	struct Node * front;
	struct Node * back;
};

// Alias the struct Queue * to a short type (Queue) so that
// the caller is presented with a simple interface.
typedef struct Queue * Queue;

// Creates an empty queue.
Queue queue_create(void);

// Returns 1 if the queue is empty, 0 otherwise.
int queue_isempty(Queue);

// Pushes a new element onto the back of the queue.
void queue_push(Queue, int);

// Removes and returns the element at the front of the queue.
// WARNING: only call this when the queue is not empty.
int queue_pop(Queue);

// Deletes any elements in the queue, then
// deletes the queue itself.
void queue_delete(Queue);

#endif				//QUEUE_H
