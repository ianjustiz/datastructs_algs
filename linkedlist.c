#include <stdio.h>
#include <stdlib.h>

// LinkedList in C

// PROS:
// - O(1) insertion of elements to tail or head.
// - Does not need to be stored in contiguous memory location.
// - 

// CONS:
// - O(k) access to kth element in list.
// - Each node is more memory-intensive when compared to an array.

typedef struct node
{
	int data;
	struct node next;
} node;

typedef struct LinkedList
{
	node *head;
	node *tail;
} LinkedList;

node *create_node(int data)
{
	node *new_node = malloc(sizeof(node));

	new_node->data = data;
	new_node->next = NULL;

	return new_node;
}

LinkedList *create_list()
{
	LinkedList *new_list = malloc(sizeof(LinkedList));

	new_list->head = NULL;
	new_list->tail = NULL;

	return new_list;
}

LinkedList *head_insert(int data, LinkedList *list)
{
	node *new_node;

	// NULL check for list.
	if (list == NULL)
		return NULL;

	// Create a node with given parameters.
	new_node = create_node(data);

	// For an empty list, update head + tail with our node.
	if (head == NULL)
	{
		list->head = list->tail = new_node;
		return list;
	}

	// Otherwise, list is non-empty. Perform insertion.
	new_node->next = list->head;
	list->head = new_node;
	return list;
}

LinkedList *tail_insert(int data, LinkedList *list)
{
	node *new_node;

	// NULL check for list.
	if (list == NULL)
		return NULL;

	// Create a node with given parameters.
	new_node = create_node(data);

	// For an empty list, update head + tail with our node.
	if (head == NULL)
	{
		list->head = list->tail = new_node;
		return list;
	}

	// Otherwise, list is non-empty. Perform insertion.
	list->
	return list;
}

int main(int argc, char **argv)
{

}
