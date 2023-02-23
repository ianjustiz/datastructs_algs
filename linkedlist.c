#include <stdio.h>
#include <stdlib.h>

#include "linkedlist.h"

node *create_node(int data)
{
	node *new_node = malloc(sizeof(node));

	if (new_node == NULL)
		return NULL;

	new_node->data = data;
	new_node->next = NULL;

	return new_node;
}

LinkedList *create_list(void)
{
	LinkedList *new_list = malloc(sizeof(LinkedList));

	if (new_list == NULL)
		return NULL;

	new_list->head = NULL;
	new_list->tail = NULL;

	return new_list;
}

void head_insert(LinkedList *list, int data)
{
	node *new_node;

	// NULL check for list.
	if (list == NULL)
		return;

	// Create a node with given parameters.
	new_node = create_node(data);

	// For an empty list, update head + tail with our node.
	if (list->head == NULL)
	{
		list->head = list->tail = new_node;
	}

	// Otherwise, list is non-empty. Perform insertion.
	else
	{
		new_node->next = list->head;
		list->head = new_node;
	}
}

void tail_insert(LinkedList *list, int data)
{
	node *new_node;

	// NULL check for list.
	if (list == NULL)
		return;

	// Create a node with given parameters.
	new_node = create_node(data);

	// For an empty list, update head + tail with our node.
	if (list->head == NULL)
	{
		list->head = list->tail = new_node;
	}

	// Otherwise, list is non-empty. Perform insertion.
	else
	{
		printf("%d\n", data);
		list->tail = list->tail->next = new_node;
	}
}

node *delete_list(node *head)
{
	node *curr;

	// Free each node iteratively.
	while (head != NULL)
	{
		curr = head->next;
		free(head);
		head = curr;
	}

	return NULL;
}

LinkedList *delete_linked_list(LinkedList *list)
{
	// NULL check for list.
	if (list == NULL)
		return NULL;

	// Free the interior list and the broader struct.
	delete_list(list->head);
	free(list);

	return NULL;
}

void print_list(node *head)
{
	if (head == NULL)
		return;

	printf("[ %d ]%s", head->data, head->next == NULL ?
		"\n" : " -> ");

	print_list(head->next);
}

void print_linked_list(LinkedList *list)
{
	node *curr;

	// NULL check for list.
	if (list == NULL)
	{
		printf("Provided list is NULL.\n");
		return;
	}

	// Empty check for list.
	else if(list->head == NULL)
	{
		printf("Provided list is empty.\n");
	}

	// Print elements.
	else
	{
		print_list(list->head);
	}
}

// int main(int argc, char **argv)
// {
// 	LinkedList *cool_list = create_list();
// 	tail_insert(cool_list, 14);
// 	tail_insert(cool_list, 41);
// 	tail_insert(cool_list, 30);
// 	head_insert(cool_list, 72);
// 	print_linked_list(cool_list);
// }
