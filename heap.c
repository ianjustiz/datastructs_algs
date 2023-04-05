#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define GENERIC_HEAP_ERR INT_MAX

// Implementation of minheap in C

typedef struct heap
{
	int *heap;
	int capacity, size;
} heap;

heap *makeHeap(int capacity)
{
	heap *new_heap;

	if (capacity < 1)
		return NULL;

	new_heap = malloc(sizeof(heap));
	new_heap->heap = malloc(sizeof(int) * capacity);

	new_heap->capacity = capacity;
	new_heap->size = 0;

	return new_heap;
}

int isFull(heap *heapy)
{
	return heapy == NULL || heapy->size >= heapy->capacity;
}

int isEmpty(heap *heapy)
{
	return heapy == NULL || heapy->size == 0;
}

int getParent(heap *heapy, int index)
{
	if (heapy == NULL || index < 0 || index >= heapy->size)
		return GENERIC_HEAP_ERR;

	return (index - 1) / 2;
}

int getLeftChild(heap *heapy, int index)
{
	if (heapy == NULL || index < 0)
		return GENERIC_HEAP_ERR;

	return ((2 * index + 1) < heapy->size) ? 2 * index + 1 : GENERIC_HEAP_ERR;
}

int getRightChild(heap *heapy, int index)
{
	if (heapy == NULL || index < 0)
		return GENERIC_HEAP_ERR;

	return ((2 * index + 2) < heapy->size) ? 2 * index + 2 : GENERIC_HEAP_ERR;
}

int getFirstNonLeaf(heap *heapy)
{
	if (heapy == NULL)
		return GENERIC_HEAP_ERR;

	return getParent(heapy, heapy->size - 1);
}

int getMin(heap *heapy)
{
	if (heapy == NULL)
		return GENERIC_HEAP_ERR;

	return heapy->heap[0];
}

void swap(heap *heapy, int a, int b)
{
	int temp;

	if (a < 0 || b < 0 || a >= heapy->size || b >= heapy->size)
		return;

	temp = heapy->heap[a];

	heapy->heap[a] = heapy->heap[b];
	heapy->heap[b] = temp;

	return;
}

int max(int a, int b)
{
	return a > b ? a : b;
}

void percolateDown(heap *heapy, int index)
{
	int left, right;

	left = getLeftChild(heapy, index);
	right = getRightChild(heapy, index);

	if (left == GENERIC_HEAP_ERR || right == GENERIC_HEAP_ERR)
		return;

	if (heapy->heap[left] < heapy->heap[right])
	{
		if (heapy->heap[index] > heapy->heap[left])
		{
			swap(heapy, index, left);
			percolateDown(heapy, left);
		}
	}

	else
	{
		if (heapy->heap[index] > heapy->heap[right])
		{
			swap(heapy, index, right);
			percolateDown(heapy, right);
		}
	}
}

void percolateUp(heap *heapy, int index)
{
	int parent;

	parent = getParent(heapy, index);

	if (parent == GENERIC_HEAP_ERR || parent == index)
		return;

	if (heapy->heap[index] < heapy->heap[parent])
	{
		swap(heapy, index, parent);
		percolateUp(heapy, parent);
	}
}

void insert(heap *heapy, int elem);

void deleteMin(heap *heapy);

heap *deleteHeap(heap *heapy)
{
	return NULL;
}

int main(void)
{
	heap *heapy = makeHeap(100);


	return 0;
}