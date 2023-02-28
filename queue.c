#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "linkedlist.h"

#define QUEUE_EMPTY_ERR INT_MAX

// I implement a queue w/o capacity here.

// QUEUE //
// FIFO Abstract Data Structure
typedef struct Queue
{
	LinkedList *list;
	int size;
} Queue;

Queue *create_queue(void)
{
	Queue *new_queue = malloc(sizeof(Queue));

	if (new_queue == NULL)
		return NULL;

	new_queue->list = create_list();

	if (new_queue->list == NULL)
		return NULL;

	new_queue->size = 0;

	return new_queue;
}

int isEmpty(Queue *q)
{
	return (q == NULL || q->size == 0);
}

int isFull(Queue *q)
{
	return (q == NULL);
}

void enqueue(Queue *q, int data)
{
	if (isFull(q) || data == QUEUE_EMPTY_ERR)
		return;

	tail_insert(q->list, data);

	s->size++;
}

int dequeue(Queue *q)
{
	node *head;
	int data;

	if (isEmpty(q))
		return QUEUE_EMPTY_ERR;

	head = q->list->head;
	data = head->data;

	q->list->head = head->next;
	free(head);

	q->size--;

	return data;
}

int peek(Queue *q)
{
	if (isEmpty(q))
		return QUEUE_EMPTY_ERR;

	return q->list->head->data;
}

int front(Queue *q)
{
	return peek(q);
}

void print_queue(Queue *q)
{
	print_linked_list(q->list);
}

int main(void)
{
	return 0;
}