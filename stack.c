#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "linkedlist.h"

#define STACK_EMPTY_ERR INT_MAX

// I implement a stack w/o capacity here.
typedef struct Stack
{
	LinkedList *list;
	int size;
} Stack;

Stack *create_stack(void)
{
	Stack *new_stack = malloc(sizeof(Stack));

	if (new_stack == NULL)
		return NULL;

	new_stack->list = create_list();

	if (new_stack->list == NULL)
		return NULL;

	new_stack->size = 0;

	return new_stack;
}

int isEmpty(Stack *s)
{
	return (s == NULL || s->size == 0);
}

int isFull(Stack *s)
{
	return (s == NULL);
}

void push(Stack *s, int data)
{
	if (isFull(s))
		return;

	head_insert(s->list, data);

	s->size++;
}

int pop(Stack *s)
{
	node *head;
	int data;

	if (isEmpty(s))
		return STACK_EMPTY_ERR;

	head = s->list->head;
	data = head->data;

	s->list->head = head->next;
	free(head);

	s->size--;

	return data;
}

int peek(Stack *s)
{
	if (isEmpty(s))
		return STACK_EMPTY_ERR;

	return s->list->head->data;
}

int top(Stack *s)
{
	return peek(s);
}

void print_stack(Stack *s)
{
	print_linked_list(s->list);
}

int main(void)
{
	Stack *cool_stack = create_stack();

	push(cool_stack, 20);
	push(cool_stack, 40);
	push(cool_stack, 60);

	printf("%d\n", top(cool_stack));

	pop(cool_stack);
	pop(cool_stack);
	pop(cool_stack);
	pop(cool_stack);
	pop(cool_stack);
	pop(cool_stack);

	push(cool_stack, 19);

	print_stack(cool_stack);

}
