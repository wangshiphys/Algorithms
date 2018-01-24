#include "MaxSubseqSum.h"


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


double timing(clock_t end, clock_t start)
{
	return (double)(end - start) * 1000 / CLOCKS_PER_SEC;
}


ElementType MaxSubSeqSum_A(const ElementType arr[], int N)
{
	int i, j, k;
	ElementType  temp, max_sum = 0;

	for (i = 0; i < N; i++) {
		for (j = i; j < N; j++) {
			temp = 0;
			for (k = i; k <= j; k++) {
				temp += arr[k];
			}
			if (temp > max_sum) {
				max_sum = temp;
			}
		}
	}
	return max_sum;
}


ElementType MaxSubSeqSum_B(const ElementType arr[], int N)
{
	int i, j;
	ElementType temp, max_sum;

	max_sum = 0;
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


static ElementType MaxSubSeqSum_C_Helper(const ElementType arr[], int left, int right)
{
	int center, i;
	ElementType max_sum_left, max_sum_right;
	ElementType max_sum_left_border, max_sum_right_border;
	ElementType temp;

	if (left == right) {
		if (arr[left] > 0) {
			return arr[left];
		}
		else {
			return 0;
		}
	}

	center = (left + right) / 2;
	max_sum_left = MaxSubSeqSum_C_Helper(arr, left, center);
	max_sum_right = MaxSubSeqSum_C_Helper(arr, center+1, right);

	temp = 0;
	max_sum_left_border = 0;
	for (i = center; i >= left; i--) {
		temp += arr[i];
		if (temp > max_sum_left_border) {
			max_sum_left_border = temp;
		}
	}

	temp = 0;
	max_sum_right_border = 0;
	for (i = center+1; i <= right; i++) {
		temp += arr[i];
		if (temp > max_sum_right_border) {
			max_sum_right_border = temp;
		}
	}
	temp = max_sum_left_border + max_sum_right_border;
	return max3(max_sum_left, max_sum_right, temp);
}


ElementType MaxSubSeqSum_C(const ElementType arr[], int N)
{
	return MaxSubSeqSum_C_Helper(arr, 0, N - 1);
}


ElementType MaxSubSeqSum_D(const ElementType arr[], int N)
{
	int i;
	ElementType temp, max_sum;

	temp = 0;
	max_sum = 0;
	for (i = 0; i < N; i++) {
		temp += arr[i];
		if (temp > max_sum) {
			max_sum = temp;
		}
		else if (temp < 0) {
			temp = 0;
		}
	}
	return max_sum;
}
