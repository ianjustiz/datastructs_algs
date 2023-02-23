
// LinkedList in C

// PROS:
// - O(1) insertion of elements to tail or head;
//	 Insertion at any arbitrary position doesn't require shifting all other elements.
// - Does not need to be stored in contiguous memory location.
// - Length can change dynamically.

// CONS:
// - O(k) access to kth element in list.
// - Each node is more memory-intensive when compared to an array.

#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H

typedef struct node
{
	int data;
	struct node *next;
} node;

typedef struct LinkedList
{
	node *head;
	node *tail;
} LinkedList;


LinkedList *create_list(void);

void head_insert(LinkedList *list, int data);

void tail_insert(LinkedList *list, int data);

LinkedList *delete_linked_list(LinkedList *list);

void print_linked_list(LinkedList *list);

#endif