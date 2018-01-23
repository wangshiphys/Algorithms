// Sorting.cpp : Defines the entry point for the console application.
//

#include "sorting.h"


int main()
{
    int i, array_length = 20000;
    clock_t start, end;
    ElementType *array_to_sort, *sorted_array;
    void(*sorting)(ElementType *, int);


    int algorithm_num = 8;
    const char *algorithm;
    const char *algorithms[] = {
        "bucket",
        "quick",
        "merge",
        "shell",
        "heap",
        "insertion",
        "selection",
        "bubble",
    };

    srand((unsigned)time(NULL));
    array_to_sort = (ElementType *)calloc(array_length, sizeof(ElementType));
    sorted_array = (ElementType *)calloc(array_length, sizeof(ElementType));
    if (array_to_sort == NULL || sorted_array == NULL) {
        FatalError("Can't allocate the required memory!");
    }
    else {
        for (i = 0; i < array_length; i++)
            array_to_sort[i] = rand() - RAND_MAX / 2;
        printf("The original array:\n");
        print_array(array_to_sort, array_length);
        printf(SEPARATOR);
    }

    for (i = 0; i < algorithm_num; i++) {
        algorithm = algorithms[i];
        if (strcmp(algorithm, "insertion") == 0)
            sorting = &insertion_sort;
        else if (strcmp(algorithm, "bubble") == 0)
            sorting = &bubble_sort;
        else if (strcmp(algorithm, "selection") == 0)
            sorting = &selection_sort;
        else if (strcmp(algorithm, "shell") == 0)
            sorting = &shell_sort;
        else if (strcmp(algorithm, "heap") == 0)
            sorting = &heap_sort;
        else if (strcmp(algorithm, "merge") == 0)
            sorting = &merge_sort;
        else if (strcmp(algorithm, "quick") == 0)
            sorting = &quick_sort;
        else if (strcmp(algorithm, "bucket") == 0)
            sorting = &bucket_sort;
        else
            continue;

        copy_array(array_to_sort, sorted_array, array_length);
        start = clock();
        sorting(sorted_array, array_length);
        end = clock();
        printf("The time spend on %s sort: %.3lf ms\n", algorithm, timing(end, start));
        printf("The sorted array:\n");
        print_array(sorted_array, array_length);
        printf(SEPARATOR);
    }
    free(sorted_array);
    free(array_to_sort);
    return 0;
}

