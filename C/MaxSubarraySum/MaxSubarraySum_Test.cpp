// MaxSubarraySum_Test.cpp : Defines the entry point for this application.
//


# include "MaxSubarraySum.h"


int main()
{
	int i, array_length = 10000;
	clock_t start, end;
	ElementType result, *array;
	ElementType (*MaxSubarraySum)(const ElementType *, int);

	int algorithm_num = 3;
	const char *algorithm;
	const char *algorithms[] = {
		"Kadane",
		"Recursive",
		"Brute Force",
	};

	srand((unsigned)time(NULL));
	array = (ElementType *)calloc(array_length, sizeof(ElementType));
	if (array == NULL) {
		FatalError("Can't allocate the required memory!");
	}
	else {
		for (i = 0; i < array_length; i++) {
			array[i] = rand() - RAND_MAX / 2;
			//array[i] = (rand() - RAND_MAX / 2) % 10;
		}
		printf("The original array:\n");
		print_array(array, array_length);
		printf(SEPARATOR);
	}

	for (i = 0; i < algorithm_num; i++) {
		algorithm = algorithms[i];
		if (strcmp(algorithm, "Brute Force") == 0) {
			MaxSubarraySum = &BruteForce;
		}
		else if (strcmp(algorithm, "Recursive") == 0) {
			MaxSubarraySum = &Recursive;
		}
		else if (strcmp(algorithm, "Kadane") == 0) {
			MaxSubarraySum = &Kadane;
		}
		else {
			continue;
		}
		
		start = clock();
		result = MaxSubarraySum(array, array_length);
		end = clock();
		printf("The time spend on %s algorithm: %.3lf ms\n", algorithm, timing(end, start));
		printf("The maximum subarray sum is : %d\n", result);
		printf(SEPARATOR);
	}
	free(array);
	return 0;
}
