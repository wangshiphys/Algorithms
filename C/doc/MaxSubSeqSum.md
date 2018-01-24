# Maximum Subsequence Sum Problem
This project provides several solutions for the Maximum Subsequence Sum Problem.

## Definition
Given (possibly negative) integers $A_1$, $A_2$, ..., $A_N$, find the maximum value of $\sum_{k=i}^j{A_k}$. *(For convenience, the maximum subsequence sum is 0 if all the integers are negative.)*

Example:
> For input -2, 11, -4, 13, -5, -2, the answer is 20 ($A_2$ through $A_4$)

This project provide **four** algorithms to solve the problem:

* int MaxSubseqSum_A(int arr[], int N)

    The running time of this algorithm is $O(N^3)$

* int MaxSubseqSum_B(int arr[], int N)

    The running time of this algorithm is $O(N^2)$

* int MaxSubseqSum_C(int arr[], int N)

    This is a recursive solution and the running time is $O(NlogN)$.

    The algorithm uses a "divide-and-conquer" strategy. The idea is to split the problem into two roughly equal subproblems, which are then solved recursively. This is the "divide" part. The "conquer" stage consists of patching together the two subproblems and possibly doing a small amount of additional work, to arrive at a solution for the whole problem.

    In our case, the maximum subsequence sum can be in one of three places. Either it occurs entirely in the left half of the input, or entirely in the right half, or it crosses the middle and is in both halves. The first two cases can be solved recursively. The last case can be obtained by finding the largest sum in the first half that include the last element in the first half and the largest sum in the second half that include the first element in the second half. These two sums can be added together.

* int MaxSubseqSum_D(int arr[], int N)

    This is an $O(N)$ (linear) solution and is simple to implement
