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

// Personally, I don't like doing stuff like this.
// See the official solutions for an implementation using this typedef.
// typedef struct Queue * Queue;

// Creates an empty queue.
struct Queue * queue_create();

// Returns 1 if the queue is empty, 0 otherwise.
int queue_isempty(struct Queue *);

// Pushes a new element onto the back of the queue.
void queue_push(struct Queue *, int);

// Removes and returns the element at the front of the queue.
// WARNING: only call this when the queue is not empty.
int queue_pop(struct Queue *);

// Deletes any elements in the queue, then
// deletes the queue itself.
void queue_delete(struct Queue *);

#endif				//QUEUE_H
