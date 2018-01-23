#include "sorting.h"


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


void copy_array(ElementType src[], ElementType dst[], int N)
{
    int i;

    for (i = 0; i < N; i++)
        dst[i] = src[i];
}


void swap(ElementType *x, ElementType *y)
{
    ElementType temp;
    temp = *x;
    *x = *y;
    *y = temp;
}


double timing(clock_t end, clock_t start)
{
    return (double)(end - start) * 1000 / CLOCKS_PER_SEC;
}


static void insertion_sort_core(ElementType arr[], int N, int increment)
{
    int i, j;
    ElementType temp;
    for (i = increment; i < N; i++) {
        temp = arr[i];
        for (j = i; j >= increment && arr[j - increment] > temp; j -= increment)
            arr[j] = arr[j - increment];
        arr[j] = temp;
    }
}


void insertion_sort(ElementType arr[], int N)
{
    insertion_sort_core(arr, N, 1);
}


void bubble_sort(ElementType arr[], int N)
{
    int i, j;
    ElementType temp0, temp1;
    for (i = N - 1; i > 0; i--)
        for (j = 0; j < i; j++) {
            temp0 = arr[j];
            temp1 = arr[j + 1];
            if (temp0 > temp1) {
                arr[j] = temp1;
                arr[j + 1] = temp0;
            }
        }
}


void selection_sort(ElementType arr[], int N)
{
    int i, j, min_index;
    ElementType temp;
    for (i = 0; i < N - 1; i++) {
        min_index = i;
        for (j = i + 1; j < N; j++)
            if (arr[j] < arr[min_index])
                min_index = j;
        temp = arr[i];
        arr[i] = arr[min_index];
        arr[min_index] = temp;
    }
}


void shell_sort(ElementType arr[], int N)
{
    int i;
    int SEDGEWICK_INCREMENTS[] = {
        1,          5,         19,         41,        109,
        209,        505,        929,       2161,       3905,
        8929,      16001,      36289,      64769,     146305,
        260609,     587521,    1045505,    2354689,    4188161,
        9427969,   16764929,   37730305,   67084289,  150958081,
        268386305,  603906049, 1073643521,
    };

    if (N > SORT_CUTOFF) {
        // The length of SEDGEWICK_INCREMENTS is 28
        // Start find the tail of SEDGEWICK_INCREMENTS, and eliminiate all entries that
        // are larger than N/2
        for (i = 27; SEDGEWICK_INCREMENTS[i] > N / 2; i--);
        for (; i >= 0; i--)
            insertion_sort_core(arr, N, SEDGEWICK_INCREMENTS[i]);
    }
    else {
        insertion_sort_core(arr, N, 1);
    }
}


static void percolate_down(ElementType arr[], int index, int N)
{
    int child;
    ElementType temp;

    for (temp = arr[index]; left_child(index) < N; index = child) {
        child = left_child(index);
        if (child != N - 1 && arr[child + 1] > arr[child])
            child++;
        if (temp < arr[child])
            arr[index] = arr[child];
        else
            break;
    }
    arr[index] = temp;
}


void heap_sort(ElementType arr[], int N)
{
    int i;
    ElementType temp;
    for (i = N / 2; i >= 0; i--)
        percolate_down(arr, i, N);
    for (i = N - 1; i > 0; i--) {
        temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        percolate_down(arr, 0, i);
    }
}


static void merge(ElementType arr[], ElementType buffer[], int left_start, int right_start, int right_end)
{
    int index0, index1, index;
    index0 = left_start;
    index1 = right_start;
    index = left_start;

    while (index0 < right_start && index1 <= right_end) {
        if (arr[index0] <= arr[index1])
            buffer[index++] = arr[index0++];
        else
            buffer[index++] = arr[index1++];
    }
    while (index0 < right_start)
        buffer[index++] = arr[index0++];
    while (index1 <= right_end)
        buffer[index++] = arr[index1++];
    for (index = left_start; index <= right_end; index++) {
        arr[index] = buffer[index];
    }
}


static void msort(ElementType arr[], ElementType buffer[], int left, int right)
{
    int center;
    if (left < right) {
        center = left + (right - left) / 2;
        msort(arr, buffer, left, center);
        msort(arr, buffer, center + 1, right);
        merge(arr, buffer, left, center + 1, right);
    }
}


void merge_sort(ElementType arr[], int N)
{
    ElementType *buffer;
    buffer = (ElementType *)calloc(N, sizeof(ElementType));
    if (buffer != NULL) {
        msort(arr, buffer, 0, N - 1);
        free(buffer);
    }
    else {
        FatalError("Can't allocate the required memory!");
    }
}


static ElementType median3(ElementType arr[], int left, int right)
{
    int center = left + (right - left) / 2;
    ElementType temp;

    if (arr[left] > arr[center]) {
        temp = arr[left];
        arr[left] = arr[center];
        arr[center] = temp;
    }
    if (arr[left] > arr[right]) {
        temp = arr[left];
        arr[left] = arr[right];
        arr[right] = temp;
    }
    if (arr[center] > arr[right]) {
        temp = arr[center];
        arr[center] = arr[right];
        arr[right] = temp;
    }
    temp = arr[center];
    arr[center] = arr[right - 1];
    arr[right - 1] = temp;
    return arr[right - 1];
}


static void qsort(ElementType arr[], int left, int right)
{
    int i, j;
    ElementType pivot, temp;

    if (right - left >= SORT_CUTOFF)
    {
        pivot = median3(arr, left, right);
        i = left;
        j = right - 1;
        for (;;) {
            while (arr[++i] < pivot) {}
            while (arr[--j] > pivot) {}
            if (i < j) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
            else {
                break;
            }
        }
        temp = arr[i];
        arr[i] = arr[right - 1];
        arr[right - 1] = temp;

        qsort(arr, left, i - 1);
        qsort(arr, i + 1, right);
    }
    else {
        insertion_sort_core(arr + left, right - left + 1, 1);
    }
}


void quick_sort(ElementType arr[], int N)
{
    qsort(arr, 0, N - 1);
}


static void find_extreme(int arr[], int N, int *min, int*max)
{
    int i, temp;

    *min = arr[0];
    *max = arr[0];
    for (i = 0; i < N; i++) {
        temp = arr[i];
        if (temp < *min)
            *min = temp;
        if (temp > *max)
            *max = temp;
    }
}


static void bucket_sort_core(int arr[], int N, int min, int max)
{
    int i, j, index, *buffer;

    max -= min;
    buffer = (int *)calloc(max + 1, sizeof(int));
    if (buffer != NULL) {
        for (i = 0; i < N; i++) {
            buffer[arr[i] - min]++;
        }
        for (index = 0, i = 0; i <= max; i++) {
            for (j = buffer[i]; j > 0; j--) {
                arr[index++] = i + min;
            }
        }
        free(buffer);
    }
    else {
        FatalError("Can't allocate the required memory!");
    }
}


void bucket_sort(int arr[], int N)
{
    int i, j, index, min, max, *buffer;

    //Find the  minimum and maximum of the input array
    min = arr[0];
    max = arr[0];
    for (i = 0; i < N; i++) {
        j = arr[i];
        if (j < min)
            min = j;
        if (j > max)
            max = j;
    }

    max -= min;
    buffer = (int *)calloc(max + 1, sizeof(int));
    if (buffer != NULL) {
        for (i = 0; i < N; i++) {
            buffer[arr[i] - min]++;
        }
        for (index = 0, i = 0; i <= max; i++) {
            for (j = buffer[i]; j > 0; j--) {
                arr[index++] = i + min;
            }
        }
        free(buffer);
    }
    else {
        FatalError("Can't allocate the required memory!");
    }
}

