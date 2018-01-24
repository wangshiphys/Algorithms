// MaxSubseqSum_Test.cpp : Defines the entry point for this application.
//


# include "MaxSubSeqSum.h"


int main()
{
	int i, array_length = 10000;
	clock_t start, end;
	ElementType result, *array;
	ElementType (*MaxSubSeqSum)(const ElementType *, int);

	int algorithm_num = 4;
	char algorithm;
	char algorithms[] = { 'D', 'C', 'B', 'A' };

	srand((unsigned)time(NULL));
	array = (ElementType *)calloc(array_length, sizeof(ElementType));
	if (array == NULL) {
		FatalError("Can't allocate the required memory!");
	}
	else {
		for (i = 0; i < array_length; i++)
			array[i] = rand() - RAND_MAX / 2;
			//array[i] = (rand() - RAND_MAX / 2) % 10;
		printf("The original array:\n");
		print_array(array, array_length);
		printf(SEPARATOR);
	}

	for (i = 0; i < algorithm_num; i++) {
		algorithm = algorithms[i];
		switch (algorithm)
		{
			case 'a':
			case 'A':
				MaxSubSeqSum = &MaxSubSeqSum_A; break;
			case 'b':
			case 'B':
				MaxSubSeqSum = &MaxSubSeqSum_B; break;
			case 'c':
			case 'C':
				MaxSubSeqSum = &MaxSubSeqSum_C; break;
			case 'd':
			case 'D':
				MaxSubSeqSum = &MaxSubSeqSum_D; break;
			default:
				break;
		}
		
		start = clock();
		result = MaxSubSeqSum(array, array_length);
		end = clock();
		printf("The time spend on MaxSubSeqSum_%c: %.3lf ms\n", algorithm, timing(end, start));
		printf("The maximum subsequence sum is : %d\n", result);
		printf(SEPARATOR);
	}
	free(array);
	return 0;
}
