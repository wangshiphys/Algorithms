#pragma once

#ifndef _MAXSUBARRAYSUM
#define _MAXSUBARRAYSUM

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define OUTPUT_CUTOFF 15
#define SEPARATOR "====================================================================\n"
#define Error(str) FatalError(str)
#define FatalError(str) fprintf(stderr, "%s\n", str), exit(EXIT_FAILURE)

typedef int ElementType;

void print_array(int arr[], int N);
double timing(clock_t end, clock_t start);
ElementType BruteForce(const ElementType arr[], int N);
ElementType Recursive(const ElementType arr[], int N);
ElementType Kadane(const ElementType arr[], int N);

#endif
