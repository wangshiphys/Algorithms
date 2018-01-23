#pragma once

#ifndef _SORTING
#define _SORTING

#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SORT_CUTOFF 10
#define OUTPUT_CUTOFF 15
#define SEPARATOR "====================================================================\n"
#define Error(str) FatalError(str)
#define FatalError(str) fprintf(stderr, "%s\n", str), exit(EXIT_FAILURE)
#define left_child(i) (2 * (i) + 1)


typedef int ElementType;

void print_array(int arr[], int N);
void swap(ElementType *x, ElementType *y);
void copy_array(ElementType src[], ElementType dst[], int N);
double timing(clock_t end, clock_t start);
void insertion_sort(ElementType arr[], int N);
void bubble_sort(ElementType arr[], int N);
void selection_sort(ElementType arr[], int N);
void shell_sort(ElementType arr[], int N);
void heap_sort(ElementType arr[], int N);
void merge_sort(ElementType arr[], int N);
void quick_sort(ElementType arr[], int N);
void bucket_sort(int arr[], int N);

#endif
