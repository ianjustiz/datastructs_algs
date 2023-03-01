#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#include "linkedlist.h"
#include "queue.h"

// Swap function for use in sorting.
// Does not check if indices are out of bounds.
void swap(int *arr, int a, int b)
{
	int temp;

	temp = arr[a];
	arr[a] = arr[b];
	arr[b] = temp;
}

// Find max and min functions for use in sorting.
// Assumes arrays are properly initialized.
int find_max(int *arr, int n)
{
	int i;
	int max = arr[0];

	for (i = 1; i < n; i++)
		if (arr[i] > max)
			max = arr[i];

	return max;
}

int find_min(int *arr, int n)
{
	int i;
	int min = arr[0];

	for (i = 1; i < n; i++)
		if (arr[i] < min)
			min = arr[i];

	return min;
}

// Bubble sort //
// Worst case: O(n^2)
// Best case: O(n)

// Description: Iterates through an array, swapping elements
// one by one if values are not in ascending order.
// Notes: Generally not used.

void bubble_sort(int *arr, int n)
{
	int i, j;
	int sorted;

	for (sorted = n; sorted > 1; sorted--)
		for (i = 1; i < sorted; i++)
			if (arr[i] < arr[i-1])
				swap(arr, i, i-1);
}

// Selection Sort //
// Worst case: O(n^2)
// Best case: O(n^2)

// Description: Iterates through an array, finding the min element
// on each pass and swapping it to the front.
// This continues until only sorted elements remain.
// Notes: Generally not used. 

void selection_sort(int *arr, int n)
{
	int i;
	int index_min, sorted;

	for (sorted = 0; sorted < n - 1; sorted++)
	{
		index_min = sorted;

		for (i = sorted + 1; i < n; i++)
			if (arr[i] < arr[index_min])
				index_min = i;

		swap(arr, sorted, index_min);
	}

}

// Insertion Sort //
// Worst case: O(n^2)
// Best case: O(n)

// Description: We begin by assuming the first element, on its own,
// is a sorted array. On each pass, pull out the first unsorted element.
// Perform swaps within the sorted array to expand it.
// Notes: Typically faster than selection or bubble sort.

void insertion_sort(int *arr, int n)
{
	int i;
	int sorted;

	for (sorted = 1; sorted < n; sorted++)
	{
		for (i = sorted; i > 0; i--)
		{
			if (arr[i] > arr[i-1])
				break;

			swap(arr, i, i - 1);
		}
	}
}

// Bucket Sort //
// Worst case: O(n + k)
// Best case: O(n + k) **?**
// (where n is the amount of elements in the array, and k is the range of the elements.)

// Description: Also known as Counting Sort, this algorithm utilizes an array
// to store counters for each element in the array. For this reason, the range
// of your values must be known. 
// Notes: While this algorithm is fast, it can be extremely space-intensive.
// Should not be used in cases where the range of elements is large,
// relative to the amount of elements.

void bucket_sort(int *arr, int n)
{	
	int i;
	int pos;
	int max, min, range;
	int *buckets;

	max = find_max(arr, n);
	min = find_min(arr, n);

	// Currently only supports positive values.
	range = max;

	buckets = calloc(range + 1, sizeof(int));

	if (buckets == NULL)
		return;

	for (i = 0; i < n; i++)
		buckets[arr[i]]++;

	pos = 0;

	for (i = 0; i <= range; i++)
	{
		while (buckets[i] > 0)
		{
			arr[pos++] = i;
			buckets[i]--;
		}
	}
}

// Radix Sort (L.S.D.) //
// Worst case: O(nd)
// Best case: **
// (where n...)

// Description:
// Notes:

void radix_sort(int *arr, int n)
{
	Queue **buckets;
	int i, j;
	int val, pos;
	int max;

	// Initialize array to store all buckets.
	buckets = malloc(sizeof(Queue *) * 10);

	if (buckets == NULL)
		return;

	// Initialize digit buckets w/ null checks.
	for (i = 0; i < 10; i++)
	{
		buckets[i] = create_queue();

		if (buckets[i] == NULL)
			return;
	}

	// Store value of maximum integer in the array.
	max = find_max(arr, n);

	// For each power of ten,
	for (i = 1; i <= max; i *= 10)
	{
		// Iterate through our array, enqueuing by digit.
		for (j = 0; j < n; j++)
		{
			enqueue(buckets[arr[j] / i % 10], arr[j]);
		}

		pos = 0;

		// Dequeue each element in order.
		for (j = 0; j < 10; j++)
		{
			while (1)
			{
				if ((val = dequeue(buckets[j])) == QUEUE_EMPTY_ERR)
					break;

				arr[pos++] = val;
			}
		}
	}
}

int *generate_rand_str(int n)
{
	int *arr, i;
	arr = malloc(sizeof(int) * n);

	if (arr == NULL)
		return NULL;

	srand(time(NULL));

	for (i = 0; i < n; i++)
		arr[i] = rand() % 100;

	return arr;
}

void print_string(int *arr, int n)
{
	int i;

	for (i = 0; i < n; i++)
		printf("%d%c", arr[i], i == n-1 ? '\n' : ' ');
}

int main(void)
{
	int size = 10;
	int *a;

	a = generate_rand_str(size);
	print_string(a, size);

	radix_sort(a, size);
	print_string(a, size);


	return 0;
}
