#pragma once

#ifndef _MAXSUBSEQSUM
#define _MAXSUBSEQSUM

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define OUTPUT_CUTOFF 15
#define SEPARATOR "====================================================================\n"
#define Error(str) FatalError(str)
#define FatalError(str) fprintf(stderr, "%s\n", str), exit(EXIT_FAILURE)

typedef int ElementType;

void print_array(int arr[], int N);
double timing(clock_t end, clock_t start);
ElementType MaxSubSeqSum_A(const ElementType arr[], int N);
ElementType MaxSubSeqSum_B(const ElementType arr[], int N);
ElementType MaxSubSeqSum_C(const ElementType arr[], int N);
ElementType MaxSubSeqSum_D(const ElementType arr[], int N);

#endif
