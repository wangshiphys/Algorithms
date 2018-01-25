#include "MaxSubarraySum.h"


// Print the input array in a beautiful format
void print_array(int arr[], int N)
{
	int i;
	if (N <= OUTPUT_CUTOFF) {
		for (i = 0; i < N - 1; i++)
			printf("%6d, ", arr[i]);
	}
	else {
		for (i = 0; i < OUTPUT_CUTOFF / 2; i++)
			printf("%6d, ", arr[i]);
		printf("......, ");
		for (i = N - OUTPUT_CUTOFF / 2; i < N - 1; i++)
			printf("%6d, ", arr[i]);
	}
	printf("%6d\n", arr[N - 1]);
}


// Calculate the time between `end` and `start` in millisecond
double timing(clock_t end, clock_t start)
{
	return (double)(end - start) * 1000 / CLOCKS_PER_SEC;
}


// Solution for the Maximum Subarray Sum problem
// Exhaustively tries all possibilities for the solution to the problem
ElementType BruteForce(const ElementType arr[], int N)
{
	int i, j;
	ElementType temp, max_sum;

	max_sum = arr[0];
	for (i = 0; i < N; i++) {
		temp = 0;
		for (j = i; j < N; j++) {
			temp += arr[j];
			if (temp > max_sum) {
				max_sum = temp;
			}
		}
	}
	return max_sum;
}


static ElementType max3(ElementType a, ElementType b, ElementType c)
{
	ElementType temp;
	temp = (a > b) ? a : b;
	return (c > temp) ? c : temp;
}


static ElementType Recursive_Helper(const ElementType arr[], int left, int right)
{
	int center, i;
	ElementType temp;
	ElementType max_sum_left, max_sum_right;
	ElementType max_sum_left_border, max_sum_right_border;

	if (left == right)
		return arr[left];

	center = (left + right) / 2;
	max_sum_left = Recursive_Helper(arr, left, center);
	max_sum_right = Recursive_Helper(arr, center+1, right);

	temp = 0;
	max_sum_left_border = arr[center];
	for (i = center; i >= left; i--) {
		temp += arr[i];
		if (temp > max_sum_left_border) {
			max_sum_left_border = temp;
		}
	}

	temp = 0;
	max_sum_right_border = arr[center + 1];
	for (i = center+1; i <= right; i++) {
		temp += arr[i];
		if (temp > max_sum_right_border) {
			max_sum_right_border = temp;
		}
	}
	temp = max_sum_left_border + max_sum_right_border;
	return max3(max_sum_left, temp, max_sum_right);
}


// Solution for the Maximum Subarray Sum problem
// This algorithm uses a "Divide-and-Conquer" strategy
ElementType Recursive(const ElementType arr[], int N)
{
	return Recursive_Helper(arr, 0, N - 1);
}


// Solution for the Maximum Subarray Sum problem
// Implementation of Kadane's algorithm
ElementType Kadane(const ElementType arr[], int N)
{
	int i;
	ElementType temp, max_sum;

	temp = 0;
	max_sum = arr[0];
	for (i = 0; i < N; i++) {
		temp += arr[i];
		if (temp > max_sum) {
			max_sum = temp;
		}
		if (temp < 0) {
			temp = 0;
		}
	}
	return max_sum;
}
