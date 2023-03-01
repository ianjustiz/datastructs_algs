
// Queues in C

#ifndef _QUEUE_H
#define _QUEUE_H

#define QUEUE_EMPTY_ERR INT_MAX

typedef struct Queue
{
	LinkedList *list;
	int size;
} Queue;


Queue *create_queue(void);

int isEmpty(Queue *q);

int isFull(Queue *q);

void enqueue(Queue *q, int data);

int dequeue(Queue *q);

int peek(Queue *q);

int front(Queue *q);

#endif