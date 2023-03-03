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
// Worst case: O(n + m)
// Best case: O(n + m)
// (where n is the amount of elements in the array, and m is the range of the elements.)

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

	free(buckets);
}

// Radix Sort (L.S.D.) //
// Worst case: O(nd) or (n log m)
// Best case: O(nd) or (n log m)
// (where n is the amount of elements, m is the largest value in the array,
// and d is the amount of digits in m.)

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

	free(buckets);
}

// Merge Sort //
// Worst case: O(n log n)
// Best case: O(n log n)
// (where n...)

// Description: 
// Notes:

void merge_sort_recursive(int *arr, int lo, int hi)
{
	int mid;
	int i, j, curr;
	int *left, *right;
	int left_max, right_max;

	// Base case.
	if (lo >= hi)
		return;

	// Calculate maximum, careful to avoiding going out of bounds.
	mid = lo + (hi - lo) / 2;

	// Recursive calls for subarrays.
	merge_sort_recursive(arr, lo, mid);
	merge_sort_recursive(arr, mid + 1, hi);

	// Calculate size of left and right arrays.
	left_max = mid - lo + 1;
	right_max = hi - mid;

	// Dynamically allocate memory for new arrays.
	left = malloc(sizeof(int) * left_max);
	right = malloc(sizeof(int) * right_max);

	// Copy values into new arrays
	for (i = 0; i < left_max; i++)
		left[i] = arr[lo + i];

	for (j = 0; j < right_max; j++)
		right[j] = arr[mid + 1 + j];		

	// Assign variables for use in merging.
	curr = lo;
	i = 0;
	j = 0;

	// Merge subarrays.
	while (curr <= hi)
	{
		if (i >= left_max || j < right_max && left[i] > right[j])
			arr[curr++] = right[j++];
		else if (j >= right_max || left[i] <= right[j])
			arr[curr++] = left[i++];
	}

	// Free left and right arrays.
	free(left);
	free(right);
}

void merge_sort(int *arr, int n)
{
	merge_sort_recursive(arr, 0, n - 1);
}

// Quicksort //
// Worst case: O(n^2)
// Best case: O(n log n)

// Description: Quicksort employs the divide-and-conquer strategy. A pivot can be selected
// by several means, including the median-of-three strategy and by merely using the leftmost element.
// Two pointers iterate from the left to right side of a given array, swapping when both are pointing
// to elements on the incorrect sides (greater than and less than respectively). When one of several
// terminating conditions is reached, the pivot is swapped into sorted position. Quicksort is then
// called recursively on the remaining subarrays, excluding the previously sorted element (pivot).
// Notes: On average, Quicksort is the fastest comparison-based sorting algorithm.
// For small arrays, it is recommended to use a different algorithm.

int get_pivot(int *arr, int lo, int hi)
{
	// Expand to use median-of-three.
	return lo;
}

void quick_sort_recursive(int *arr, int lo, int hi)
{
	int pivot, index_pivot;
	int i, j, cont;

	// Base case.
	if (lo >= hi)
		return;

	// Get a pivot and its index.
	index_pivot = get_pivot(arr, lo, hi);
	pivot = arr[index_pivot];

	// Initialize pointers for left and right side.
	i = index_pivot + 1;
	j = hi;

	// Perform swapping operation.
	while (i < j)
	{
		while (arr[i] <= pivot && i <= j)
			i++;

		while (arr[j] > pivot && j > index_pivot)
			j--;

		if (i < j && arr[i] > pivot && arr[j] <= pivot)
			swap(arr, i++, j--);
	}

	// Ensure the right pointer (now likely left) is pointing to an element equal to
	// or less than the pivot, if not the pivot itself.
	while (j > index_pivot && arr[j] > pivot)
		j--;

	// Swap if the right pointer's element is less than the pivot.
	if (arr[j] < pivot)
	{
		swap(arr, index_pivot, j);
		index_pivot = j;
	}

	// Recursive calls for subarrays.
	quick_sort_recursive(arr, lo, index_pivot - 1);
	quick_sort_recursive(arr, index_pivot + 1, hi);
}

void quick_sort(int *arr, int n)
{
	quick_sort_recursive(arr, 0, n-1);
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

int sort_tester(void)
{
	int *a;
	int i, j;

	for (i = 0; i < 1000000; i++)
	{
		a = generate_rand_str(20);

		quick_sort(a, 20);

		for (j = 1; j < 20; j++)
			if (a[j] < a[j-1])
				return 1;

		free(a);
	}

	return 0;
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

	//printf("%s\n", tester() ? "Does not work." : "Works great!");

	a = generate_rand_str(size);
	print_string(a, size);
	fflush(stdout);

	quick_sort(a, size);
	print_string(a, size);

	return 0;
}
